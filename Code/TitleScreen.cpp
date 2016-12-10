#include "TitleScreen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

//Constructor
//Setting textures, sprites, etc for display
TitleScreen::TitleScreen(){
	textureBackground.loadFromFile("Graphics/background.jpg");

	spriteBackground.setTexture(textureBackground);
	
	spriteBackground.setPosition(0,0); //Cover screen for background
	
	logoFont.loadFromFile("Fonts/SEASRN__.ttf");
	regularFont.loadFromFile("Fonts/ostrich-regular.ttf");

	//Set the font to text messages
	logoText.setFont(logoFont);
	startText.setFont(regularFont);
	creditsText.setFont(regularFont);
	optionText.setFont(regularFont);
	quitText.setFont(regularFont);

	//Assign message, size, and color of text
	logoText.setString("NO STAIRS");
	logoText.setCharacterSize(200);
	logoText.setFillColor(Color::Red);

	startText.setString("START");
	startText.setCharacterSize(150);

	creditsText.setString("CREDITS");
	creditsText.setCharacterSize(150);

	optionText.setString("OPTIONS");
	optionText.setCharacterSize(150);

	quitText.setString("QUIT");
	quitText.setCharacterSize(150);

	//Sounds
	selectBuffer.loadFromFile("Sounds/button-21.wav");
	selection.setBuffer(selectBuffer);
}

int TitleScreen::display(RenderWindow& window){
	//Fit image onto screen
	spriteBackground.setScale(
		window.getSize().x / spriteBackground.getLocalBounds().width,
		window.getSize().y / spriteBackground.getLocalBounds().height);

	//Sets text in the middle of the screen
	FloatRect textRect = logoText.getLocalBounds();
	logoText.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	logoText.setPosition(window.getSize().x / 2.0f, window.getSize().y * .25f);

	startText.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	//Here I use 1.4 instead of 1.5 for half so it visually looks in the middle of the logo
	startText.setPosition(logoText.getPosition().x * 1.4f, window.getSize().y * .45f);

	creditsText.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	//Here I use 1.4 instead of 1.5 for half so it visually looks in the middle of the logo
	creditsText.setPosition(logoText.getPosition().x * 1.4f, window.getSize().y * .60f);

	optionText.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	//Here I use 1.4 instead of 1.5 for half so it visually looks in the middle of the logo
	optionText.setPosition(logoText.getPosition().x * 1.4f, window.getSize().y * .75f);

	quitText.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	//Here I use 1.4 instead of 1.5 for half so it visually looks in the middle of the logo
	quitText.setPosition(logoText.getPosition().x * 1.4f, window.getSize().y * .90f);

	bool playSelected = false; 
	
	//Game Loop
	while(window.isOpen()){
		//Process Event
		Event event;
		
		//Must utilize event instead of isKeyPressed to handle single execution
		while(window.pollEvent(event)){
			switch(event.type){
				case Event::KeyPressed:
					if(event.key.code == Keyboard::Down){
						if(selected < 3){
							selected++;
							selection.play();
						}
					}
					if(event.key.code == Keyboard::Up){
						if(selected > 0){
							selected--;
							selection.play();
						}
					}
					if(event.key.code == Keyboard::Return){
						if(selected == 2){
							selection.play();
							return 6;
						}else if(selected == 1){
							selection.play();
							return 7;
						}else if(selected == 0){
							selection.play();
							playSelected = true; //Break out of title screen
						}
					}
					if(event.key.code == Keyboard::Escape){
						selection.play();
						window.close();
						return 0;
					}		
					break;
				default:
					break;
			}
		}
		
		if(Keyboard::isKeyPressed(Keyboard::Return)){
			//Quit			
			if(selected == 3){
				selection.play();
				window.close();
				return 0;
			}
		}		

		//Update the scene

		//Draw the scene(Order matters)
		window.clear();
		
		//Indicate which option is selected
		if(selected == 3){
			startText.setFillColor(Color::White);
			creditsText.setFillColor(Color::White);
			optionText.setFillColor(Color::White);
			quitText.setFillColor(Color::Red);	
		}
		if(selected == 2){
			startText.setFillColor(Color::White);
			creditsText.setFillColor(Color::White);
			optionText.setFillColor(Color::Red);
			quitText.setFillColor(Color::White);
		}
		if(selected == 1){
			startText.setFillColor(Color::White);
			creditsText.setFillColor(Color::Red);
			optionText.setFillColor(Color::White);
			quitText.setFillColor(Color::White);
		}
		if(selected == 0){
			startText.setFillColor(Color::Red);
			creditsText.setFillColor(Color::White);
			optionText.setFillColor(Color::White);
			quitText.setFillColor(Color::White);
		}
		
		//Break out of class and start the game
		if(playSelected){
			return 1;
			break;
		}

		window.draw(spriteBackground);
		window.draw(logoText);
		window.draw(startText);
		window.draw(creditsText);
		window.draw(optionText);
		window.draw(quitText);		

		//Show everything we just drew
		window.display();
	}
}

void TitleScreen::credits(RenderWindow& window){
	//Clear initial window	
	window.clear();

	//Clock to adjust positioning
	Clock clock;

	regularFont.loadFromFile("Fonts/ostrich-regular.ttf");

	//Set font to messages
	nameAndDate.setFont(regularFont);
	copyright.setFont(regularFont);
	maristClass.setFont(regularFont);
	backgroundSource.setFont(regularFont);
	spriteSource.setFont(regularFont);
	fontSource.setFont(regularFont);

	//Assign messages to text
	nameAndDate.setString("Sami Ellougani - 10/25/2016");
	nameAndDate.setCharacterSize(150);
	nameAndDate.setPosition(window.getSize().x / 5.0f, window.getSize().y + 100);

	copyright.setString("Copyright: Copyright 2016 Sami J. Ellougani");
	copyright.setCharacterSize(75);
	copyright.setPosition(window.getSize().x / 5.0f, window.getSize().y + 300);

	maristClass.setString("Marist College Game Design + Programming Final Project");
	maristClass.setCharacterSize(75);
	maristClass.setPosition(window.getSize().x / 5.0f, window.getSize().y + 400);

	backgroundSource.setString("Background Source: The Horror Movies Blog");
	backgroundSource.setCharacterSize(75);
	backgroundSource.setPosition(window.getSize().x / 5.0f, window.getSize().y + 500);

	spriteSource.setString("Sprite Source: SpriteCow");
	spriteSource.setCharacterSize(75);
	spriteSource.setPosition(window.getSize().x / 5.0f, window.getSize().y + 600);

	fontSource.setString("Font Source: Font Squirrel");
	fontSource.setCharacterSize(75);
	fontSource.setPosition(window.getSize().x / 5.0f, window.getSize().y + 700);

	//Set scrolling variable
	bool scrolling = true;
	while(scrolling){
		//Process Event
		Event event;
		
		//Must utilize event instead of isKeyPressed to handle single execution
		while(window.pollEvent(event)){
			switch(event.type){
				case Event::KeyPressed:
					if(event.key.code == Keyboard::Return){
						scrolling = false;
						selection.play();
						break;
					}
					if(event.key.code == Keyboard::Escape){
						scrolling = false;
						selection.play();
						break;
					}
					break;
				default:
					break;
			}
		}
		
		//Utilize clock for frame rate issues
		Time dt = clock.restart();

		//Move text upward
		nameAndDate.setPosition(
			nameAndDate.getPosition().x,
			nameAndDate.getPosition().y -
			(textSpeed * dt.asSeconds()));

		copyright.setPosition(
			copyright.getPosition().x,
			copyright.getPosition().y -
			(textSpeed * dt.asSeconds()));

		maristClass.setPosition(
			maristClass.getPosition().x,
			maristClass.getPosition().y -
			(textSpeed * dt.asSeconds()));

		backgroundSource.setPosition(
			backgroundSource.getPosition().x,
			backgroundSource.getPosition().y -
			(textSpeed * dt.asSeconds()));

		spriteSource.setPosition(
			spriteSource.getPosition().x,
			spriteSource.getPosition().y -
			(textSpeed * dt.asSeconds()));

		fontSource.setPosition(
			fontSource.getPosition().x,
			fontSource.getPosition().y -
			(textSpeed * dt.asSeconds()));
	
		window.clear();
		window.draw(spriteBackground);
		window.draw(nameAndDate);
		window.draw(copyright);
		window.draw(maristClass);
		window.draw(backgroundSource);
		window.draw(spriteSource);
		window.draw(fontSource);
		window.display();
	}
	window.close();
}

int TitleScreen::options(RenderWindow& window){
	//Clear initial window	
	window.clear();

	//Set Fonts to all Text
	fullscreen.setFont(regularFont);
	windowed.setFont(regularFont);

	//Assign messages to text
	fullscreen.setString("FullScreen Mode");
	fullscreen.setCharacterSize(150);
	windowed.setString("Windowed Mode");
	windowed.setCharacterSize(150);
	
	//Use logo to place correctly
	FloatRect textRect = logoText.getLocalBounds();

	fullscreen.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	//Here I use 1.4 instead of 1.5 for half so it visually looks in the middle of the logo
	fullscreen.setPosition(logoText.getPosition().x * 1.2f, window.getSize().y * .50f);
	fullscreen.setFillColor(Color::Red);

	windowed.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	//Here I use 1.4 instead of 1.5 for half so it visually looks in the middle of the logo
	windowed.setPosition(logoText.getPosition().x * 1.2f, window.getSize().y * .65f);
	windowed.setFillColor(Color::White);

	int select = 0;

	while(window.isOpen()){
		//Process Event
		Event event;
		
		//Must utilize event instead of isKeyPressed to handle single execution
		while(window.pollEvent(event)){
			switch(event.type){
				case Event::KeyPressed:
					if(event.key.code == Keyboard::Return){
						if(select == 0){//Fullscreen mode
							window.create(VideoMode::getFullscreenModes().front(), "No Stairs", Style::Fullscreen);
							selection.play();
						}else{//Windowed mode
							window.create(VideoMode::getFullscreenModes().front(), "No Stairs");
							selection.play();
						}
					}
					//Return back to title screen
					if(event.key.code == Keyboard::Escape){
						selection.play();
						return 2;
					}
					if(event.key.code == Keyboard::Up){
						if(select > 0){
							select--;
						}						
					}
					if(event.key.code == Keyboard::Down){
						if(select < 1){
							select++;
						}
					}
					break;
				default:
					break;
			}
		}
		if(select == 0){
			fullscreen.setFillColor(Color::Red);
			windowed.setFillColor(Color::White);
		}else{
			fullscreen.setFillColor(Color::White);
			windowed.setFillColor(Color::Red);
		}
		window.clear();
		window.draw(spriteBackground);
		window.draw(fullscreen);
		window.draw(windowed);
		window.display();
	}

}

