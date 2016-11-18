#include "CustomizationScreen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;

//Constructor
//Setting textures, sprites, etc for display
CustomizationScreen::CustomizationScreen(){
	textureBackground.loadFromFile("Graphics/background.jpg");

	spriteBackground.setTexture(textureBackground);
	
	spriteBackground.setPosition(0,0); //Cover screen for background
	
	regularFont.loadFromFile("Fonts/ostrich-regular.ttf");

	//Set the font to text messages
	chooseGender.setFont(regularFont);
	Male.setFont(regularFont);
	Female.setFont(regularFont);
	pressEnter.setFont(regularFont);
	goBack.setFont(regularFont);
	navigate.setFont(regularFont);

	
	//Assign messages, size, and color of texts
	chooseGender.setString("CHOOSE GENDER");
	chooseGender.setCharacterSize(250);
	chooseGender.setFillColor(Color::White);

	Male.setString("MALE");
	Male.setCharacterSize(200);
	Male.setFillColor(Color::Red);

	Female.setString("FEMALE");
	Female.setCharacterSize(200);
	Female.setFillColor(Color::White);

	pressEnter.setString("ENTER TO CONTINUE");
	pressEnter.setCharacterSize(100);
	pressEnter.setFillColor(Color::White);

	goBack.setString("ESCAPE TO GO BACK");
	goBack.setCharacterSize(200);
	goBack.setFillColor(Color::White);

	navigate.setString("CHOOSE (LEFT/RIGHT)");
	navigate.setCharacterSize(250);
	navigate.setFillColor(Color::White);	
}

int CustomizationScreen::display(RenderWindow& window){
	window.clear();
	//Fit image onto screen
	spriteBackground.setScale(
		window.getSize().x / spriteBackground.getLocalBounds().width,
		window.getSize().y / spriteBackground.getLocalBounds().height);

	//Sets text in the middle of the screen
	FloatRect textRect = chooseGender.getLocalBounds();
	chooseGender.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	chooseGender.setPosition(window.getSize().x / 2.0f, window.getSize().y * .25f);

	Male.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	//Here I use 1.4 instead of 1.5 for half so it visually looks in the middle of the logo
	Male.setPosition(chooseGender.getPosition().x * 1.4f, window.getSize().y * .50f);

	Female.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	//Here I use 1.4 instead of 1.5 for half so it visually looks in the middle of the logo
	Female.setPosition(chooseGender.getPosition().x * 1.345f, window.getSize().y * .70f);

	pressEnter.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	//Here I use 1.4 instead of 1.5 for half so it visually looks in the middle of the logo
	pressEnter.setPosition(chooseGender.getPosition().x * 1.265f, window.getSize().y * .99f);

	//Preparing the sound
	selectBuffer.loadFromFile("Sounds/button-21.wav");
	selection.setBuffer(selectBuffer);

	//Game Loop
	while(window.isOpen()){
		//Process Event
		Event event;
		
		//Must utilize event instead of isKeyPressed to handle single execution
		while(window.pollEvent(event)){
			switch(event.type){
				case Event::KeyPressed:
					if(event.key.code == Keyboard::Down){
						if(genderSelection < 1){
							genderSelection++;
							selection.play();
						}
					}
					if(event.key.code == Keyboard::Up){
						if(genderSelection > 0){
							genderSelection--;
							selection.play();
						}
					}
					if(event.key.code == Keyboard::Escape){
						selection.play();
						return 2;
					}
					if(event.key.code == Keyboard::Return){
						selection.play();						
						return 3;
					}		
					break;
				default:
					break;
			}
		}		

		//Update the scene

		//Draw the scene(Order matters)
		window.clear();
		
		//Indicate which option is selected
		if(genderSelection == 1){
			Male.setFillColor(Color::White);
			Female.setFillColor(Color::Red);	
		}
		if(genderSelection == 0){
			Male.setFillColor(Color::Red);
			Female.setFillColor(Color::White);	
		}

		window.draw(spriteBackground);
		window.draw(chooseGender);
		window.draw(Male);
		window.draw(Female);
		window.draw(pressEnter);		

		//Show everything we just drew
		window.display();
	}
}

int CustomizationScreen::finalize(RenderWindow& window){
	//Girl sprites location directory
	String girl1LoadDir = "Sprites/girl-1.png";
	String girl2LoadDir = "Sprites/girl-2.png";

	String boy1LoadDir = "Sprites/player.png";

	//Textures for sprites
	if(genderSelection == 1){ //Female
		charTexture.loadFromFile(girl1LoadDir);
	}else{ //Male
		charTexture.loadFromFile(boy1LoadDir);
	}
	
	
	//Sprites
	charSprite.setTexture(charTexture);
	charSprite.setTextureRect(IntRect(17, 141, 30, 49));
	charSprite.setScale(charSprite.getScale().x * 4, charSprite.getScale().y * 4);
	charSprite.setPosition(window.getSize().x / 2.15f, window.getSize().y * .40f);
	
	window.clear();
	//Fit image onto screen
	spriteBackground.setScale(
		window.getSize().x / spriteBackground.getLocalBounds().width,
		window.getSize().y / spriteBackground.getLocalBounds().height);

	//Sets text in the middle of the screen
	FloatRect textRect = navigate.getLocalBounds();
	navigate.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	navigate.setPosition(window.getSize().x / 2.0f, window.getSize().y * .25f);

	//Preparing the sound
	selectBuffer.loadFromFile("Sounds/button-21.wav");
	selection.setBuffer(selectBuffer);

	//Game Loop
	while(window.isOpen()){
		//Process Event
		Event event;
		
		//Must utilize event instead of isKeyPressed to handle single execution
		while(window.pollEvent(event)){
			switch(event.type){
				case Event::KeyPressed:
					if(event.key.code == Keyboard::Right){
						//Female
						if(genderSelection == 1){
							if(charSelection < 1){
								charSelection++;
								charTexture.loadFromFile(girl2LoadDir);
								charSprite.setTexture(charTexture);
								selection.play();
							}
						}else{ //Male
							charTexture.loadFromFile(boy1LoadDir);
							charSprite.setTexture(charTexture);
							charSprite.setTextureRect(IntRect(17, 141, 30, 49));
							selection.play();
						}
					}
					if(event.key.code == Keyboard::Left){
						//Female
						if(genderSelection == 1){
							if(charSelection > 0){
								charSelection--;
								charTexture.loadFromFile(girl1LoadDir);
								charSprite.setTexture(charTexture);
								selection.play();
							}
						}else{ //Male
							charTexture.loadFromFile(boy1LoadDir);
							charSprite.setTexture(charTexture);
							charSprite.setTextureRect(IntRect(17, 141, 30, 49));
							selection.play();
						}
					}
					if(event.key.code == Keyboard::Escape){
						selection.play();
						return 4;
					}
					if(event.key.code == Keyboard::Return){
						selection.play();						
						return 5;
					}		
					break;
				default:
					break;
			}
		}		

		//Update the scene

		//Draw the scene(Order matters)
		window.clear();

		window.draw(spriteBackground);
		window.draw(navigate);
		window.draw(charSprite);
		window.draw(pressEnter);		

		//Show everything we just drew
		window.display();
	}
}

Sprite CustomizationScreen::getCharSprite(){
	return charSprite;
}

Texture CustomizationScreen::getCharTexture(){
	return charTexture;
}
