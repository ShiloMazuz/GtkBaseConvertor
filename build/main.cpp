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
        set_title("BasedIP");
        set_default_size(300, 100);

        builder->get_widget("grid", grid);
        builder->get_widget("box", box);
        builder->get_widget("entryIpInput", entryIpInput);
        builder->get_widget("entryPrefix", entryPrefix);
        builder->get_widget("labelIpBin", labelIpBin);
        builder->get_widget("labelSubnetMask", labelSubnetMask);
        builder->get_widget("labelNetworkAddress", labelNetworkAddress);
        builder->get_widget("labelBroadcastAddress", labelBroadcastAddress);
        builder->get_widget("labelAvailableHosts", labelAvailableHosts);
        builder->get_widget("buttonIpConvert", buttonIpConvert);
        builder->get_widget("entryHostsWanted", entryHostsWanted);

        buttonIpConvert->signal_clicked().connect(
            [&] {
                labelIpBin->set_markup("<b>Bin IP: </b>" + convertedIpToBin(extractIpFromString(entryIpInput->get_text())));
                if(!(entryHostsWanted->get_text().empty())) {
                    entryPrefix->set_text(hostsToPrefixString(entryHostsWanted->get_text()));
                }
                labelAvailableHosts->set_markup("<b>Available Hosts: </b>" + prefixToHostsString(entryPrefix->get_text()));
                labelSubnetMask->set_markup("<b>Subnet Mask: </b>" + prefixToSubnetString(entryPrefix->get_text()));
                labelNetworkAddress->set_markup("<b>Network Address: </b>" + findNetworkAddress(entryIpInput->get_text(), entryPrefix->get_text()));
                labelBroadcastAddress->set_markup("<b>Broadcast Address: </b>" + findBroadcastAddress(entryIpInput->get_text(), entryPrefix->get_text()));
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
    Gtk::Label* labelNetworkAddress;
    Gtk::Label* labelBroadcastAddress;
    Gtk::Label* labelAvailableHosts;
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
