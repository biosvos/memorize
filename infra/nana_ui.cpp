//
// Created by biosvos on 11/18/22.
//

#include <utility>
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>

#include "nana_ui.h"

namespace {
    std::string &LeftTrim(std::string &s) {
        auto it = std::find_if(s.begin(), s.end(),
                               [](char c) {
                                   return !std::isspace<char>(c, std::locale::classic());
                               });
        s.erase(s.begin(), it);
        return s;
    }

    std::string &RightTrim(std::string &s) {
        auto it = std::find_if(s.rbegin(), s.rend(),
                               [](char c) {
                                   return !std::isspace<char>(c, std::locale::classic());
                               });
        s.erase(it.base(), s.end());
        return s;
    }

    std::string &Trim(std::string &s) {
        return LeftTrim(RightTrim(s));
    }

    std::vector<std::string> Split(std::string str, const std::string &delim) {
        size_t pos;
        std::vector<std::string> ret;
        std::string token;
        while ((pos = str.find(delim)) != std::string::npos) {
            token = str.substr(0, pos);
            ret.push_back(Trim(token));
            str.erase(0, pos + delim.length());
        }
        ret.push_back(Trim(str));
        return ret;
    }
}

NanaUi::NanaUi(std::shared_ptr<IUsecase> usecase) :
        usecase_(std::move(usecase)) {}

void NanaUi::Run() {
    nana::form form;
    nana::place place(form);

    place.div("vert gap=5 <><fit word><fit meanings><show><success_or_failure><>");

    nana::label word_label = nana::label(form, "word");
    place.field("word") << word_label;
    nana::label meanings_label = nana::label(form, "meanings");
    place.field("meanings") << meanings_label;
    nana::button show_button = nana::button(form, "show");
    place.field("show") << show_button;
    nana::button success_button = nana::button(form, "success");
    nana::button failure_button = nana::button(form, "failure");
    place.field("success_or_failure")
            << success_button << failure_button;


    place.collocate();
    {
        meanings_label.hide();
        success_button.hide();
        failure_button.hide();
    }

    show_button.events().click([&]() {
        show_button.hide();
        meanings_label.show();
        success_button.show();
        failure_button.show();
    });

    success_button.events().click([&] {
        meanings_label.hide();
        success_button.hide();
        failure_button.hide();
        show_button.show();
    });

    failure_button.events().click([&] {
        meanings_label.hide();
        success_button.hide();
        failure_button.hide();
        show_button.show();
    });

    {
        nana::accel_key a_key;
        a_key.key = 'a';

        form.keyboard_accelerator(a_key, [&] {
            nana::inputbox box(form, "add card");
            nana::inputbox::text word("word");
            nana::inputbox::text meanings("meanings");
            if (box.show(word, meanings)) {
                auto means = Split(meanings.value(), ",");
                usecase_->AddCard(IUsecase::Card{word.value(), means, 0, 0});
            }
        });
    }

    {
        nana::accel_key l_key;
        l_key.key = 'l';

        form.keyboard_accelerator(l_key, [&] {
            nana::form child(form);

            nana::place child_place(child);
            child_place.collocate();

            child.modality();
        });
    }

    form.show();
    nana::exec();
}
