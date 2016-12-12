#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <iostream>

using namespace sf;

class Chest{
	private:	
		//Texture
		Texture m_Texture;

		//Animation
		Animation openAnimation;
		Animation* currentAnimation;
		AnimatedSprite animatedSprite;

	public:
		//Constructor
		Chest(RenderWindow& window);

		//Play Opening Animation
		void play();

		//Update the Animation
		void update(Time time, RenderWindow& window);

		//Stop the animation
		void stop();

		//Return the Animated Sprite object
		AnimatedSprite& getAnimatedSprite();

		//Return Local and Global bounds of Animated Sprite
		FloatRect getAnimatedSpriteLocalBounds();
		FloatRect getAnimatedSpriteGlobalBounds();

		//Set position of chest
		void setPosition(Vector2f vector);
};
