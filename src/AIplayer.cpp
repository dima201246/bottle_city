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
		if ((players_tanks[i].getLife() > 0) && (players_tanks[i].bulletStatus()) && (tank::bulletComparsion(players_tanks[i].getBulletRect()))) {
			players_tanks[i].bulletDestroy();
			tank::bulletDestroy();
		}

	for (int	i	= 0; i < players_num; i++)	// Обработка столкновений пули с врагом
		if ((players_tanks[i].getLife() > 0) && (tank::bulletComparsion(players_tanks[i].getRect()))) {
			players_tanks[i].bax_bax();
			tank::bulletDestroy();
			if ((i + 1) == 1)
				tank::r_b->setP1Life(tank::r_b->getP1Life() - 1);
			else 
				tank::r_b->setP2Life(tank::r_b->getP2Life() - 1);
		}
}

void AIplayer::init(Texture &image, player *g_other_tanks, int g_other_tanks_num, AIplayer *l_frends, int l_frend_num, game_map *l_main_map, right_bar *l_r_b, int l_life, int l_type, int l_id) {
	tank::init(image, l_main_map, l_r_b);
	tank::setLife(0);
	tank::setID(l_id);
	main_map		= l_main_map;
	type			= l_type;
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

bool AIplayer::checkWallX(int x, int x2, int y) {
	bool	noWall			= true;
	int 	temp;
	if (x2<x)
	{	
		temp = x2;
		x2 = x;
		x = temp;
	} 
	for (int k = 0; k < x2-x; ++k)
	{	
		temp = main_map->getElement(x+k, y);
		if ((temp != 's') && (temp != 'v') && (temp != 'i'))
		{
			noWall = false; 
			break;
		} 
	}
	return noWall;

}
bool AIplayer::checkWallY(int y, int y2, int x) {
	bool	noWall			= true;
	int 	temp;
	if (y2<y)
	{	
		temp = y2;
		y2 = x;
		y = temp;
	} 
	for (int k = 0; k < y2-y; ++k)
	{	
		temp = main_map->getElement(x, y+k);
		if ((temp != 's') && (temp != 'v') && (temp != 'i'))
		{
			noWall = false; 
			break;
		} 
	}
	return noWall;

}

void AIplayer::update(float time) {
	bool 	canMove			= false;

	char	temp;
	int 	tankTop			= tank::getRect().top;
	int 	tankLeft		= tank::getRect().left;
/*	if (tank::getLife()>0)
	{
		if (currentSide == 8)
		{
			currentSide = (rand()%4)*2;
		}
		for (int	i	= 0; i < players_num; i++)	{
			if(abs(tankLeft - players_tanks[i].getRect().left) < 16 and players_tanks[i].getLife()>0){ // танк на вертикальной линии с игроком
				if(AIplayer::checkWallY(tankTop/16, players_tanks[i].getRect().top/16, (tankLeft)/16)){
					if(tankTop < players_tanks[i].getRect().top) {
						if (currentSide == UP_SIDE){ //сверху игрок, танк едет туда же, между ними нет стен
							tank::piu_piu();
						} else if (currentSide == RIGHT_SIDE or currentSide == LEFT_SIDE) {
							currentSide = UP_SIDE;
						}
					}
					if(tankTop < players_tanks[i].getRect().top) {
						if (currentSide == DOWN_SIDE){ //снизу игрок, танк едет туда же, между ними нет стен
							tank::piu_piu();
						} else if (currentSide == RIGHT_SIDE or currentSide == LEFT_SIDE) {
							currentSide = DOWN_SIDE;
						}
					}
				}
			}
			
			if(abs(tankTop - players_tanks[i].getRect().top)<16 and players_tanks[i].getLife()>0){ // танк на горизонтальной линии с игроком
				if(AIplayer::checkWallY(tankLeft/16, players_tanks[i].getRect().left/16, (tankTop)/16)) { 
					if(tankLeft > players_tanks[i].getRect().left) {
						if (currentSide == LEFT_SIDE){ //слева игрок, танк едет туда же, между ними нет стен
							tank::piu_piu();
						} else if (currentSide == UP_SIDE or currentSide == DOWN_SIDE) {
							currentSide = LEFT_SIDE;
						}
					}
					if(tankLeft < players_tanks[i].getRect().left) {
						if (currentSide == RIGHT_SIDE){ //справа игрок, танк едет туда же, между ними нет стен
							tank::piu_piu();
						} else if (currentSide == UP_SIDE or currentSide == DOWN_SIDE) {
							currentSide = RIGHT_SIDE;
						}
					}

				}
			}
			
		}*/
		
		
/*		if (not tank::move(currentSide)) //если в сторону, в которую хотим ехать, нельзя проехать
		{	
			for (int i = 0; i < 4; ++i)
			{	
				if (!AIplayer::tankCollision(i*2, tank::getID()))
				{
					canMove = tank::move(i*2) || canMove;
				}
			}
			if (!canMove)
			{	
				currentSide = (rand()%4)*2;
				tank::move(currentSide);
				tank::piu_piu();
			} else {	
				currentSide = (rand()%4)*2;
			}
		}*/

		// if (!AIplayer::tankCollision(currentSide, tank::getID())) 
		// { 
		// tank::move(currentSide); 
		// }
		tank::update(time);
	// }
	if (tank::bulletStatus())
		bulletCollision();
}


void AIplayer::activation(unsigned int x, unsigned int y) {
	if (tank::r_b->getEminems() > 0)
	{
		tank::setLife(3);
		AIplayers_num--;
		startPosition.left = x;
		startPosition.top = y;
		tank::setPosition(x, y, DOWN_SIDE);
	}
}

void AIplayer::bax_bax() {
	if (tank::getLife() > 0) {
		tank::setLife(tank::getLife() - 1);
		if (tank::getLife() == 0) {
			tank::r_b->setEminems(tank::r_b->getEminems() - 1);
			AIplayer::activation(startPosition.left, startPosition.top);
		}
	} 
}

void AIplayer::draw(RenderWindow &window) {
	if (tank::getLife()!=0)
	{
		tank::draw(window);
	}
}
