#include "../include/obj.hpp"

void Tank::init(sf::Texture &image, GameMap *l_main_map, RightBar *l_r_b) {
	Bullet::init(image, l_main_map);
	Body::init(image, l_main_map);
	r_b			= l_r_b;
}

void Tank::update(float time) {
	Body::update(time);

	if (Bullet::active()) {
		Bullet::update(time);
	}
}

void Tank::piu_piu() {
	if (!Bullet::active()) {
		Bullet::shot(Body::getRect().left, Body::getRect().top, Body::getSide());
	}
}

sf::FloatRect Tank::getRect() {
	return Body::getRect();
}

void Tank::draw(sf::RenderWindow& window) {
	Body::draw(window);

	if (Bullet::active()) {
		Bullet::draw(window);
	}
}

void Tank::setLife(int l_life) {
	life	= l_life;
}

int Tank::getLife() {
	return life;
}

void Tank::setID(int l_id) {
	id	= l_id;
}

int Tank::getID() {
	return id;
}