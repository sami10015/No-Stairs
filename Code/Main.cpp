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
		}//Start game
		else if(num == 5){
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

	//Textures
	Texture firstLevelBackground;
	firstLevelBackground.loadFromFile("Graphics/first-level.png");
	Texture bowTexture;
	bowTexture.loadFromFile("Sprites/bow.png", IntRect(0, 90, 47, 90));

	//Sprites
	Sprite firstLevelBackgroundSprite;
	firstLevelBackgroundSprite.setTexture(firstLevelBackground);
	Sprite bowSprite;
	bowSprite.setTexture(bowTexture);
	

	//Fit image onto screen
	firstLevelBackgroundSprite.setScale(
		window.getSize().x / firstLevelBackgroundSprite.getLocalBounds().width,
		window.getSize().y / firstLevelBackgroundSprite.getLocalBounds().height);
	firstLevelBackgroundSprite.setPosition(0,0);
	
	bowSprite.setPosition(window.getSize().x * .5, window.getSize().y * .78);

	//Create Player object
	Player player(custoScreen.getCharTexture(), window);

	//Create Chest object
	Chest chest(window);

	//Clock for timing everything
	Clock frameClock;
	Clock chestClock;

	//Background sound
	backgroundBuffer.loadFromFile("Sounds/wind.wav");
	backgroundSound.setBuffer(backgroundBuffer);

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

	//Pick up sound
	SoundBuffer pickUpSoundBuffer;
	Sound pickUpSound;
	pickUpSoundBuffer.loadFromFile("Sounds/pickup.wav");
	pickUpSound.setBuffer(pickUpSoundBuffer);

	//Check if any key was pressed
	bool noKeyWasPressed = true;
	
	//Check if player is moving or shooting, if so play sound
	bool footstepPlaying = false;
	bool arrowPlaying = false;
	bool chestPlaying = false;

	//Check which side the player is facing
	bool facingLeft = false;
	bool facingRight = true;

	//Boolean to check if chest is open, and bow is picked up
	bool opened = false;
	bool pickUp = false;

	//Play background music
	backgroundSound.setVolume(50);
	backgroundSound.play();
	
	while(window.isOpen()){
		//Process Event
		Event event;
		
		//Must utilize event instead of isKeyPressed to handle single execution
		while(window.pollEvent(event)){
			switch(event.type){
				case Event::KeyPressed:
					if(event.key.code == Keyboard::Escape){
						backgroundSound.setLoop(false);						
						backgroundSound.stop();
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
			if(pickUp){
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
		}
		
		//Open Chest
		if (Keyboard::isKeyPressed(Keyboard::G))
		{	
			//Check if the player is in range of the chest	
			if(player.getAnimatedSpriteGlobalBounds().intersects(chest.getAnimatedSpriteGlobalBounds()) && !opened){
				chest.update(frameTime, window);
				if(!chestPlaying){
					chestSound.play();
					chestPlaying = true;
				}
				opened = true;			
			}
		}

		chest.play();
		player.play();
		player.move(movement, frameTime.asSeconds());

		if(player.getAnimatedSpriteGlobalBounds().intersects(bowSprite.getGlobalBounds()) && opened && !pickUp){
			pickUpSound.play();			
			pickUp = true;
		}

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
		window.draw(chest.getAnimatedSprite());
		if(!pickUp && opened){
			window.draw(bowSprite);
		}
		window.draw(player.getAnimatedSprite());
		window.display();
	}
	return 0;
}
