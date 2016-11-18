#include "Player.h"
#include <SFML/Graphics.hpp>

Player::Player(Texture& texture){
	//Set up Player Stats
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	//Set up Left Walking Animation
	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.setSpriteSheet(texture);
    	walkingAnimationLeft.addFrame(sf::IntRect(22, 590, 21, 48));
    	walkingAnimationLeft.addFrame(sf::IntRect(83, 591, 25, 47));
    	walkingAnimationLeft.addFrame(sf::IntRect(149, 590, 22, 47));
    	walkingAnimationLeft.addFrame(sf::IntRect(214, 590, 23, 47));
    	walkingAnimationLeft.addFrame(sf::IntRect(278, 590, 24, 48));
    	walkingAnimationLeft.addFrame(sf::IntRect(340, 591, 28, 47));
    	walkingAnimationLeft.addFrame(sf::IntRect(406, 590, 24, 48));
    	walkingAnimationLeft.addFrame(sf::IntRect(470, 590, 23, 48));
    	walkingAnimationLeft.addFrame(sf::IntRect(534, 590, 22, 48));

	//Set up Right Walking Animation
	walkingAnimationRight.setSpriteSheet(texture);
    	walkingAnimationRight.addFrame(sf::IntRect(21, 718, 21, 48));
    	walkingAnimationRight.addFrame(sf::IntRect(84, 719, 25, 47));
    	walkingAnimationRight.addFrame(sf::IntRect(149, 718, 22, 47));
    	walkingAnimationRight.addFrame(sf::IntRect(211, 718, 23, 47));
    	walkingAnimationRight.addFrame(sf::IntRect(274, 718, 24, 48));
    	walkingAnimationRight.addFrame(sf::IntRect(336, 719, 28, 47));
    	walkingAnimationRight.addFrame(sf::IntRect(402, 718, 24, 48));
    	walkingAnimationRight.addFrame(sf::IntRect(467, 718, 23, 48));
    	walkingAnimationRight.addFrame(sf::IntRect(532, 718, 22, 48));

	//Set current animation
	currentAnimation = &walkingAnimationLeft;

    	// set up AnimatedSprite
    	animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));
}

void Player::moveLeft(){
	currentAnimation = &walkingAnimationLeft;
}

void Player::moveRight(){
	currentAnimation = &walkingAnimationRight;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::update(Time time){
	animatedSprite.update(time);
}

void Player::upgradeSpeed()
{
	// 20% speed upgrade
	m_Speed += (START_SPEED * .2);
}

void Player::upgradeHealth()
{
	// 20% max health upgrade
	m_MaxHealth += (START_HEALTH * .2);

}

void Player::increaseHealthLevel(int amount)
{
	m_Health += amount;

	// But not beyond the maximum
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}

void Player::play()
{
	animatedSprite.play(currentAnimation);
}

void Player::move(Vector2f movement, float seconds)
{
	animatedSprite.move(movement * seconds);
}

void Player::stop(){
	animatedSprite.stop();
}
