#include "Chest.h"
#include <SFML/Graphics.hpp>

Chest::Chest(RenderWindow& window){
	//Set up texture
	m_Texture.loadFromFile("Sprites/chest.png");

	//Construct AnimatedSprite object
	animatedSprite = AnimatedSprite(sf::seconds(.001f), true, false);

	//Set up open animation
	openAnimation.setSpriteSheet(m_Texture);
	openAnimation.addFrame(sf::IntRect(3, 47, 94, 88));
	openAnimation.addFrame(sf::IntRect(203, 20, 94, 115));

	//Set Current Animation
	currentAnimation = &openAnimation;

    	//Set up AnimatedSprite
    	animatedSprite.setPosition(sf::Vector2f(window.getSize().x * .8,window.getSize().y * .8));
}

//Play Animated Sprite
void Chest::play(){
	animatedSprite.play(*currentAnimation);
}

//Update Animated Sprite
void Chest::update(Time time, RenderWindow& window){
	animatedSprite.setPosition(sf::Vector2f(window.getSize().x * .8,window.getSize().y * .77));
	animatedSprite.update(time);
}

//Stop the animation
void Chest::stop(){
	animatedSprite.stop();
}

//Return the Animated Sprite	
AnimatedSprite& Chest::getAnimatedSprite(){
	return animatedSprite;
}

//Return Local Bounds
FloatRect Chest::getAnimatedSpriteLocalBounds(){
	return animatedSprite.getLocalBounds();
}

//Return Global Bounds
FloatRect Chest::getAnimatedSpriteGlobalBounds(){
	return animatedSprite.getGlobalBounds();
}
