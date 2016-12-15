#include "obj.hpp"

void AIplayer::init(Texture &image, player *g_other_tanks, int g_other_tanks_num, game_map *l_main_map, bool l_active, int l_life, int l_type) {
	tank::init(image, l_main_map);

	life			= l_life;
	type			= l_type;
	active			= l_active;
	players_tanks	= g_other_tanks;
	players_num		= g_other_tanks_num;
	currentSide		= 4; // 0 - низ, 1 верх, 2 лево, 3 право, 4- не определено
}

void AIplayer::update(float time) {
	bool 	canMove			= false;
	if(tank::getRect().left == -1){ // совпадает с коорд игрока
		tank::moveDown();
		tank::piu_piu();
		tank::update(time);
		return;
	}
	if(tank::getRect().top == -1){ // совпадает с коорд игрока
		tank::moveRight();
		tank::piu_piu();
		tank::update(time);
		return;
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
		}
	}

	tank::update(time);
}

void AIplayer::activation(unsigned int x, unsigned int y) {
	active	= true;
	//startPosition.left = x;
	//startPosition.top = y;
	tank::setPosition(x, y, DOWN_SIDE);
}


void AIplayer::draw(RenderWindow &window) {
	if (active) {
		tank::draw(window);
		//if (life == 0)
		//{
			//AIplayer::activation(startPosition.left, startPosition.top);
			//tank::draw(window);
		//}
	}
}