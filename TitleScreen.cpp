//Include SFML Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

using namespace sf;

//Use reference to allow manipulation of the same window, and also more efficient
void credits(RenderWindow& window){
	//Clear initial window	
	window.clear();

	//Speed of text and clock to adjust positioning
	int textSpeed = 100;
	Clock clock;
	
	//Texture to hold background
	Texture textureBackground;
	textureBackground.loadFromFile("Graphics/background.jpg");
	
	//Sprites
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0,0);

	//Texts
	Text nameAndDate;
	Text copyright;
	Text maristClass;
	Text backgroundSource;
	Text spriteSource;
	Text fontSource;

	//Fonts
	Font regularFont;
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

	//Selection sound
	SoundBuffer selectBuffer;
	selectBuffer.loadFromFile("Sounds/button-21.wav");
	Sound selection;
	selection.setBuffer(selectBuffer);

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
}

int main(){
	//Get best video mode supported
	RenderWindow window(VideoMode::getFullscreenModes().front(), "No Stairs");

	//Indicates which option is selected in the menu
	int selected = 0;
	
	//Texture to hold background of title screen
	Texture textureBackground;
	textureBackground.loadFromFile("Graphics/background.jpg");

	//Sprites to hold textures
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0,0); //Cover screen for background
	
	//Texts to output on the screen
	Text logoText;
	Text startText;
	Text creditsText;
	Text optionText;
	Text quitText;

	//Fonts for our text
	Font logoFont;
	Font regularFont;
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

	//Position of texts

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
	startText.setPosition(logoText.getPosition().x * 1.4f, window.getSize().y * .50f);

	creditsText.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	//Here I use 1.4 instead of 1.5 for half so it visually looks in the middle of the logo
	creditsText.setPosition(logoText.getPosition().x * 1.4f, window.getSize().y * .65f);

	optionText.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	//Here I use 1.4 instead of 1.5 for half so it visually looks in the middle of the logo
	optionText.setPosition(logoText.getPosition().x * 1.4f, window.getSize().y * .80f);

	quitText.setOrigin(textRect.left +
 		textRect.width / 2.0f,
 		textRect.top +
 		textRect.height / 2.0f);
	//Here I use 1.4 instead of 1.5 for half so it visually looks in the middle of the logo
	quitText.setPosition(logoText.getPosition().x * 1.4f, window.getSize().y * .95f);

	//Preparing the sound

	//Selection sound
	SoundBuffer selectBuffer;
	selectBuffer.loadFromFile("Sounds/button-21.wav");
	Sound selection;
	selection.setBuffer(selectBuffer);

	//Background sound
	SoundBuffer backgroundBuffer;
	backgroundBuffer.loadFromFile("Sounds/rain.ogg");
	Sound backgroundSound;
	backgroundSound.setBuffer(backgroundBuffer);
	backgroundSound.setLoop(true); //Replay background sound if loop ends
	backgroundSound.play(); //Play sound 
	
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
						if(selected == 1){
							credits(window);
							selection.play();
						}
					}
					if(event.key.code == Keyboard::Escape){
						selection.play();
						window.close();
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

		window.draw(spriteBackground);
		window.draw(logoText);
		window.draw(startText);
		window.draw(creditsText);
		window.draw(optionText);
		window.draw(quitText);		

		//Show everything we just drew
		window.display();
	}

	return 0;
}
