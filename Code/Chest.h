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
		Chest();

		//Play Opening Animation
		void play();

		//Update the Animation
		void update(Time time);

		//Stop the animation
		void stop();

		//Return the Animated Sprite object
		AnimatedSprite& getAnimatedSprite();
};
