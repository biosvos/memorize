//
// Created by biosvos on 10/11/22.
//

#include <gtkmm.h>
#include "gtk_ui.h"

class AddWidget : public Gtk::Frame {
public:
    AddWidget() {
        Gtk::Grid grid;
        set_child(grid);
        Gtk::Label word_label("단어");
        grid.attach(word_label, 0, 0);
        Gtk::Entry word_entry;
        grid.attach(word_entry, 1, 0);

        Gtk::Label meanings_label("뜻");
        grid.attach(meanings_label, 0, 1);
        Gtk::Entry meanings_entry;
        grid.attach(meanings_entry, 1, 1);
        Gtk::Button button("button");
        grid.attach(button, 1, 2);
    }
};

class TrainWidget : public Gtk::Frame {
public:
    TrainWidget() {
        Gtk::Box box(Gtk::Orientation::VERTICAL);
        set_child(box);
        Gtk::Label word("A");
        Gtk::Label meaings("B");
        Gtk::Button button("button");
        box.append(word);
        box.append(meaings);
        box.append(button);
    }
};

class ListWidget : public Gtk::Frame {
public:
    ListWidget() {
        Gtk::ListViewText view(4);
        set_child(view);
//        view.set_model()
//        auto store = std::make_shared<Gtk::ListStore>();
        view.set_column_title(0, "word");
        view.set_column_title(1, "meanings");
        view.set_column_title(2, "next");
        view.set_column_title(3, "success");

        auto row = view.append();
        view.set_text(row, 0, "a");
        view.set_text(row, 1, "b");
        view.set_text(row, 2, "c");
        view.set_text(row, 3, "d");

    }
};


class MainWindow : public Gtk::Window {
public:
    MainWindow();

private:
    Gtk::Notebook notebook_;
    AddWidget add_;
    TrainWidget train_;
    ListWidget list_;
};

MainWindow::MainWindow() {
    set_title("Basic application");
    set_default_size(200, 200);
    set_child(notebook_);

    notebook_.set_expand();
    notebook_.append_page(add_, "add");
    notebook_.append_page(train_, "train");
    notebook_.append_page(list_, "list");
    notebook_.show();
}


void GtkUi::Run() {
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    app->make_window_and_run<MainWindow>(0, nullptr);
}
