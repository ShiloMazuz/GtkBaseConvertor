CXX = g++
CXXFLAGS = -std=c++17 `pkg-config --cflags gtkmm-3.0`
LDFLAGS = `pkg-config --libs gtkmm-3.0`

SRC = main.cpp converter.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main

all: check-deps $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

install:
	chmod 755 ../misc/converter.desktop
	chmod 644 ../assets/BasedIP.png
	cp ../misc/converter.desktop /usr/share/applications/
	cp ../assets/BasedIP.png /usr/share/icons/hicolor/256x256/apps/
	cp ../build/main /usr/bin/BasedConverter
	mkdir /usr/share/basedIP
	cp ../styling/layout.ui /usr/share/basedIP/
	gtk-update-icon-cache /usr/share/icons/hicolor
	update-desktop-database /usr/share/applications/

uninstall:
	rm -f /usr/share/applications/converter.desktop
	rm -f /usr/share/icons/hicolor/256x256/apps/BasedIP.png
	rm -f /usr/bin/BasedConverter
	rm -rf /usr/share/basedIP
	gtk-update-icon-cache usr/share/icons/hicolor/
	update-desktop-database usr/share/applications/

check-deps:
	@pkg-config --exists gtkmm-3.0 || \
	(echo "Error: gtkmm-3.0 is not installed. Please install libgtkmm-3.0-dev (Debian/Ubuntu) or gtkmm3-devel (Fedora/Arch)." && exit 1)

clean:
	rm -f $(OBJ) $(TARGET)
