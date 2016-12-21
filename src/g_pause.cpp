#include "../include/obj.hpp"

GPause::GPause(Texture &image, GameMap *main_map) {
	p_sprite.setTexture(image);
	p_sprite.scale(SCALE_X, SCALE_Y);
	p_sprite.setTextureRect(IntRect(288, 175, 40, 8));
	p_sprite.setPosition((((main_map->getMaxX() / 2) * (16 * SCALE_X))) - (12 * SCALE_X), (((main_map->getMaxY() / 2) * (16 * SCALE_Y))) - (2 * SCALE_Y));
	status_game	= false;
}

void GPause::paused(RenderWindow &window) {
	if (!status_game) {
		window.draw(p_sprite);
        window.display();
		status_game	= true;
	} else {
		status_game	= false;
	}
}

bool GPause::status() {
	return status_game;
}