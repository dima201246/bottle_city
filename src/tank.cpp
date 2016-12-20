#include "../include/obj.hpp"

void tank::init(Texture &image, game_map *l_main_map, right_bar *l_r_b) {
	bullet::init(image, l_main_map);
	body::init(image, l_main_map);
	r_b			= l_r_b;
}

void tank::update(float time) {
	body::update(time);

	if (bullet::active()) {
		bullet::update(time);
	}
}

void tank::piu_piu() {
	if (!bullet::active()) {
		bullet::shot(body::getRect().left, body::getRect().top, body::getSide());
	}
}

FloatRect tank::getRect() {
	return body::getRect();
}

void tank::draw(RenderWindow& window) {
	body::draw(window);

	if (bullet::active()) {
		bullet::draw(window);
	}
}

void tank::setLife(int l_life) {
	life	= l_life;
}

int tank::getLife() {
	return life;
}

void tank::setID(int l_id) {
	id	= l_id;
}

int tank::getID() {
	return id;
}