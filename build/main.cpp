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
    {
        set_title("Ip Converter");
        set_default_size(300, 100);

        builder->get_widget("grid", grid);
        builder->get_widget("box", box);
        builder->get_widget("entryIpInput", entryIpInput);
        builder->get_widget("entryPrefix", entryPrefix);
        builder->get_widget("labelIpBin", labelIpBin);
        builder->get_widget("labelSubnetMask", labelSubnetMask);
        builder->get_widget("labelAvilableHosts", labelAvilableHosts);
        builder->get_widget("buttonIpConvert", buttonIpConvert);
        builder->get_widget("entryHostsWanted", entryHostsWanted);

        buttonIpConvert->signal_clicked().connect(
            [&] {
                labelIpBin->set_text("Bin ip: " + convertedIpToBin(extractIpFromString(entryIpInput->get_text())));
                if(!(entryHostsWanted->get_text().empty())) {
                    entryPrefix->set_text(hostsToPrefixString(entryHostsWanted->get_text()));
                }
                labelAvilableHosts->set_text("Avilable Hosts: " + prefixToHostsString(entryPrefix->get_text()));
                labelSubnetMask->set_text("Subnet Mask: " + prefixToSubnetString(entryPrefix->get_text()));
                               }); //I need to figure out what the fuck happens here

        show_all_children();
    }
private:
    Gtk::Grid* grid;
    Glib::RefPtr<Gtk::Adjustment> adjustment;
    Gtk::Box* box;
    Gtk::Entry* entryIpInput;
    Gtk::Entry* entryPrefix;
    Gtk::Label* labelIpBin;
    Gtk::Label* labelSubnetMask;
    Gtk::Label* labelAvilableHosts;
    Gtk::Entry* entryHostsWanted;
    Gtk::Button* buttonIpConvert;
};

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gnome.typeconverter");
    //auto builder = Gtk::Builder::create_from_file("../styling/layout.ui");
    Glib::RefPtr<Gtk::Builder> builder {};
    try {
    builder = Gtk::Builder::create_from_file("/usr/share/basedIP/layout.ui");
    }
    catch(Glib::FileError& error) {
    std::cout << "layout not found at /usr/share/basedIP/layout.ui, trying ../styling/layout.ui";
    builder = Gtk::Builder::create_from_file("../styling/layout.ui");
    }

    MyWindow* window = nullptr;
    builder->get_widget_derived("window", window);
    return app->run(*window);
}
