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
}
