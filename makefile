CXX = g++
CXXFLAGS = -std=c++11 - pedantic
CXXLIBS = -lsmfl-graphics -lsfml-window -lsfml-system -lsfml-audio
DEBUGFLAGS = -g -Wall

all: Main

TitleScreen: Main.o TitleScreen.o
	$(CXX) $< -o $@ $(CXXLIBS)

code/%.o: %.cpp
	$(CXX) $< -c -o $@

clean:
	rm TitleScreen code/*.o
