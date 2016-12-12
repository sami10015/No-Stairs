#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <iostream>

using namespace sf;

class Player{
	private:
		const float START_SPEED = 140.f;
		const float START_HEALTH = 100;

		//Sprite
		Sprite m_Sprite;

		//Texture
		Texture playerTexture;

		//Animation
		Animation walkingAnimationLeft;
		Animation walkingAnimationRight;
		Animation shootAnimationLeft;
		Animation shootAnimationRight;
		Animation* currentAnimation;
		AnimatedSprite animatedSprite;

		//Health
		int m_Health;
		int m_MaxHealth; //Max health the player can have

		//Speed in pixels per second
		float m_Speed;
	public:
		//Constructor
		Player(Texture& texture, RenderWindow& window, int genderSelection);

		//The next four function move the player animation
		void moveLeft();
		void moveRight();

		//Shoot animation function
		void shootLeft();
		void shootRight();

		//Call this function once every frame
		void update(Time time);

		//Give player a speed boost
		void upgradeSpeed();

		//Give the player some health
		void upgradeHealth();

		//Increase max health player can have
		void increaseHealthLevel(int amount);

		//Play the animated sprite
		void play();

		//Move the animated sprite
		void move(Vector2f movement, float seconds);

		//Stop moving the animated sprite
		void stop();

		//Return the animated sprite
		AnimatedSprite& getAnimatedSprite();

		//Get the speed of the character
		float getSpeed();

		//Return Local and Global bounds of Animated Sprite
		FloatRect getAnimatedSpriteLocalBounds();
		FloatRect getAnimatedSpriteGlobalBounds();

		//Set position
		void setPosition(Vector2f vector);	
};
