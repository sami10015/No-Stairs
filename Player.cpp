#include "Player.h"
#include <SFML/Graphics.hpp>

Player::Player(){
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

void Player::spawn(){
	// Place the player to the left
	m_Position.x = 100;
	m_Position.y = 638;
}

void Player::setSprite(Sprite charSprite){
	m_Sprite = charSprite;
}

Sprite Player::getSprite(){
	return m_Sprite;
}

void Player::moveLeft(){
	m_LeftPressed = true;
}

void Player::moveRight(){
	m_RightPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::update(float elapsedTime){
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);
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
