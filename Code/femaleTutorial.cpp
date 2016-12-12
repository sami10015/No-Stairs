#include "femaleTutorial.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;

femaleTutorial::femaleTutorial(RenderWindow& window){
	//Background and bow
	firstLevelBackground.loadFromFile("Graphics/background2.png");
	swordTexture.loadFromFile("Sprites/sword.png");	
	firstLevelBackgroundSprite.setTexture(firstLevelBackground);
	swordSprite.setTexture(swordTexture);

	//Fit image onto screen
	firstLevelBackgroundSprite.setScale(
		window.getSize().x / firstLevelBackgroundSprite.getLocalBounds().width,
		window.getSize().y / firstLevelBackgroundSprite.getLocalBounds().height);
	firstLevelBackgroundSprite.setPosition(0,0);
	
	swordSprite.setPosition(window.getSize().x * .5, window.getSize().y * .83);

	//Background sound
	backgroundBuffer.loadFromFile("Sounds/forest.wav");
	backgroundSound.setBuffer(backgroundBuffer);

	//Footstep sound
	footstepBuffer.loadFromFile("Sounds/footstep.wav");
	footstepSound.setBuffer(footstepBuffer);

	//Chest sound
	chestBuffer.loadFromFile("Sounds/chest.wav");
	chestSound.setBuffer(chestBuffer);

	//Pick up sound
	pickUpSoundBuffer.loadFromFile("Sounds/pickup.wav");
	pickUpSound.setBuffer(pickUpSoundBuffer);

	//Play background music
	backgroundSound.play();
}

void femaleTutorial::display(RenderWindow& window, Player player, Chest chest){
	player.setPosition(Vector2f(window.getSize().x * .1,window.getSize().y * .848));
	chest.setPosition(Vector2f(window.getSize().x * .8,window.getSize().y * .82));

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
				chest.setPosition(Vector2f(window.getSize().x * .8,window.getSize().y * .795));
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

		if(player.getAnimatedSpriteGlobalBounds().intersects(swordSprite.getGlobalBounds()) && opened && !pickUp){
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
		}
		noKeyWasPressed = true;

		//Update Player and Screen
		player.update(frameTime);
		window.clear();
		window.draw(firstLevelBackgroundSprite);
		window.draw(chest.getAnimatedSprite());
		if(!pickUp && opened){
			window.draw(swordSprite);
		}
		window.draw(player.getAnimatedSprite());
		window.display();
	}
}
