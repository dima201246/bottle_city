#include "../include/obj.hpp"

bool AIplayer::tankCollision(int side, int id) {
	FloatRect	tempRect	= Tank::getRect();

	switch (side) {
		case LEFT_SIDE:		tempRect.left--;	break;
		case RIGHT_SIDE:	tempRect.left++;	break;
		case UP_SIDE:		tempRect.top--;		break;
		case DOWN_SIDE:		tempRect.top++;		break;
	}

	for (int	i	= 0; i < nAIPlayers; i++)	// Столкновение с другом
		if ((AIplayers_tanks[i].getLife() > 0) && (id != AIplayers_tanks[i].getID()) && (tempRect.intersects(AIplayers_tanks[i].getRect())))
			return true;

	for (int	i	= 0; i < nPlayers; i++)	// Столкновение с врагом
		if ((players_tanks[i].getLife() > 0) && (tempRect.intersects(players_tanks[i].getRect())))
			return true;

	return false;
}

void AIplayer::bulletCollision() {
	for (int	i	= 0; i < nAIPlayers; i++)	// Обработка столкновений пули с другом
		if ((AIplayers_tanks[i].getLife() > 0) && ((i + 1) != Tank::getID()) && (Tank::bulletComparsion(AIplayers_tanks[i].getRect())))
			Tank::bulletDestroy();

	for (int	i	= 0; i < nPlayers; i++)	// Обработка столкновений пули с пулей противника
		if ((players_tanks[i].getLife() > 0) && (players_tanks[i].bulletStatus()) && (Tank::bulletComparsion(players_tanks[i].getBulletRect())))
		{
			players_tanks[i].bulletDestroy();
			Tank::bulletDestroy();
		}

	for (int	i	= 0; i < nPlayers; i++)	// Обработка столкновений пули с врагом
		if ((players_tanks[i].getLife() > 0) && (Tank::bulletComparsion(players_tanks[i].getRect())))
		{
			Tank::bulletDestroy();
			players_tanks[i].bax_bax();

			if ((i + 1) == 1)
				Tank::r_b->setP1Life(Tank::r_b->getP1Life() - 1);
			else 
				Tank::r_b->setP2Life(Tank::r_b->getP2Life() - 1);
		}
}

void AIplayer::init(Texture &image, Player *players, int intNPlayer, AIplayer *l_frends, int intNAIplayer, GameMap *l_main_map, RightBar *l_r_b, int l_life, int l_type, int l_id) {
	Tank::init(image, l_main_map, l_r_b);
	Tank::setLife(0);
	Tank::setID(l_id);

	main_map		= l_main_map;
	type			= l_type;
	AIplayers_tanks	= l_frends;
	nAIPlayers		= intNAIplayer;
	players_tanks	= players;
	nPlayers		= intNPlayer;
	currentSide		= 8; 
}

int abs(int x){
	if (x<0)
		return x*(-1);
	else
		return x;
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
	int 	tankTop			= Tank::getRect().top;
	int 	tankLeft		= Tank::getRect().left;
	if (Tank::getLife()>0)
	{
		if (currentSide == 8)
		{
			currentSide = (rand()%4)*2;
		}

		for (int	i	= 0; i < nPlayers; i++)	{
			if(abs(tankLeft - players_tanks[i].getRect().left) < 16 and players_tanks[i].getLife()>0)	// танк на вертикальной линии с игроком
			{
				if(AIplayer::checkWallY(tankTop/16, players_tanks[i].getRect().top/16, (tankLeft)/16))
				{
					if(tankTop < players_tanks[i].getRect().top)
					{
						if (currentSide == UP_SIDE){ //сверху игрок, танк едет туда же, между ними нет стен
							Tank::piu_piu();
						}
						else if (currentSide == RIGHT_SIDE or currentSide == LEFT_SIDE)
						{
							currentSide = UP_SIDE;
						}
					}

					if(tankTop < players_tanks[i].getRect().top)	//снизу игрок, танк едет туда же, между ними нет стен
					{
						if (currentSide == DOWN_SIDE)
						{
							Tank::piu_piu();
						}
						else if (currentSide == RIGHT_SIDE or currentSide == LEFT_SIDE)
						{
							currentSide = DOWN_SIDE;
						}
					}
				}
			}

			if(abs(tankTop - players_tanks[i].getRect().top)<16 and players_tanks[i].getLife()>0)	// танк на горизонтальной линии с игроком
			{
				if(AIplayer::checkWallY(tankLeft/16, players_tanks[i].getRect().left/16, (tankTop)/16))
				{
					if(tankLeft > players_tanks[i].getRect().left)
					{
						if (currentSide == LEFT_SIDE)	//слева игрок, танк едет туда же, между ними нет стен
						{
							Tank::piu_piu();
						}
						else if (currentSide == UP_SIDE or currentSide == DOWN_SIDE)
						{
							currentSide = LEFT_SIDE;
						}
					}

					if(tankLeft < players_tanks[i].getRect().left)
					{
						if (currentSide == RIGHT_SIDE)	//справа игрок, танк едет туда же, между ними нет стен
						{
							Tank::piu_piu();
						}
						else if (currentSide == UP_SIDE or currentSide == DOWN_SIDE)
						{
							currentSide = RIGHT_SIDE;
						}
					}
				}
			}
		}
		
		
		if (not Tank::move(currentSide)) //если в сторону, в которую хотим ехать, нельзя проехать
		{	
			for (int i = 0; i < 4; ++i)
			{	
				if (!AIplayer::tankCollision(i*2, Tank::getID()))
				{
					canMove = Tank::move(i*2) || canMove;
				}
			}

			if (!canMove)
			{	
				currentSide = (rand()%4)*2;
				Tank::move(currentSide);
				Tank::piu_piu();
			}
			else
			{	
				currentSide = (rand()%4)*2;
			}
		}

		if (!AIplayer::tankCollision(currentSide, Tank::getID())) 
		{ 
		Tank::move(currentSide); 
		}
		Tank::update(time);
	}

	if (Tank::bulletStatus())
		bulletCollision();
}


void AIplayer::activation(unsigned int x, unsigned int y) {
	if (Tank::r_b->getEminems() > 0)
	{
		Tank::setLife(3);
		nAIPlayers--;
		startPosition.left = x;
		startPosition.top = y;
		Tank::setPosition(x, y, DOWN_SIDE);
	}
}

void AIplayer::bax_bax() {
	if (Tank::getLife() > 0) {
		Tank::setLife(Tank::getLife() - 1);
		if (Tank::getLife() == 0) {
			Tank::r_b->setEminems(Tank::r_b->getEminems() - 1);
			AIplayer::activation(startPosition.left, startPosition.top);
		}
	} 
}

void AIplayer::draw(RenderWindow &window) {
	if (Tank::getLife()!=0)
	{
		Tank::draw(window);
	}
}
