#include <iostream>
#include <gtkmm.h>
#include <string>
#include "converter.h"

class MyWindow : public Gtk::Window {
public:
    MyWindow(BaseObjectType* cobject,
             const Glib::RefPtr<Gtk::Builder>& builder)
        : adjustment(Gtk::Adjustment::create(0.0, 0.0, 10e9, 1.0, 10.0, 0.0))
        , Gtk::Window(cobject)
        //entry(adjustment, 1.0, 0) // climb rate = 1.0, digits = 0
    {
        set_title("Ip Converter");
        set_default_size(300, 100);

  //      grid.set_row_spacing(10);
  //      add(grid);
        builder->get_widget("grid", grid);
        builder->get_widget("entryIpInput", entryIpInput);
        builder->get_widget("entryPrefix", entryPrefix);
        builder->get_widget("labelIpBin", labelIpBin);
        builder->get_widget("labelSubnetMask", labelSubnetMask);
        builder->get_widget("buttonIpConvert", buttonIpConvert);

  //     grid.attach(entry, Gtk::PACK_SHRINK);
   //     //Gtk::PACK_SHRINK is equivilant to ...false, false, 0);

   //     label.set_text("WAWI!!! (hex)");
   //     grid.attach(label, Gtk::PACK_SHRINK);

   //     labelBin.set_text("WAWI!!! (bin)");
   //     grid.attach(labelBin, Gtk::PACK_SHRINK);

   //     button.set_label("press this pls");
   //     grid.attach(button, false, false, 0); 
        //the first false, disables centering the widget in the space it has available,
        //the second false, disables expanding the widget to the available space

//        button.signal_clicked().connect(
//            [&] {
//                label.set_text(entry.get_text());
//        }); //I need to figure out what the fuck happens here

//        button.signal_clicked().connect(
//            [&] {
//                label.set_text("Hex Value: " + decimalToHexString(entry.get_value_as_int()));
//                labelBin.set_text("Bin Value: " + decimalToBinString(entry.get_value_as_int()));
//                std::cout << decimalToHexString(entry.get_value_as_int()) << '\n';
//                               }); //I need to figure out what the fuck happens here
        //ip converter section
//        entryIpInput.set_placeholder_text("enter an ip address");
//        grid.attach(entryIpInput, 0, 0, 1, 1);
//        //col, row, col size, row size
//        //label to show converted ip adress
//        labelIpBin.set_text("Bin ip:");
//        grid.attach(labelIpBin, 0, 1, 1, 1);
//
//        entryPrefix.set_placeholder_text("prefix");
//        grid.attach(entryPrefix, 1, 0, 1, 1);
//
//        labelSubnetMask.set_text("Subnet Mask:");
//        grid.attach(labelSubnetMask, 0, 2, 1, 1);
//
//        //button that converts ip address and prints labels
//        buttonIpConvert.set_label("press to convert ip to bin");
//        grid.attach(buttonIpConvert, 0, 3, 1, 1); 

        buttonIpConvert->signal_clicked().connect(
            [&] {
                labelIpBin->set_text("Bin ip: " + convertedIpToBin(extractIpFromString(entryIpInput->get_text())));
                labelSubnetMask->set_text("Subnet Mask: " + prefixToSubnetString(entryPrefix->get_text()));
                               }); //I need to figure out what the fuck happens here

        show_all_children();
    }
private:
    Gtk::Grid* grid;
    Glib::RefPtr<Gtk::Adjustment> adjustment;
    //number conversion widgets
//    Gtk::SpinButton entry;
//    Gtk::Label label;
//    Gtk::Label labelBin;
//    Gtk::Button button;
    //ip conversion widgets
    Gtk::Entry* entryIpInput;
    Gtk::Entry* entryPrefix;
    Gtk::Label* labelIpBin;
    Gtk::Label* labelSubnetMask;
    Gtk::Button* buttonIpConvert;
};

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gnome.typeconverter");
    //auto builder = Gtk::Builder::create_from_file("../styling/layout.ui");
    auto builder = Gtk::Builder::create_from_file("../styling/layout.ui");
    MyWindow* window = nullptr;
    builder->get_widget_derived("window", window);
    return app->run(*window);
}
