CXX = g++
CXXFLAGS = -std=c++17 `pkg-config --cflags gtkmm-3.0`
LDFLAGS = `pkg-config --libs gtkmm-3.0`

SRC = main.cpp converter.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main

all: $(TARGET)

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
	gtk-update-icon-cache /usr/share/icons/hicolor
	update-desktop-database /usr/share/applications/

uninstall:
	rm -f /usr/share/applications/converter.desktop
	rm -f /usr/share/icons/hicolor/256x256/apps/BasedIP.png
	rm -f /usr/bin/BasedConverter
	gtk-update-icon-cache usr/share/icons/hicolor/
	update-desktop-database usr/share/applications/

clean:
	rm -f $(OBJ) $(TARGET)
