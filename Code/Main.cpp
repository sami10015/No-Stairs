//Include SFML Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <string>
#include "TitleScreen.h"
#include "CustomizationScreen.h"
#include "Player.h"
#include "Chest.h"

using namespace sf;

int main(){
	//Get best video mode supported
	RenderWindow window(VideoMode::getFullscreenModes().front(), "No Stairs");
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
			backgroundSound.setLoop(false);
			backgroundSound.stop();
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
	Player player(custoScreen.getCharTexture());

	//Create Chest object
	Chest chest;

	//Clock for timing everything
	Clock frameClock;

	//Footstep sound
	SoundBuffer footstepBuffer;
	Sound footstepSound;
	footstepBuffer.loadFromFile("Sounds/footstep.wav");
	footstepSound.setBuffer(footstepBuffer);

	//Arrow sound
	SoundBuffer arrowBuffer;
	Sound arrowSound;
	arrowBuffer.loadFromFile("Sounds/arrow.wav");
	arrowSound.setBuffer(arrowBuffer);

	//Chest opening sound
	SoundBuffer chestBuffer;
	Sound chestSound;
	chestBuffer.loadFromFile("Sounds/chest.wav");
	chestSound.setBuffer(chestBuffer);

	//Check if any key was pressed
	bool noKeyWasPressed = true;
	
	//Check if player is moving or shooting, if so play sound
	bool footstepPlaying = false;
	bool arrowPlaying = false;
	bool chestPlaying = false;

	//Check which side the player is facing
	bool facingLeft = false;
	bool facingRight = true;
	
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
		
		//Frame Time
		sf::Time frameTime = frameClock.restart();

		//If a key was pressed set the correct animation and move correctly
		sf::Vector2f movement(0.f, 0.f);

		//Walf Left
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			player.moveLeft();
			movement.x -= player.getSpeed();
            		noKeyWasPressed = false;
			facingLeft = true;
			facingRight = false;
			if(!footstepPlaying){
				footstepSound.play();
				footstepPlaying = true;
			}
		}

		//Walk Right
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			player.moveRight();
			movement.x += player.getSpeed();
			facingLeft = false;
			facingRight = true;
            		noKeyWasPressed = false;
			if(!footstepPlaying){
				footstepSound.play();
				footstepPlaying = true;
			}
		}

		//Shoot Bow and Arrow
		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			if(facingLeft){
				player.shootLeft();
			}else{
				player.shootRight();
			}
			if(!arrowPlaying){
				arrowSound.play();
				arrowSound.setLoop(true);
				arrowPlaying = true;
			}
            		noKeyWasPressed = false;
			footstepSound.stop();
		    	footstepPlaying = false;
		}
		
		//Open Chest
		if (Keyboard::isKeyPressed(Keyboard::G))
		{
			chest.update(frameTime);
			if(!chestPlaying){
				chestSound.play();
				chestPlaying = true;
			}
		}

		chest.play();
		player.play();
		player.move(movement, frameTime.asSeconds());

		//If no key was pressed stop the animation
		if (noKeyWasPressed)
		{
			//Stop player movement
			player.stop();
			//Stop footstep souds
			footstepSound.stop();
			footstepPlaying = false;
			//Stop arrow sounds			
			arrowSound.stop();
			arrowPlaying = false;
			arrowSound.setLoop(false);		
		}
		noKeyWasPressed = true;

		//Update Player and Screen
		player.update(frameTime);
		window.clear();
		window.draw(firstLevelBackgroundSprite);
		window.draw(player.getAnimatedSprite());
		window.draw(chest.getAnimatedSprite());
		window.display();
	}
	return 0;
}
