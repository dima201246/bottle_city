#include "../include/obj.hpp"

GameOver::GameOver(sf::Texture &image, GameMap *main_map) {
	sprite_.setTexture(image);
	sprite_.scale(SCALE_X, SCALE_Y);
	sprite_.setTextureRect(sf::IntRect(289, 184, 31, 16));
	endY_		= (main_map->getMaxY() / 2) * (16 * SCALE_Y) - (16 * SCALE_Y);
	dx_			= (main_map->getMaxX() / 2) * (16 * SCALE_X) - (7 * SCALE_X);
	dy_			= main_map->getMaxY() * (16 * SCALE_Y);
	status_ 	= false;
	countDelay	= 0;
}

void GameOver::draw(sf::RenderWindow &window, float time) {
	if (dy_ > endY_)
	{
		dy_	-= 0.1 * time;
		sprite_.setPosition(dx_, dy_);
	}
	else
	{
		if (countDelay < 150)
			countDelay++;
		else
			status_ = false;
	}

	if (status_)
		window.draw(sprite_);
}

void GameOver::gameEnd()
{
	status_	= true;
}

bool GameOver::getStatus()
{
	return status_;
}