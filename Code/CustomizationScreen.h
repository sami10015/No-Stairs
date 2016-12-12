#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

using namespace sf;

class CustomizationScreen{
	private:
		//Selection Integers
		int genderSelection = 0; //Choosing gender
		int charSelection = 0; //Choosing sprite

		//Textures
		Texture textureBackground;
		Texture charTexture;

		//Sprites
		Sprite spriteBackground;
		Sprite charSprite;

		//Texts
		Text chooseGender;
		Text Male;
		Text Female;
		Text pressEnter;
		Text navigate;
		Text goBack;
		Text Done;
		
		//Fonts
		Font regularFont;

		//Sounds and sound buffers
		SoundBuffer selectBuffer;
		Sound selection;
		SoundBuffer backgroundBuffer;
		Sound backgroundSound;
	public:
		CustomizationScreen(); //Constructor
		//Integer use to go back and forth between screens
		int display(RenderWindow& window); //Start customization
		int finalize(RenderWindow& window); //Finalize customization
		Sprite getCharSprite(); //Get the Sprite
		Texture& getCharTexture(); //Get the texture
		int getGenderSelection(); //Get the gender
};
