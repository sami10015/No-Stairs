CXX = g++
CXXFLAGS = -std=c++11 - pedantic
CXXLIBS = -lsmfl-graphics -lsfml-window -lsfml-system -lsfml-audio
DEBUGFLAGS = -g -Wall

all: sfml-app

Main: Main.o Player.o TitleScreen.o CustomizationScreen.o 
	$(CXX) $< -o $@ $(CXXLIBS)

%.o: %.cpp
	$(CXX) $< -c -o $@

clean:
	rm *.o
