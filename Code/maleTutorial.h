#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AnimatedSprite.hpp"
#include "Player.h"
#include "Chest.h"
#include <sstream>

using namespace sf;

class maleTutorial{
	private:
		//Textures
		Texture firstLevelBackground;
		Texture bowTexture;
		
		//Sprites
		Sprite firstLevelBackgroundSprite;
		Sprite bowSprite;	

		//Clock
		Clock frameClock;

		//Sounds for level
		SoundBuffer backgroundBuffer;
		Sound backgroundSound;
		
		SoundBuffer arrowBuffer;
		Sound arrowSound;

		SoundBuffer chestBuffer;
		Sound chestSound;
		
		SoundBuffer pickUpSoundBuffer;
		Sound pickUpSound;

		SoundBuffer footstepBuffer;
		Sound footstepSound;

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
	public:
		maleTutorial(RenderWindow& window);
		void display(RenderWindow& window, Player player, Chest chest); 
};

