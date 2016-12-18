#include "../include/obj.hpp"

void AIplayer::init(Texture &image, player *g_other_tanks, int g_other_tanks_num, game_map *l_main_map, right_bar *l_r_b, bool l_active, int l_life, int l_type) {
	tank::init(image, l_main_map, l_r_b);

	main_map		= l_main_map;

	life			= l_life;
	type			= l_type;
	active			= l_active;
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
	bool	wall			= true;
	char	temp;
	int 	tankTop			= tank::getRect().top;
	int 	tankLeft		= tank::getRect().left;
	int 	maxX			= main_map->getMaxX();
	int 	maxY			= main_map->getMaxY();
	for (int	i	= 0; i < players_num; i++)	{
		if(abs(tankLeft - players_tanks[i].getRect().left) < 16){ // совпадает с коорд игрока
			if(tankTop<players_tanks[i].getRect().top) {

					for (int k = 0; k < maxY-tankTop/16; ++k)
					{	
						temp = main_map->getElement((tankLeft/16), (tankTop/16+k));
						if (temp == 's'||temp == 'v'||temp == 'i')
						{
							wall = true and wall;
						} 
						else
						{
							break;
							wall = false;
						}
					}
				
				if (wall) {
					currentSide = DOWN_SIDE;
					tank::piu_piu();
				}
			} else {

					for (int k = 0; k < maxY-players_tanks[i].getRect().top/16; ++k)
					{	
						temp = main_map->getElement((tankLeft/16), (players_tanks[i].getRect().top/16+k));
						if (temp == 's'||temp == 'v'||temp == 'i')
						{
							wall = true and wall;
						} 
						else
						{	
							break;
							wall = false;
						}
					}

				if (wall) {
					currentSide = UP_SIDE;
					tank::piu_piu();
				}
			}
			wall = true;
			if (rand()%players_num == 0) {
				return;
			}		
		}
		
		if(abs(tankTop - players_tanks[i].getRect().top)<16){ // совпадает с коорд игрока
			if(tankLeft>players_tanks[i].getRect().left) {
				
					for (int k = 0; k < maxX-players_tanks[i].getRect().left/16; ++k)
					{	
						temp = main_map->getElement((players_tanks[i].getRect().left/16+k), (tankTop/16));
						if (temp == 's'||temp == 'v'||temp == 'i')
						{
							wall = true and wall;
						} 
						else
						{
							break;
							wall = false;
						}
					}
				
				if (wall) {
					currentSide = LEFT_SIDE;
					tank::piu_piu();
				}
			} else {
				
					for (int k = 0; k < maxX-tankLeft/16; ++k)
					{	
						temp = main_map->getElement((tankLeft/16+k), (tankTop/16));
						if (temp == 's'||temp == 'v'||temp == 'i')
						{
							wall = true and wall;
						} 
						else
						{
							break;
							wall = false;
						}
					}
				
				if (wall) {
					currentSide = RIGHT_SIDE;
					tank::piu_piu();
				}
			}
			wall = true;
			if (rand()%players_num == 0) {
				return;
			}
		}
	}
	
	
	if (not tank::move(currentSide)) //если в сторону, в которую хотим ехать, нельзя проехать
	{	
		for (int i = 0; i < 4; ++i)
		{	
			canMove = tank::move(i*2) or canMove;
		}
		if (not canMove)
		{
			tank::piu_piu();
		} else {	
			currentSide = (rand()%4)*2;
		}
	}
	tank::move(currentSide);
	tank::update(time);
}


void AIplayer::activation(unsigned int x, unsigned int y) {
	active	= true;
	life = 3;
	startPosition.left = x;
	startPosition.top = y;
	tank::setPosition(x, y, DOWN_SIDE);
}

FloatRect AIplayer::getRect() {
	return tank::getRect();
}

int AIplayer::getLife() {
	return life;
}

void AIplayer::bulletDestroy() {
	tank::bulletDestroy();
}

FloatRect AIplayer::getBulletRect() {
	return tank::getBulletRect();
}

void AIplayer::bax_bax() {
	if (life > 0)
		life--;
}

void AIplayer::draw(RenderWindow &window) {
	if (active) {
		if (life == 0)
		{
			AIplayer::activation(startPosition.left, startPosition.top);
			tank::draw(window);
		} else {		
			tank::draw(window);
		}
	}
}