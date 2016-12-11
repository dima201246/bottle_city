#include "obj.hpp"

void player::init(Texture &image, player *g_tanks, int g_tanks_num, AIplayer *g_other_tanks, int g_other_tanks_num, game_map *l_main_map, int l_life, int l_level, int l_left_tank, int l_num_of_player) {
	tank::init(image, l_main_map);

	life			= l_life;
	level			= l_level;
	left_tank		= l_left_tank;
	num_of_player	= l_num_of_player;

	players_tanks	= g_tanks;
	players_num		= g_tanks_num;

	AIplayers_tanks	= g_other_tanks;
	AIplayers_num	= g_other_tanks_num;

	if (num_of_player == 1) {
		tank::setPosition(4, 11, UP_SIDE);
	} else {
		tank::setPosition(8, 11, UP_SIDE);
	}
}

void player::update(float time) {
	bool	k_d		= true,
			k_u		= true,
			k_r		= true,
			k_l		= true,
			action	= true;

	for (int	i	= 0; i < players_num; i++) {
		if ((players_tanks[i].getLife() > 0) && ((i + 1) != num_of_player) && (tank::tankComparsion(players_tanks[i].getRect()))) {
			// action	= false;
		}
	}

	if ((action) && (num_of_player == 2)) {
		/*Защита от диагоналей Начало*/
		if ((Keyboard::isKeyPressed(Keyboard::Left)) && (Keyboard::isKeyPressed(Keyboard::Down))) {
			if (tank::getSide() == LEFT_SIDE)	k_d	= false;
			else k_l	= false;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Left)) && (Keyboard::isKeyPressed(Keyboard::Up)))	{
			if (tank::getSide() == LEFT_SIDE)	k_u	= false;
			else k_l	= false;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Down))) {
			if (tank::getSide() == RIGHT_SIDE)	k_d	= false;
			else k_r	= false;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Up))) {
			if (tank::getSide() == RIGHT_SIDE)	k_u	= false;
			else k_r	= false;
		}
		/*Защита от диагоналей Конец*/

		/*Обработка кнопок Начало*/
		if ((Keyboard::isKeyPressed(Keyboard::Left)) && (k_l)) {
			tank::moveLeft();
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right)) && (k_r)) {
			tank::moveRight();
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (k_u)) {
			tank::moveUp();
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down)) && (k_d)) {
			tank::moveDown();
		}

		if (Keyboard::isKeyPressed(Keyboard::Period)) {
			tank::piu_piu();
		}
		/*Обработка кнопок Конец*/
	} else if ((action) && (num_of_player == 1)) {
		/*Защита от диагоналей Начало*/
		if ((Keyboard::isKeyPressed(Keyboard::A)) && (Keyboard::isKeyPressed(Keyboard::S))) {
			if (tank::getSide() == LEFT_SIDE)	k_d	= false;
			else k_l	= false;
		}

		if ((Keyboard::isKeyPressed(Keyboard::A)) && (Keyboard::isKeyPressed(Keyboard::W)))	{
			if (tank::getSide() == LEFT_SIDE)	k_u	= false;
			else k_l	= false;
		}

		if ((Keyboard::isKeyPressed(Keyboard::D)) && (Keyboard::isKeyPressed(Keyboard::S))) {
			if (tank::getSide() == RIGHT_SIDE)	k_d	= false;
			else k_r	= false;
		}

		if ((Keyboard::isKeyPressed(Keyboard::D)) && (Keyboard::isKeyPressed(Keyboard::W))) {
			if (tank::getSide() == RIGHT_SIDE)	k_u	= false;
			else k_r	= false;
		}
		/*Защита от диагоналей Конец*/

		/*Обработка кнопок Начало*/
		if ((Keyboard::isKeyPressed(Keyboard::A)) && (k_l)) {
			tank::moveLeft();
		}

		if ((Keyboard::isKeyPressed(Keyboard::D)) && (k_r)) {
			tank::moveRight();
		}

		if ((Keyboard::isKeyPressed(Keyboard::W)) && (k_u)) {
			tank::moveUp();
		}

		if ((Keyboard::isKeyPressed(Keyboard::S)) && (k_d)) {
			tank::moveDown();
		}

		if (Keyboard::isKeyPressed(Keyboard::Z)) {
			tank::piu_piu();
		}
		/*Обработка кнопок Конец*/
	}

	tank::update(time);
}

void player::draw(RenderWindow &window) {
	tank::draw(window);
}

int player::getLife() {
	return life;
}

FloatRect player::getRect() {
	return tank::getRect();
}