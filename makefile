CXX = g++
CXXFLAGS = -std=c++11 - pedantic
CXXLIBS = -lsmfl-graphics -lsfml-window -lsfml-system
DEBUGFLAGS = -g -Wall

all: Timber

TitleScreen: code/TitleScreen.o
	$(CXX) $< -o $@ $(CXXLIBS)

code/%.o: %.cpp
	$(CXX) $< -c -o $@

clean:
	rm TitleScreen code/*.o
