//Include SFML Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "TitleScreen.h"

using namespace sf;

int main(){
	//Get best video mode supported
	RenderWindow window(VideoMode::getFullscreenModes().front(), "No Stairs");
	TitleScreen title; //Initial starting screen object
	title.display(window); //Display the title screen, if start is selected, you break out of this function within the TitleScreen class


	return 0;
}
