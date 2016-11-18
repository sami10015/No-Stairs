#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"

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
		Animation walkingAnimationRight
		Animation* currentAnimation;
		AnimatedSprite animatedSprite(sf::seconds(0.15), true, false);

		//Screen resolution
		Vector2f m_Resolution;

		//Position
		Vector2f m_Position;

		//Directions player is moving in(Left and right for now due to side scrolling)
		bool m_LeftPressed;
		bool m_RightPressed;

		//Health
		int m_Health;
		int m_MaxHealth; //Max health the player can have

		//Speed in pixels per second
		float m_Speed;
	public:
		//Constructor
		Player(Texture& texture);

		//The next four function move the player
		void moveLeft();
		void moveRight();

		//Stop the player moving in a specific direction
		void stopLeft();
		void stopRight();

		//Call this function once every frame
		void update(Time time);

		//Give player a speed boost
		void upgradeSpeed();

		//Give the player some health
		void upgradeHealth();

		//Increase max health player can have
		void increaseHealthLevel(int amount);

		void play();

		void move(Vector2f movement, float seconds);

		void stop();	
};
