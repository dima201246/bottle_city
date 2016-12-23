#include "../include/obj.hpp"

GPause::GPause(sf::Texture &image, GameMap *main_map) {
	sprite_.setTexture(image);
	sprite_.scale(SCALE_X, SCALE_Y);
	sprite_.setTextureRect(sf::IntRect(288, 175, 40, 8));
	sprite_.setPosition((((main_map->getMaxX() / 2) * (16 * SCALE_X))) - (12 * SCALE_X), (((main_map->getMaxY() / 2) * (16 * SCALE_Y))) - (2 * SCALE_Y));
	statusGame_	= false;
}

void GPause::paused(sf::RenderWindow &window) {
	if (!statusGame_) {
		window.draw(sprite_);
        window.display();
		statusGame_	= true;
	} else {
		statusGame_	= false;
	}
}

bool GPause::status() {
	return statusGame_;
}