//Include SFML Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <string>
#include "TitleScreen.h"
#include "CustomizationScreen.h"
#include "Player.h"
#include "Chest.h"
#include "maleTutorial.h"
#include "femaleTutorial.h"

using namespace sf;

int main(){
	//Get best video mode supported
	RenderWindow window(VideoMode::getFullscreenModes().front(), "No Stairs", Style::Fullscreen);
	window.setFramerateLimit(60);
	//Play background sound
	SoundBuffer backgroundBuffer;
	Sound backgroundSound;
	backgroundBuffer.loadFromFile("Sounds/rain.ogg");
	backgroundSound.setBuffer(backgroundBuffer);
	backgroundSound.setLoop(true); //Replay background sound if loop ends
	backgroundSound.play(); //Play sound
	//Initial starting screen object
	TitleScreen title; 
	//Customization screen object
	CustomizationScreen custoScreen; 
	//Display the title screen, if start is selected, you break out of this function within the TitleScreen class	
	int num = title.display(window); 
	bool selection = true;
	//This loop allows transition from different objects
	while(selection){
		//End the program from Title Screen
		if(num == 0){
			window.close();
			backgroundSound.setLoop(false);
			backgroundSound.stop();
			return 0;
		}//Title Screen to Customization screen
		else if(num == 1){
			window.clear();
			num = custoScreen.display(window);
		}//Customization screen/Options screen back to title screen
		else if(num == 2){
			window.clear();
			num = title.display(window);
		}//Customization screen to finalize screen
		else if(num == 3){
			window.clear();
			num = custoScreen.finalize(window);
		}//Finalize screen to customization screen
		else if(num == 4){
			window.clear();
			num = custoScreen.display(window);
		}//Start game(8 for female tutorial, 5 for male)
		else if(num == 5 || num == 8){
			window.clear();
			backgroundSound.setLoop(false);
			backgroundSound.stop();
			selection = false;
		}//Options
		else if(num == 6){
			window.clear();
			num = title.options(window);
		}//Credits
		else if(num == 7){
			//Stop music and clear screen
			window.clear();
			backgroundSound.setLoop(false);
			backgroundSound.stop();

			//Play song for credits(I use music for speed purposes)
			Music creditsSound;
			creditsSound.openFromFile("Sounds/credits.wav");
			creditsSound.play();		
			title.credits(window);
			creditsSound.stop();
			return 0;
		}
	}
	//Create Player object
	Player player(custoScreen.getCharTexture(), window, custoScreen.getGenderSelection());

	//Create Chest object
	Chest chest(window);
	
	if(num == 5){//Male Tutorial Level
		maleTutorial firstLevel(window);
		firstLevel.display(window, player, chest);
	}else{//Female Tutorial Level
		femaleTutorial firstLevel(window);
		firstLevel.display(window, player, chest);
	}

	//Continue here for future fun!
	return 0;
}
