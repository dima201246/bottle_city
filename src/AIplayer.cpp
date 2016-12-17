#include "../include/obj.hpp"

void AIplayer::init(Texture &image, player *g_other_tanks, int g_other_tanks_num, game_map *l_main_map, bool l_active, int l_life, int l_type) {
	tank::init(image, l_main_map);

	main_map		= l_main_map;

	life			= l_life;
	type			= l_type;
	active			= l_active;
	players_tanks	= g_other_tanks;
	players_num		= g_other_tanks_num;
	currentSide		= 4; // 0 - низ, 1 верх, 2 лево, 3 право, 4- не определено
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
	for (int	i	= 0; i < players_num; i++)	{
		if(abs(tank::getRect().left - players_tanks[i].getRect().left) < 16){ // совпадает с коорд игрока
			if(tank::getRect().top>players_tanks[i].getRect().top) {
				tank::move(1);
			} else {
				tank::move(0);
			}
			tank::piu_piu();
			tank::update(time);
			return;
		}
		if(abs(tank::getRect().top == players_tanks[i].getRect().top)<16){ // совпадает с коорд игрока
			if(tank::getRect().left>players_tanks[i].getRect().left) {
				tank::move(2);
			} else {
				tank::move(3);
			}
			tank::piu_piu();
			tank::update(time);
			return;
		}
	}
	

	
	if (not tank::move(currentSide)) //если в сторону, в которую хотим ехать, нельзя проехать
	{	
		for (int i = 0; i < 4; ++i)
		{
			canMove = tank::move(i) or canMove;
		}
		if (not canMove)
		{
			currentSide = rand()%4;
			tank::piu_piu();
		} else {
			currentSide = rand()%4;	
			tank::move(currentSide);
		}
	}
	
	tank::update(time);
}

void AIplayer::activation(unsigned int x, unsigned int y) {
	active	= true;
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

void AIplayer::draw(RenderWindow &window) {
	if (active) {
		tank::draw(window);
		if (life == 0)
		{
			AIplayer::activation(startPosition.left, startPosition.top);
		}
	}
}