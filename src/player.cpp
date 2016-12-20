#include "../include/obj.hpp"

bool player::tankCollision(int side, int id) {
	FloatRect	tempRect	= tank::getRect();

	switch (side) {
		case LEFT_SIDE:		tempRect.left--;	break;
		case RIGHT_SIDE:	tempRect.left++;	break;
		case UP_SIDE:		tempRect.top--;		break;
		case DOWN_SIDE:		tempRect.top++;		break;
	}

	for (int	i	= 0; i < players_num; i++)	// Столкновение с другом
		if ((players_tanks[i].getLife() > 0) && (id != players_tanks[i].getID()) && (tempRect.intersects(players_tanks[i].getRect())))
			return true;

	for (int	i	= 0; i < AIplayers_num; i++)	// Столкновение с врагом
		if ((AIplayers_tanks[i].getLife() > 0) && (tempRect.intersects(AIplayers_tanks[i].getRect())))
			return true;

	return false;
}

void player::bulletCollision() {
	for (int	i	= 0; i < players_num; i++)	// Обработка столкновений пули с другом
		if ((players_tanks[i].getLife() > 0) && ((i + 1) != tank::getID()) && (tank::bulletComparsion(players_tanks[i].getRect())))
			tank::bulletDestroy();

	for (int	i	= 0; i < AIplayers_num; i++)	// Обработка столкновений пули с пулей противника
		if ((AIplayers_tanks[i].getLife() > 0) && (AIplayers_tanks[i].bulletStatus()) && (tank::bulletComparsion(AIplayers_tanks[i].getBulletRect()))) {
			AIplayers_tanks[i].bulletDestroy();
			tank::bulletDestroy();
		}

	for (int	i	= 0; i < AIplayers_num; i++)	// Обработка столкновений пули с врагом
		if ((AIplayers_tanks[i].getLife() > 0) && (tank::bulletComparsion(AIplayers_tanks[i].getRect()))) {
			AIplayers_tanks[i].bax_bax();
			tank::bulletDestroy();	
		}
}

void player::init(Texture &image, player *g_tanks, int l_frend_num, AIplayer *g_other_tanks, int g_other_tanks_num, game_map *l_main_map, right_bar *l_r_b, int l_life, int l_level, int l_left_tank, int l_num_of_player) {
	tank::init(image, l_main_map, l_r_b);

	main_map		= l_main_map;

	tank::setLife(l_life);
	level			= l_level;
	left_tank		= l_left_tank;
	tank::setID(l_num_of_player);

	players_tanks	= g_tanks;
	players_num		= l_frend_num;
	AIplayers_tanks	= g_other_tanks;
	AIplayers_num	= g_other_tanks_num;

	if (tank::getID() == 1) {
		tank::setPosition(4, 12, UP_SIDE);
	} else {
		tank::setPosition(8, 12, UP_SIDE);
	}
}

void player::update(float time) {
	bool	k_d		= true,
			k_u		= true,
			k_r		= true,
			k_l		= true;

	if (tank::getLife() > 0) {
		if (tank::getID() == 2) {
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
				if (!tankCollision(LEFT_SIDE, tank::getID()))
					tank::moveLeft();
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right)) && (k_r)) {
				if (!tankCollision(RIGHT_SIDE, tank::getID()))
					tank::moveRight();
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up)) && (k_u)) {
				if (!tankCollision(UP_SIDE, tank::getID()))
					tank::moveUp();
			}

			if ((Keyboard::isKeyPressed(Keyboard::Down)) && (k_d)) {
				if (!tankCollision(DOWN_SIDE, tank::getID()))
					tank::moveDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::Period)) {
				tank::piu_piu();
			}
			/*Обработка кнопок Конец*/
		} else if (tank::getID() == 1) {
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
				if (!tankCollision(LEFT_SIDE, tank::getID()))
					tank::moveLeft();
			}

			if ((Keyboard::isKeyPressed(Keyboard::D)) && (k_r)) {
				if (!tankCollision(RIGHT_SIDE, tank::getID()))
					tank::moveRight();
			}

			if ((Keyboard::isKeyPressed(Keyboard::W)) && (k_u)) {
				if (!tankCollision(UP_SIDE, tank::getID()))
					tank::moveUp();
			}

			if ((Keyboard::isKeyPressed(Keyboard::S)) && (k_d)) {
				if (!tankCollision(DOWN_SIDE, tank::getID()))
					tank::moveDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::Z)) {
				tank::piu_piu();
			}
			/*Обработка кнопок Конец*/
		}

		tank::update(time);

		if (tank::bulletStatus())
			bulletCollision();
	}
}

void player::draw(RenderWindow &window) {
	if (tank::getLife()!=0)	{
		tank::draw(window);
	}
}

void player::bax_bax() {
	if (tank::getID() == 1)
		tank::setPosition(4, 12, UP_SIDE);
	else
		tank::setPosition(8, 12, UP_SIDE);

	tank::setLife(tank::getLife() - 1);
}