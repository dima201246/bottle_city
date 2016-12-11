#include "obj.hpp"

void AIplayer::init(Texture &image, player *g_other_tanks, int g_other_tanks_num, game_map *l_main_map, bool l_active, int l_life, int l_type) {
	tank::init(image, l_main_map);

	life			= l_life;
	type			= l_type;
	active			= l_active;
	players_tanks	= g_other_tanks;
	players_num		= g_other_tanks_num;
}

void AIplayer::update(float time) {
	/*Место для ИИ*/

	tank::update(time);
}

void AIplayer::activation(unsigned int x, unsigned int y) {
	active	= true;

	tank::setPosition(x, y);
}


void AIplayer::draw(RenderWindow &window) {
	if (active)
		tank::draw(window);
}