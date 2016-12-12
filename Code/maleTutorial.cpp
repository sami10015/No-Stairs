#include "maleTutorial.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;

maleTutorial::maleTutorial(RenderWindow& window){
	//Background and bow
	firstLevelBackground.loadFromFile("Graphics/first-level.png");
	bowTexture.loadFromFile("Sprites/bow.png", IntRect(0, 90, 47, 90));	
	firstLevelBackgroundSprite.setTexture(firstLevelBackground);
	bowSprite.setTexture(bowTexture);

	//Fit image onto screen
	firstLevelBackgroundSprite.setScale(
		window.getSize().x / firstLevelBackgroundSprite.getLocalBounds().width,
		window.getSize().y / firstLevelBackgroundSprite.getLocalBounds().height);
	firstLevelBackgroundSprite.setPosition(0,0);
	
	bowSprite.setPosition(window.getSize().x * .5, window.getSize().y * .78);

	//Background sound
	backgroundBuffer.loadFromFile("Sounds/wind.wav");
	backgroundSound.setBuffer(backgroundBuffer);

	//Footstep sound
	footstepBuffer.loadFromFile("Sounds/footstep.wav");
	footstepSound.setBuffer(footstepBuffer);

	//Arrow sound
	arrowBuffer.loadFromFile("Sounds/arrow.wav");
	arrowSound.setBuffer(arrowBuffer);

	//Chest sound
	chestBuffer.loadFromFile("Sounds/chest.wav");
	chestSound.setBuffer(chestBuffer);

	//Pick up sound
	pickUpSoundBuffer.loadFromFile("Sounds/pickup.wav");
	pickUpSound.setBuffer(pickUpSoundBuffer);

	//Play background music
	backgroundSound.setVolume(50);
	backgroundSound.play();
}

void maleTutorial::display(RenderWindow& window, Player player, Chest chest){
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
}
