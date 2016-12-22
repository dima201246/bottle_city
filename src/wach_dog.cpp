#include "../include/obj.hpp"

WachDog::WachDog(GameMap *GameMap_mainMap, Player *Player_player)
{
	eaglePos_	= GameMap_mainMap->getEaglePos();
	mainMap_	= GameMap_mainMap;
	player_	= Player_player;
}

int WachDog::wach() {
	if (mainMap_->getElement(eaglePos_.posX, eaglePos_.posY) == ' ')
		return WIN_PLAYER;

	if (player_->getLeftTank() == 0)
		return WIN_PLAYER;

	return WIN_NONE;
	// WIN_EMINEM
}