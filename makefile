CXX = g++
CXXFLAGS = -std=c++11 - pedantic
CXXLIBS = -lsmfl-graphics -lsfml-window -lsfml-system -lsfml-audio
DEBUGFLAGS = -g -Wall

all: Main

TitleScreen: *.o 
	$(CXX) $< -o $@ $(CXXLIBS)

%.o: %.cpp
	$(CXX) $< -c -o $@

clean:
	rm *.o
