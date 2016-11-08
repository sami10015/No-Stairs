#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player{
	private:
		const float START_SPEED = 200;
		const float START_HEALTH = 100;

		//Sprite
		Sprite m_Sprite;

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
		Player();

		//Spawn the sprite
		void spawn();
		
		//Choose Sprite from customization menu
		void setSprite(Sprite charSprite);

		//Send a copy of the sprite to main
		Sprite getSprite();

		//The next four function move the player
		void moveLeft();
		void moveRight();

		//Stop the player moving in a specific direction
		void stopLeft();
		void stopRight();

		//Call this function once every frame
		void update(float elapsedTime);

		//Give player a speed boost
		void upgradeSpeed();

		//Give the player some health
		void upgradeHealth();

		//Increase max health player can have
		void increaseHealthLevel(int amount);		
};
