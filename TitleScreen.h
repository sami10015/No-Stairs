#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

class TitleScreen{
	private:
		//Indicates which option is selected in the menu
		int selected = 0; 
		
		//Texture to hold background of title screen
		Texture textureBackground; 
		
		//Sprites
		Sprite spriteBackground;
		
		//Texts to output on the screen
		Text logoText;
		Text startText;
		Text creditsText;
		Text optionText;
		Text quitText;

		//More text for credits function
		Text nameAndDate;
		Text copyright;
		Text maristClass;
		Text backgroundSource;
		Text spriteSource;
		Text fontSource;

		//Fonts for our text
		Font logoFont;
		Font regularFont;

		//Sounds and sound buffers
		SoundBuffer selectBuffer;
		Sound selection;
		SoundBuffer backgroundBuffer;
		Sound backgroundSound;
	public:
		TitleScreen(); //Constructor
		display(RenderWindow& window); //Display the title screen
}
