#include "../include/obj.hpp"

tank::~tank() {
	delete t_bullet;
	delete t_body;
}

void tank::init(Texture &image, game_map *l_main_map) {
	t_bullet	= new bullet(image, l_main_map);
	t_body		= new body(image, l_main_map);
}

void tank::setPosition(unsigned int x, unsigned int y, int getted_side) {
	t_body->setPosition(x, y, getted_side);
}

void tank::update(float time) {
	t_body->update(time);

	if (t_bullet->active()) {
		t_bullet->update(time);
	}
}

void tank::piu_piu() {
	FloatRect t_rect	= t_body->getRect();

	if (!t_bullet->active()) {
		t_bullet->shot(t_rect.left, t_rect.top, t_body->getSide());
	}
}

bool tank::moveUp() {
	return t_body->moveUp();
}

bool tank::moveDown() {
	return t_body->moveDown();
}

bool tank::moveLeft() {
	return t_body->moveLeft();
}

bool tank::moveRight() {
	return t_body->moveRight();
}

bool tank::tankComparsion(FloatRect l_rect) {
	return t_body->tankComparsion(l_rect);
}

bool tank::move(int side) {
	return t_body->move(side);
}

int tank::getSide() {
	return t_body->getSide();
}

FloatRect tank::getRect() {
	return t_body->getRect();
}

bool tank::bulletComparsion(FloatRect b_rect) {
	return t_bullet->bulletComparsion(b_rect);
}


FloatRect tank::getBulletRect() {
	return t_bullet->getRect();
}

void tank::bulletDestroy() {
	t_bullet->destroy();
}

bool tank::bulletStatus() {
	return t_bullet->active();
}

void tank::draw(RenderWindow& window) {
	t_body->draw(window);

	if (t_bullet->active()) {
		t_bullet->draw(window);
	}
}