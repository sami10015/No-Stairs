#include "Player.h"
#include <SFML/Graphics.hpp>

//Constructor
Player::Player(Texture& texture, RenderWindow& window, int genderSelection){
	//Set up Player Stats
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	//Construct AnimatedSprite object
	animatedSprite = AnimatedSprite(sf::seconds(0.1), true, false);
	
	//Male
	if(genderSelection == 0){
		//Set up Left Walking Animation
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

		//Set up Left Shooting Animation
		shootAnimationLeft.setSpriteSheet(texture);
		shootAnimationLeft.addFrame(sf::IntRect(7, 1102, 44, 48));
		shootAnimationLeft.addFrame(sf::IntRect(76, 1102, 37, 48));
		shootAnimationLeft.addFrame(sf::IntRect(136, 1102, 39, 48));
		shootAnimationLeft.addFrame(sf::IntRect(201, 1102, 39, 48));
		shootAnimationLeft.addFrame(sf::IntRect(261, 1100, 43, 50));
		shootAnimationLeft.addFrame(sf::IntRect(320, 1097, 44, 53));
		shootAnimationLeft.addFrame(sf::IntRect(385, 1095, 45, 55));
		shootAnimationLeft.addFrame(sf::IntRect(452, 1097, 45, 53));
		shootAnimationLeft.addFrame(sf::IntRect(519, 1101, 44, 49));
		shootAnimationLeft.addFrame(sf::IntRect(589, 1099, 35, 51));
		shootAnimationLeft.addFrame(sf::IntRect(653, 1099, 34, 51));
		shootAnimationLeft.addFrame(sf::IntRect(717, 1099, 31, 51));
		shootAnimationLeft.addFrame(sf::IntRect(776, 1099, 39, 51));

		//Set up Right Shooting Animation
		shootAnimationRight.setSpriteSheet(texture);
		shootAnimationRight.addFrame(sf::IntRect(13, 1230, 44, 48));
		shootAnimationRight.addFrame(sf::IntRect(79, 1230, 37, 48));
		shootAnimationRight.addFrame(sf::IntRect(145, 1230, 39, 48));
		shootAnimationRight.addFrame(sf::IntRect(208, 1230, 39, 48));
		shootAnimationRight.addFrame(sf::IntRect(272, 1228, 43, 50));
		shootAnimationRight.addFrame(sf::IntRect(340, 1225, 44, 53));
		shootAnimationRight.addFrame(sf::IntRect(402, 1223, 45, 55));
		shootAnimationRight.addFrame(sf::IntRect(463, 1225, 45, 53));
		shootAnimationRight.addFrame(sf::IntRect(525, 1229, 44, 49));
		shootAnimationRight.addFrame(sf::IntRect(592, 1227, 35, 51));
		shootAnimationRight.addFrame(sf::IntRect(657, 1227, 34, 51));
		shootAnimationRight.addFrame(sf::IntRect(724, 1227, 31, 51));
		shootAnimationRight.addFrame(sf::IntRect(785, 1227, 39, 51));
	}else{ //Female
		//Set up Left Walking Animation
		walkingAnimationLeft.setSpriteSheet(texture);
	    	walkingAnimationLeft.addFrame(sf::IntRect(20, 590, 24, 48));
	    	walkingAnimationLeft.addFrame(sf::IntRect(84, 591, 24, 47));
	    	walkingAnimationLeft.addFrame(sf::IntRect(148, 591, 24, 46));
	    	walkingAnimationLeft.addFrame(sf::IntRect(212, 590, 24, 47));
	    	walkingAnimationLeft.addFrame(sf::IntRect(276, 590, 26, 48));
	    	walkingAnimationLeft.addFrame(sf::IntRect(340, 591, 27, 47));
	    	walkingAnimationLeft.addFrame(sf::IntRect(404, 591, 26, 47));
	    	walkingAnimationLeft.addFrame(sf::IntRect(468, 590, 24, 48));
	    	walkingAnimationLeft.addFrame(sf::IntRect(532, 590, 24, 48));

		//Set up Right Walking Animation
		walkingAnimationRight.setSpriteSheet(texture);
	    	walkingAnimationRight.addFrame(sf::IntRect(20, 718, 24, 48));
	    	walkingAnimationRight.addFrame(sf::IntRect(84, 719, 24, 47));
	    	walkingAnimationRight.addFrame(sf::IntRect(148, 719, 24, 46));
	    	walkingAnimationRight.addFrame(sf::IntRect(212, 718, 24, 47));
	    	walkingAnimationRight.addFrame(sf::IntRect(274, 718, 26, 48));
	    	walkingAnimationRight.addFrame(sf::IntRect(337, 719, 27, 47));
	    	walkingAnimationRight.addFrame(sf::IntRect(402, 719, 26, 47));
	    	walkingAnimationRight.addFrame(sf::IntRect(468, 718, 24, 48));
	    	walkingAnimationRight.addFrame(sf::IntRect(532, 718, 24, 48));

		//Set up Left Shooting Animation
		shootAnimationLeft.setSpriteSheet(texture);
		shootAnimationLeft.addFrame(sf::IntRect(53, 1614, 55, 51));
		shootAnimationLeft.addFrame(sf::IntRect(269, 1616, 30, 46));
		shootAnimationLeft.addFrame(sf::IntRect(466, 1615, 36, 47));
		shootAnimationLeft.addFrame(sf::IntRect(646, 1614, 57, 48));
		shootAnimationLeft.addFrame(sf::IntRect(787, 1614, 89, 48));
		shootAnimationLeft.addFrame(sf::IntRect(978, 1614, 90, 48));
	
		//Set up Right Shooting Animation
		shootAnimationRight.setSpriteSheet(texture);
		shootAnimationRight.addFrame(sf::IntRect(84, 1998, 55, 51));
		shootAnimationRight.addFrame(sf::IntRect(277, 2000, 31, 46));
		shootAnimationRight.addFrame(sf::IntRect(458, 1999, 36, 47));
		shootAnimationRight.addFrame(sf::IntRect(641, 1998, 57, 48));
		shootAnimationRight.addFrame(sf::IntRect(852, 1998, 89, 48));
		shootAnimationRight.addFrame(sf::IntRect(1044, 1998, 90, 48));
	}	

	//Set Current Animation
	currentAnimation = &walkingAnimationLeft;

    	//Set up AnimatedSprite
    	animatedSprite.setPosition(sf::Vector2f(window.getSize().x * .1,window.getSize().y * .823));
}

//Move the animation left
void Player::moveLeft(){
	currentAnimation = &walkingAnimationLeft;
}

//Move the animation right
void Player::moveRight(){
	currentAnimation = &walkingAnimationRight;
}

//Update the animation
void Player::update(Time time){
	animatedSprite.update(time);
}

//Upgrade the speed of the player
void Player::upgradeSpeed()
{
	// 20% speed upgrade
	m_Speed += (START_SPEED * .2);
}

//Upgrade the heatlh of the player
void Player::upgradeHealth()
{
	// 20% max health upgrade
	m_MaxHealth += (START_HEALTH * .2);

}

//Increase the health of the player
void Player::increaseHealthLevel(int amount)
{
	m_Health += amount;

	// But not beyond the maximum
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}

//Play the Animated Sprite
void Player::play()
{
	animatedSprite.play(*currentAnimation);
}

//Move the position of the animation
void Player::move(Vector2f movement, float seconds)
{
	animatedSprite.move(movement * seconds);
}

//Stop movement
void Player::stop(){
	animatedSprite.stop();
}

//Return the AnimatedSprite
AnimatedSprite& Player::getAnimatedSprite(){
	return animatedSprite;
}

//Get the Speed
float Player::getSpeed(){
	return START_SPEED;
}

//Animation for shooting left
void Player::shootLeft(){
	currentAnimation = &shootAnimationLeft;
}

//Animation for shooting right
void Player::shootRight(){
	currentAnimation = &shootAnimationRight;
}

//Return Local Bounds
FloatRect Player::getAnimatedSpriteLocalBounds(){
	return animatedSprite.getLocalBounds();
}

//Return Global Bounds
FloatRect Player::getAnimatedSpriteGlobalBounds(){
	return animatedSprite.getGlobalBounds();
}

void Player::setPosition(Vector2f vector){
	animatedSprite.setPosition(vector);
}
