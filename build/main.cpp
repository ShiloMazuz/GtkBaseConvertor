#include <iostream>
#include <gtkmm.h>
#include <string>
#include "converter.h"

class MyWindow : public Gtk::Window {
public:
    MyWindow()
        : adjustment(Gtk::Adjustment::create(0.0, 0.0, 10e9, 1.0, 10.0, 0.0)),
        entry(adjustment, 1.0, 0) // climb rate = 1.0, digits = 0
    {
        set_title("Ip Converter");
        set_default_size(300, 100);

        vbox.set_spacing(10);
        add(vbox);
        vbox.pack_start(entry, Gtk::PACK_SHRINK);
        //Gtk::PACK_SHRINK is equivilant to ...false, false, 0);

        label.set_text("WAWI!!! (hex)");
        vbox.pack_start(label, Gtk::PACK_SHRINK);

        labelBin.set_text("WAWI!!! (bin)");
        vbox.pack_start(labelBin, Gtk::PACK_SHRINK);

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
                label.set_text("Hex Value: " + decimalToHexString(entry.get_value_as_int()));
                labelBin.set_text("Bin Value: " + decimalToBinString(entry.get_value_as_int()));
                std::cout << decimalToHexString(entry.get_value_as_int()) << '\n';
                               }); //I need to figure out what the fuck happens here
        //ip converter section
        entryIpInput.set_placeholder_text("enter an ip address");
        vbox.pack_start(entryIpInput, Gtk::PACK_SHRINK);

        //label to show converted ip adress
        labelIpBin.set_text("Bin ip:");
        vbox.pack_start(labelIpBin, Gtk::PACK_SHRINK);

        entryPrefix.set_placeholder_text("prefix");
        vbox.pack_start(entryPrefix, Gtk::PACK_SHRINK);

        labelSubnetMask.set_text("Subnet Mask:");
        vbox.pack_start(labelSubnetMask, Gtk::PACK_SHRINK);

        //button that converts ip address and prints labels
        buttonIpConvert.set_label("press to convert ip to bin");
        vbox.pack_start(buttonIpConvert, false, false, 0); 

        buttonIpConvert.signal_clicked().connect(
            [&] {
                labelIpBin.set_text("Bin ip: " + convertedIpToBin(extractIpFromString(entryIpInput.get_text())));
                labelSubnetMask.set_text("Subnet Mask: " + prefixToSubnetString(entryPrefix.get_text()));
                               }); //I need to figure out what the fuck happens here

        show_all_children();
    }
private:
    Gtk::Box vbox{Gtk::ORIENTATION_VERTICAL};
    Glib::RefPtr<Gtk::Adjustment> adjustment;
    //number conversion widgets
    Gtk::SpinButton entry;
    Gtk::Label label;
    Gtk::Label labelBin;
    Gtk::Button button;
    //ip conversion widgets
    Gtk::Entry entryIpInput;
    Gtk::Label labelIpBin;
    Gtk::Entry entryPrefix;
    Gtk::Label labelSubnetMask;
    Gtk::Button buttonIpConvert;
};

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gnome.typeconverter");
    MyWindow window {};
    return app->run(window);
}
