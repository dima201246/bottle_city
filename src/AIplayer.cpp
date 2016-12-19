#include "../include/obj.hpp"

bool AIplayer::tankCollision(int side, int id) {
	FloatRect	tempRect	= tank::getRect();

	switch (side) {
		case LEFT_SIDE:		tempRect.left--;	break;
		case RIGHT_SIDE:	tempRect.left++;	break;
		case UP_SIDE:		tempRect.top--;		break;
		case DOWN_SIDE:		tempRect.top++;		break;
	}

	for (int	i	= 0; i < AIplayers_num; i++)	// Столкновение с другом
		if ((AIplayers_tanks[i].getLife() > 0) && (id != AIplayers_tanks[i].getID()) && (tempRect.intersects(AIplayers_tanks[i].getRect())))
			return true;

	for (int	i	= 0; i < players_num; i++)	// Столкновение с врагом
		if ((players_tanks[i].getLife() > 0) && (tempRect.intersects(players_tanks[i].getRect())))
			return true;

	return false;
}

void AIplayer::bulletCollision() {
	for (int	i	= 0; i < AIplayers_num; i++)	// Обработка столкновений пули с другом
		if ((AIplayers_tanks[i].getLife() > 0) && ((i + 1) != tank::getID()) && (tank::bulletComparsion(AIplayers_tanks[i].getRect())))
			tank::bulletDestroy();

	for (int	i	= 0; i < players_num; i++)	// Обработка столкновений пули с пулей противника
		if ((players_tanks[i].getLife() > 0) && (tank::bulletComparsion(players_tanks[i].getBulletRect()))) {
			players_tanks[i].bulletDestroy();
			tank::bulletDestroy();
		}

	for (int	i	= 0; i < players_num; i++)	// Обработка столкновений пули с врагом
		if ((players_tanks[i].getLife() > 0) && (tank::bulletComparsion(players_tanks[i].getRect()))) {
			players_tanks[i].bax_bax();
			if ((i + 1) == 1)
				tank::r_b->setP1Life(tank::r_b->getP1Life() - 1);
			else 
				tank::r_b->setP2Life(tank::r_b->getP2Life() - 1);
		}
}

void AIplayer::init(Texture &image, player *g_other_tanks, int g_other_tanks_num, AIplayer *l_frends, int l_frend_num, game_map *l_main_map, right_bar *l_r_b, bool l_active, int l_life, int l_type, int l_id) {
	tank::init(image, l_main_map, l_r_b);
	tank::setLife(l_life);
	tank::setID(l_id);

	main_map		= l_main_map;
	type			= l_type;
	active			= l_active;
	AIplayers_tanks	= l_frends;
	AIplayers_num	= l_frend_num;
	players_tanks	= g_other_tanks;
	players_num		= g_other_tanks_num;
	currentSide		= 8; 
}

int abs(int x){
	if (x<0)
	{
		return x*(-1);
	} else {
		return x;
	}
}

void AIplayer::update(float time) {
	bool 	canMove			= false;
	bool	noWall			= true;
	char	temp;
	int 	tankTop			= tank::getRect().top;
	int 	tankLeft		= tank::getRect().left;
	if (currentSide == 8)
	{
		currentSide = (rand()%4)*2;
	}
	for (int	i	= 0; i < players_num; i++)	{
		if(abs(tankLeft - players_tanks[i].getRect().left) < 16){ // совпадает с коорд игрока
			if(tankTop<players_tanks[i].getRect().top and currentSide == DOWN_SIDE) {

				for (int k = 0; k < abs(tankTop-players_tanks[i].getRect().top)/16; ++k)
				{	
					temp = main_map->getElement(((tankLeft+8)/16), (tankTop/16+k/16));
					if (temp != 's' and temp != 'v' and temp != 'i')
					{
						noWall = false; 
						break;
					} 
				}
				if (noWall) {
					tank::piu_piu();
				}
			} else if (currentSide == UP_SIDE) {

				for (int k = 0; k < abs(tankTop-players_tanks[i].getRect().top)/16; ++k)
				{	
					temp = main_map->getElement(((tankLeft+8)/16), (players_tanks[i].getRect().top/16+k/16));
					if (temp != 's' and temp != 'v' and temp != 'i')
					{
						noWall = false; 
						break;
					} 
				}

				if (noWall) {
					tank::piu_piu();
				}
			}
			noWall = true;
		}
		
		if(abs(tankTop - players_tanks[i].getRect().top)<16){ // совпадает с коорд игрока
			if(tankLeft>players_tanks[i].getRect().left and currentSide == LEFT_SIDE) {
				
				for (int k = 0; k < abs(tankLeft-players_tanks[i].getRect().left)/16; ++k)
				{	
					temp = main_map->getElement((players_tanks[i].getRect().left/16+k/16), ((tankTop+8)/16));
					if (temp != 's' and temp != 'v' and temp != 'i')
					{
						noWall = false; 
						break;
					} 
				}
				
				if (noWall) {
					tank::piu_piu();
				}
			} else if (currentSide = RIGHT_SIDE) {
				
				for (int k = 0; k < abs(tankLeft-players_tanks[i].getRect().left)/16; ++k)
				{	
					temp = main_map->getElement((tankLeft/16+k/16), ((tankTop+8)/16));
					if (temp != 's' and temp != 'v' and temp != 'i')
					{
						noWall = false; 
						break;
					} 
				}
				
				if (noWall) {
					tank::piu_piu();
				}
			}
			noWall = true;
		}
	}
	
	
	if (not tank::move(currentSide)) //если в сторону, в которую хотим ехать, нельзя проехать
	{	
		for (int i = 0; i < 4; ++i)
		{	
			canMove = tank::move(i*2) or canMove;
		}
		if (!canMove)
		{	
			currentSide = (rand()%4)*2;
			tank::move(currentSide);
			tank::piu_piu();
		} else {	
			currentSide = (rand()%4)*2;
		}
	}
	//if (true)
	if (!AIplayer::tankCollision(currentSide, tank::getID()))
	{
		tank::move(currentSide);
		tank::update(time);
	} else {
		currentSide = (rand()%4)*2;
		AIplayer::update(time);
	}
}


void AIplayer::activation(unsigned int x, unsigned int y) {
	active	= true;
	tank::setLife(3);
	startPosition.left = x;
	startPosition.top = y;
	tank::setPosition(x, y, DOWN_SIDE);
}

void AIplayer::bulletDestroy() {
	tank::bulletDestroy();
}

void AIplayer::bax_bax() {
	if (tank::getLife() > 0)
		tank::setLife(tank::getLife() - 1);
}

void AIplayer::draw(RenderWindow &window) {
	if (active) {
		if (tank::getLife() == 0)
		{
			AIplayer::activation(startPosition.left, startPosition.top);
			tank::draw(window);
		} else {		
			tank::draw(window);
		}
	}
}