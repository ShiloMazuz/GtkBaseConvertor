#include <iostream>
#include <gtkmm.h>
#include "converter.h"

class MyWindow : public Gtk::Window {
public:
    MyWindow()
        : adjustment(Gtk::Adjustment::create(0.0, 0.0, 10e9, 1.0, 10.0, 0.0)),
        entry(adjustment, 1.0, 0) // climb rate = 1.0, digits = 0
    {
        set_title("test window");
        set_default_size(300, 100);

        vbox.set_spacing(10);
        add(vbox);
        vbox.pack_start(entry, Gtk::PACK_SHRINK);
        //Gtk::PACK_SHRINK is equivilant to ...false, false, 0);

        label.set_text("WAWI!!!");
        vbox.pack_start(label, Gtk::PACK_SHRINK);

        button.set_label("press this pls");
        vbox.pack_start(button, false, false, 0); 
        //the first false, disables centering the widget in the space it has available,
        //the second false, disables expanding the widget to the available space

//        button.signal_clicked().connect(
//            [&] {
//                label.set_text(entry.get_text());
//        }); //I need to figure out what the fuck happens here

        button.signal_clicked().connect(
            [&] {
                label.set_text(decimalToHexString(entry.get_value_as_int()));
                std::cout << decimalToHexString(entry.get_value_as_int()) << '\n';
                               }); //I need to figure out what the fuck happens here
        show_all_children();
    }
private:
    Gtk::Box vbox{Gtk::ORIENTATION_VERTICAL};
    Glib::RefPtr<Gtk::Adjustment> adjustment;
    Gtk::SpinButton entry;
    Gtk::Label label;
    Gtk::Button button;
};

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gnome.typeconverter");
    MyWindow window {};
    return app->run(window);
}
