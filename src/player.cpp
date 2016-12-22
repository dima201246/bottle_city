#include "../include/obj.hpp"

bool Player::tankCollision(int side, int id) {
	FloatRect	tempRect	= Tank::getRect();

	switch (side) {
		case LEFT_SIDE:		tempRect.left--;	break;
		case RIGHT_SIDE:	tempRect.left++;	break;
		case UP_SIDE:		tempRect.top--;		break;
		case DOWN_SIDE:		tempRect.top++;		break;
	}

	Tank::setSide(side);

	for (int	i	= 0; i < nPlayers; i++)		// Столкновение с другом
		if ((players_tanks[i].getLife() > 0) && (id != players_tanks[i].getID()) && (tempRect.intersects(players_tanks[i].getRect())))
			return true;

	for (int	i	= 0; i < nAIPlayers; i++)	// Столкновение с врагом
		if ((AIplayers_tanks[i].getLife() > 0) && (tempRect.intersects(AIplayers_tanks[i].getRect())))
			return true;

	return false;
}

void Player::bulletCollision() {
	for (int	i	= 0; i < nPlayers; i++)		// Обработка столкновений пули с другом
		if ((players_tanks[i].getLife() > 0) && ((i + 1) != Tank::getID()) && (Tank::bulletComparsion(players_tanks[i].getRect())))
			Tank::bulletDestroy();

	for (int	i	= 0; i < nAIPlayers; i++)	// Обработка столкновений пули с пулей противника
		if ((AIplayers_tanks[i].getLife() > 0) && (AIplayers_tanks[i].bulletStatus()) && (Tank::bulletComparsion(AIplayers_tanks[i].getBulletRect())))
		{
			Tank::bulletDestroy();
			AIplayers_tanks[i].bulletDestroy();
		}

	for (int	i	= 0; i < nAIPlayers; i++)	// Обработка столкновений пули с врагом
		if ((AIplayers_tanks[i].getLife() > 0) && (Tank::bulletComparsion(AIplayers_tanks[i].getRect())))
		{
			Tank::bulletDestroy();	
			AIplayers_tanks[i].bax_bax();
		}
}

void Player::init(Texture &image, Player *players, int intNPlayer, AIplayer *AI_player, int intNAIplayer, GameMap *l_main_map, RightBar *l_r_b, int l_life, int l_level, int l_left_tank, int l_num_of_player) {
	Tank::init(image, l_main_map, l_r_b);


	Tank::setLife(l_life);
	Tank::setID(l_num_of_player);

	level			= l_level;
	nPlayers		= intNPlayer;
	main_map		= l_main_map;
	left_tank		= l_left_tank;
	nAIPlayers		= intNAIplayer;
	players_tanks	= players;
	AIplayers_tanks	= AI_player;

	if (Tank::getID() == 1)
		Tank::setPosition(8, 12, UP_SIDE);
	else
		Tank::setPosition(4, 12, UP_SIDE);
}

void Player::update(float time) {
	bool	k_d		= true,
			k_u		= true,
			k_r		= true,
			k_l		= true;

	if (Tank::getLife() > 0)
	{
		if (Tank::getID() == 1)
		{
			/*Защита от диагоналей Начало*/
			if ((Keyboard::isKeyPressed(Keyboard::Left)) && (Keyboard::isKeyPressed(Keyboard::Down)))
			{
				if (Tank::getSide() == LEFT_SIDE)	k_d	= false;
				else k_l	= false;
			}

			if ((Keyboard::isKeyPressed(Keyboard::Left)) && (Keyboard::isKeyPressed(Keyboard::Up)))
			{
				if (Tank::getSide() == LEFT_SIDE)	k_u	= false;
				else k_l	= false;
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Down)))
			{
				if (Tank::getSide() == RIGHT_SIDE)	k_d	= false;
				else k_r	= false;
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Up)))
			{
				if (Tank::getSide() == RIGHT_SIDE)	k_u	= false;
				else k_r	= false;
			}
			/*Защита от диагоналей Конец*/

			/*Обработка кнопок Начало*/
			if ((Keyboard::isKeyPressed(Keyboard::Left)) && (k_l))
			{
				if (!tankCollision(LEFT_SIDE, Tank::getID()))
					Tank::moveLeft();
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right)) && (k_r))
			{
				if (!tankCollision(RIGHT_SIDE, Tank::getID()))
					Tank::moveRight();
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up)) && (k_u))
			{
				if (!tankCollision(UP_SIDE, Tank::getID()))
					Tank::moveUp();
			}

			if ((Keyboard::isKeyPressed(Keyboard::Down)) && (k_d))
			{
				if (!tankCollision(DOWN_SIDE, Tank::getID()))
					Tank::moveDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::Period))
				Tank::piu_piu();
			/*Обработка кнопок Конец*/
		}
		else if (Tank::getID() == 2)
		{
			/*Защита от диагоналей Начало*/
			if ((Keyboard::isKeyPressed(Keyboard::A)) && (Keyboard::isKeyPressed(Keyboard::S)))
			{
				if (Tank::getSide() == LEFT_SIDE)	k_d	= false;
				else k_l	= false;
			}

			if ((Keyboard::isKeyPressed(Keyboard::A)) && (Keyboard::isKeyPressed(Keyboard::W)))
			{
				if (Tank::getSide() == LEFT_SIDE)	k_u	= false;
				else k_l	= false;
			}

			if ((Keyboard::isKeyPressed(Keyboard::D)) && (Keyboard::isKeyPressed(Keyboard::S)))
			{
				if (Tank::getSide() == RIGHT_SIDE)	k_d	= false;
				else k_r	= false;
			}

			if ((Keyboard::isKeyPressed(Keyboard::D)) && (Keyboard::isKeyPressed(Keyboard::W)))
			{
				if (Tank::getSide() == RIGHT_SIDE)	k_u	= false;
				else k_r	= false;
			}
			/*Защита от диагоналей Конец*/

			/*Обработка кнопок Начало*/
			if ((Keyboard::isKeyPressed(Keyboard::A)) && (k_l))
			{
				if (!tankCollision(LEFT_SIDE, Tank::getID()))
					Tank::moveLeft();
			}

			if ((Keyboard::isKeyPressed(Keyboard::D)) && (k_r))
			{
				if (!tankCollision(RIGHT_SIDE, Tank::getID()))
					Tank::moveRight();
			}

			if ((Keyboard::isKeyPressed(Keyboard::W)) && (k_u))
			{
				if (!tankCollision(UP_SIDE, Tank::getID()))
					Tank::moveUp();
			}

			if ((Keyboard::isKeyPressed(Keyboard::S)) && (k_d))
			{
				if (!tankCollision(DOWN_SIDE, Tank::getID()))
					Tank::moveDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::Z))
				Tank::piu_piu();
			/*Обработка кнопок Конец*/
		}

		Tank::update(time);

		if (Tank::bulletStatus())
			bulletCollision();
	}
}

void Player::draw(RenderWindow &window) {
	if (Tank::getLife()!=0)
		Tank::draw(window);
}

void Player::bax_bax() {
/*	if (Tank::getID() == 1)
		Tank::setPosition(8, 12, UP_SIDE);
	else
		Tank::setPosition(4, 12, UP_SIDE);

	Tank::setLife(Tank::getLife() - 1);*/
}