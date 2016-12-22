#include "../include/obj.hpp"

bool AIplayer::tankCollision_(int side, int id) {
	FloatRect	tempRect	= Tank::getRect();

	switch (side) {
		case LEFT_SIDE:		tempRect.left--;	break;
		case RIGHT_SIDE:	tempRect.left++;	break;
		case UP_SIDE:		tempRect.top--;		break;
		case DOWN_SIDE:		tempRect.top++;		break;
	}

	for (int	i	= 0; i < nAIPlayers_; i++)	// Столкновение с другом
		if ((AIplayersTanks_[i].getLife() > 0) && (id != AIplayersTanks_[i].getID()) && (tempRect.intersects(AIplayersTanks_[i].getRect())))
			return true;

	for (int	i	= 0; i < nPlayers_; i++)	// Столкновение с врагом
		if ((playersTanks_[i].getLife() > 0) && (tempRect.intersects(playersTanks_[i].getRect())))
			return true;

	return false;
}

void AIplayer::bulletCollision_() {
	for (int	i	= 0; i < nAIPlayers_; i++)	// Обработка столкновений пули с другом
		if ((AIplayersTanks_[i].getLife() > 0) && ((i + 1) != Tank::getID()) && (Tank::bulletComparsion(AIplayersTanks_[i].getRect())))
			Tank::bulletDestroy();

	for (int	i	= 0; i < nPlayers_; i++)	// Обработка столкновений пули с пулей противника
		if ((playersTanks_[i].getLife() > 0) && (playersTanks_[i].bulletStatus()) && (Tank::bulletComparsion(playersTanks_[i].getBulletRect())))
		{
			playersTanks_[i].bulletDestroy();
			Tank::bulletDestroy();
		}

	for (int	i	= 0; i < nPlayers_; i++)	// Обработка столкновений пули с врагом
		if ((playersTanks_[i].getLife() > 0) && (Tank::bulletComparsion(playersTanks_[i].getRect())))
		{
			Tank::bulletDestroy();
			playersTanks_[i].bax_bax();

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

	mainMap_		= l_main_map;
	type_			= l_type;
	AIplayersTanks_	= l_frends;
	nAIPlayers_		= intNAIplayer;
	playersTanks_	= players;
	nPlayers_		= intNPlayer;
	currentSide_		= 8; 
}

int abs(int x){
	if (x<0)
		return x*(-1);
	else
		return x;
}

bool AIplayer::checkWallX_(int x, int x2, int y) {
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
		temp = mainMap_->getElement(x+k, y);
		if ((temp != 's') && (temp != 'v') && (temp != 'i'))
		{
			noWall = false; 
			break;
		} 
	}
	return noWall;

}
bool AIplayer::checkWallY_(int y, int y2, int x) {
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
		temp = mainMap_->getElement(x, y+k);
		if ((temp != 's') && (temp != 'v') && (temp != 'i'))
		{
			noWall = false; 
			break;
		} 
	}
	return noWall;

}

void AIplayer::update(float time) {
	bool 	canMove		= false;

	char	temp;

	int 	tankTop		= Tank::getRect().top,
			tankLeft	= Tank::getRect().left;

	if (Tank::getLife() > 0)
	{
		if (currentSide_ == 8)
		{
			currentSide_ = (rand()%4)*2;
		}

		for (int	i	= 0; i < nPlayers_; i++)	{
			if(abs(tankLeft - playersTanks_[i].getRect().left) < 16 and playersTanks_[i].getLife()>0)	// танк на вертикальной линии с игроком
			{
				if(AIplayer::checkWallY_(tankTop/16, playersTanks_[i].getRect().top/16, (tankLeft)/16))
				{
					if(tankTop < playersTanks_[i].getRect().top)
					{
						if (currentSide_ == UP_SIDE){ //сверху игрок, танк едет туда же, между ними нет стен
							Tank::piu_piu();
						}
						else if (currentSide_ == RIGHT_SIDE or currentSide_ == LEFT_SIDE)
						{
							currentSide_ = UP_SIDE;
						}
					}

					if(tankTop < playersTanks_[i].getRect().top)	//снизу игрок, танк едет туда же, между ними нет стен
					{
						if (currentSide_ == DOWN_SIDE)
						{
							Tank::piu_piu();
						}
						else if (currentSide_ == RIGHT_SIDE or currentSide_ == LEFT_SIDE)
						{
							currentSide_ = DOWN_SIDE;
						}
					}
				}
			}

			if(abs(tankTop - playersTanks_[i].getRect().top)<16 and playersTanks_[i].getLife()>0)	// танк на горизонтальной линии с игроком
			{
				if(AIplayer::checkWallY_(tankLeft/16, playersTanks_[i].getRect().left/16, (tankTop)/16))
				{
					if(tankLeft > playersTanks_[i].getRect().left)
					{
						if (currentSide_ == LEFT_SIDE)	//слева игрок, танк едет туда же, между ними нет стен
						{
							Tank::piu_piu();
						}
						else if (currentSide_ == UP_SIDE or currentSide_ == DOWN_SIDE)
						{
							currentSide_ = LEFT_SIDE;
						}
					}

					if(tankLeft < playersTanks_[i].getRect().left)
					{
						if (currentSide_ == RIGHT_SIDE)	//справа игрок, танк едет туда же, между ними нет стен
						{
							Tank::piu_piu();
						}
						else if (currentSide_ == UP_SIDE or currentSide_ == DOWN_SIDE)
						{
							currentSide_ = RIGHT_SIDE;
						}
					}
				}
			}
		}

		if ((!Tank::move(currentSide_)) || (AIplayer::tankCollision_(currentSide_, Tank::getID()))) //если в сторону, в которую хотим ехать, нельзя проехать
		{	
			for (int i = 0; i < 4; ++i)
			{	
				if (!AIplayer::tankCollision_(i*2, Tank::getID()))
				{
					canMove = Tank::move(i*2) || canMove;
				}
			}

			if (!canMove)
			{	
				currentSide_ = (rand()%4)*2;
				Tank::move(currentSide_);
				Tank::piu_piu();
			}
			else
			{	
				currentSide_ = (rand()%4)*2;
			}
		}

		if ((rand()%500) == 0) // с шансом ~3% стреляет просто так
		{
			Tank::piu_piu();
		}

		if (!AIplayer::tankCollision_(currentSide_, Tank::getID())) 
		{ 
			Tank::move(currentSide_); 
		}

		Tank::update(time);
	}

	if (Tank::bulletStatus())
		bulletCollision_();
}


void AIplayer::activation(unsigned int x, unsigned int y) {
	if ((Tank::r_b->getEminems() - 2) > 0)
	{
		Tank::setLife(3);
		nAIPlayers_--;
		startPosition_.left = x;
		startPosition_.top = y;
		Tank::setPosition(x, y, DOWN_SIDE);
	}
}

int AIplayer::bax_bax()
{
	if (Tank::getLife() > 0)
	{
		Tank::setLife(Tank::getLife() - 1);

		if (Tank::getLife() == 0)
		{
			Tank::r_b->setEminems(Tank::r_b->getEminems() - 1);
			AIplayer::activation(startPosition_.left, startPosition_.top);

			mainMap_->randomMap();

			return TANK_KILL;

		}

		return TANK_WOUND;
	}

	return TANK_NONE;
}

void AIplayer::draw(RenderWindow &window)
{
	if (Tank::getLife() != 0)
	{
		Tank::draw(window);
	}
}
