CXX = g++
CXXFLAGS = -std=c++17 `pkg-config --cflags gtkmm-3.0`
LDFLAGS = `pkg-config --libs gtkmm-3.0`

SRC = main.cpp converter.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main

DESKTOP_LOCATION = ../misc/converter.desktop
ICON_LOCATION = ../assets/BasedIP.png
BINARY_LOCATION = ../build/main
STYLING_LOCATION = ../styling/layout.ui

DESKTOP_DESTINATION = /usr/share/applications/converter.desktop 
ICON_DESTINATION = /usr/share/icons/hicolor/256x256/apps/BasedIP.png 
BINARY_DESTINATION = /usr/bin/BasedConverter 
STYLING_DESTINATION = /usr/share/basedIP 

all: check-deps $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

install:
	chmod 755 $(DESKTOP_LOCATION)
	chmod 644 $(ICON_LOCATION)
	cp $(DESKTOP_LOCATION) $(DESKTOP_DESTINATION)
	cp $(ICON_LOCATION) $(ICON_DESTINATION)
	cp $(BINARY_LOCATION) $(BINARY_DESTINATION)
	if [ ! -d /usr/share/basedIP/ ]; then mkdir $(STYLING_DESTINATION); fi
	cp $(STYLING_LOCATION) $(STYLING_DESTINATION)

uninstall:
	rm -f $(DESKTOP_DESTINATION)
	rm -f $(ICON_DESTINATION)
	rm -f $(BINARY_DESTINATION)
	rm -rf $(STYLING_DESTINATION)

check-deps:
	@pkg-config --exists gtkmm-3.0 || \
	(echo "Error: gtkmm-3.0 is not installed. Please install libgtkmm-3.0-dev (Debian/Ubuntu) or gtkmm3-devel (Fedora/Arch)." && exit 1)

uninstall_test:
	gtk-update-icon-cache usr/share/icons/hicolor/
	update-desktop-database usr/share/applications/

clean:
	rm -f $(OBJ) $(TARGET)
