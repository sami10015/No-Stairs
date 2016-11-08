//Include SFML Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <string>
#include "TitleScreen.h"
#include "CustomizationScreen.h"
#include "Player.h"

using namespace sf;

int main(){
	//Get best video mode supported
	RenderWindow window(VideoMode::getFullscreenModes().front(), "No Stairs");
	TitleScreen title; //Initial starting screen object
	CustomizationScreen custoScreen; //Customization screen object
	int num = title.display(window); //Display the title screen, if start is selected, you break out of this function within the TitleScreen class	
	bool selection = true;
	//This loop allows transition from different objects
	while(selection){
		//End the program from Title Screen
		if(num == 0){
			window.close();
			return 0;
		}//Title Screen to Customization screen
		else if(num == 1){
			window.clear();
			num = custoScreen.display(window);
		}//Customization screen back to title screen
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
		}//Start game
		else if(num == 5){
			window.clear();
			selection = false;
		}
	}

	//Textures
	Texture firstLevelBackground;
	firstLevelBackground.loadFromFile("Graphics/first-level.png");

	//Sprites
	Sprite firstLevelBackgroundSprite;
	firstLevelBackgroundSprite.setTexture(firstLevelBackground);
	//Fit image onto screen
	firstLevelBackgroundSprite.setScale(
		window.getSize().x / firstLevelBackgroundSprite.getLocalBounds().width,
		window.getSize().y / firstLevelBackgroundSprite.getLocalBounds().height);
	firstLevelBackgroundSprite.setPosition(0,0);

	//Create Player object
	Player player;
	player.setSprite(custoScreen.getCharSprite());
	player.spawn();

	//Clock for timing everything
	Clock clock;
	
	while(window.isOpen()){
		//Process Event
		Event event;
		
		//Must utilize event instead of isKeyPressed to handle single execution
		while(window.pollEvent(event)){
			switch(event.type){
				case Event::KeyPressed:
					if(event.key.code == Keyboard::Escape){
						window.close();
					}
					break;
				default:
					break;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			player.moveLeft();
		}
		else
		{
			player.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			player.moveRight();
		}
		else
		{
			player.stopRight();
		}

		Time dt = clock.restart();
		// Make a decimal fraction of 1 from the delta time
		float dtAsSeconds = dt.asSeconds();

		player.update(dtAsSeconds);
		window.clear();
		window.draw(firstLevelBackgroundSprite);
		window.draw(player.getSprite());
		window.display();
	}
	return 0;
}
