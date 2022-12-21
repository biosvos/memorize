//
// Created by biosvos on 12/19/22.
//

#include <gtkmm.h>
#include <iostream>


class HelloWorld : public Gtk::Window {
public:
    HelloWorld(int count) :
            m_button_("Hello World"),
            cnt_(count) {
        // Sets the margin around the button.
        m_button_.set_margin(10);

        // When the button receives the "clicked" signal, it will call the
        // on_button_clicked() method defined below.
        m_button_.signal_clicked().connect(sigc::mem_fun(*this,
                                                         &HelloWorld::OnButtonClicked));

        // This packs the button into the Window (a container).
        set_child(m_button_);
    }

    ~HelloWorld() override {}

protected:
    //Signal handlers:
    void OnButtonClicked() {
        std::cout << "Hello World" << std::endl;
        HelloWorld world(1);
        world.set_visible();
        world.set_modal();
        world.show();
    }

    //Member widgets:
    Gtk::Button m_button_;
    int cnt_;
};

int main(int argc, char **argv) {
    auto app = Gtk::Application::create();
    return app->make_window_and_run<HelloWorld>(argc, argv, 1);


    return 0;
}