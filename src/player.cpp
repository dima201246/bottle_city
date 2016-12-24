#include "../include/obj.hpp"

bool Player::tankCollision(int side, int id) {
	sf::FloatRect	tempRect	= Tank::getRect();

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

			if (AIplayers_tanks[i].bax_bax() == TANK_KILL)
			{
				Player::killAI();

				if (nPlayers != 1)
					players_tanks[(Tank::getID() == 1 ? 1 : 0)].killAI();	// Сообщение напарнику, об убийстве врага
			}
		}
}

void Player::init(sf::Texture &image, Player *players, int intNPlayer, GameMap *l_main_map, RightBar *l_r_b, int l_life, int l_level, int l_left_tank, int l_num_of_player) {
	Tank::init(image, l_main_map, l_r_b);


	Tank::setLife(l_life);
	Tank::setID(l_num_of_player);

	level			= l_level;
	nPlayers		= intNPlayer;
	main_map		= l_main_map;
	left_tank		= l_left_tank;
	players_tanks	= players;

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
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			{
				if (Tank::getSide() == LEFT_SIDE)	k_d	= false;
				else k_l	= false;
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
			{
				if (Tank::getSide() == LEFT_SIDE)	k_u	= false;
				else k_l	= false;
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			{
				if (Tank::getSide() == RIGHT_SIDE)	k_d	= false;
				else k_r	= false;
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
			{
				if (Tank::getSide() == RIGHT_SIDE)	k_u	= false;
				else k_r	= false;
			}
			/*Защита от диагоналей Конец*/

			/*Обработка кнопок Начало*/
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (k_l))
			{
				if (!tankCollision(LEFT_SIDE, Tank::getID()))
					Tank::moveLeft();
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (k_r))
			{
				if (!tankCollision(RIGHT_SIDE, Tank::getID()))
					Tank::moveRight();
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (k_u))
			{
				if (!tankCollision(UP_SIDE, Tank::getID()))
					Tank::moveUp();
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (k_d))
			{
				if (!tankCollision(DOWN_SIDE, Tank::getID()))
					Tank::moveDown();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
				Tank::piu_piu();
			/*Обработка кнопок Конец*/
		}
		else if (Tank::getID() == 2)
		{
			/*Защита от диагоналей Начало*/
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
			{
				if (Tank::getSide() == LEFT_SIDE)	k_d	= false;
				else k_l	= false;
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
			{
				if (Tank::getSide() == LEFT_SIDE)	k_u	= false;
				else k_l	= false;
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
			{
				if (Tank::getSide() == RIGHT_SIDE)	k_d	= false;
				else k_r	= false;
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
			{
				if (Tank::getSide() == RIGHT_SIDE)	k_u	= false;
				else k_r	= false;
			}
			/*Защита от диагоналей Конец*/

			/*Обработка кнопок Начало*/
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (k_l))
			{
				if (!tankCollision(LEFT_SIDE, Tank::getID()))
					Tank::moveLeft();
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && (k_r))
			{
				if (!tankCollision(RIGHT_SIDE, Tank::getID()))
					Tank::moveRight();
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (k_u))
			{
				if (!tankCollision(UP_SIDE, Tank::getID()))
					Tank::moveUp();
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && (k_d))
			{
				if (!tankCollision(DOWN_SIDE, Tank::getID()))
					Tank::moveDown();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				Tank::piu_piu();
			/*Обработка кнопок Конец*/
		}

		Tank::update(time);

		if (Tank::bulletStatus())
			bulletCollision();
	}
}

void Player::draw(sf::RenderWindow &window) {
	if (Tank::getLife()!=0)
		Tank::draw(window);
}

void Player::bax_bax() {
	if (Tank::getID() == 1)
		Tank::setPosition(8, 12, UP_SIDE);
	else
		Tank::setPosition(4, 12, UP_SIDE);

	Tank::setLife(Tank::getLife() - 1);

	if (Tank::getLife() == 0)
		Tank::bulletDestroy();
}

int Player::getLeftTank()
{
	return Player::left_tank;
}

void Player::killAI()
{
	if (Player::left_tank != 0)
		Player::left_tank--;
}

void Player::setEminemsPoint(AIplayer *AI_player, int intNAIplayer)
{
	AIplayers_tanks	= AI_player;
	nAIPlayers		= intNAIplayer;
}