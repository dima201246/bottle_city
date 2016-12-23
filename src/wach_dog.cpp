#include "../include/obj.hpp"

WachDog::WachDog(GameMap *GameMap_mainMap, Player *Player_player, int int_nPlayer)
{
	eaglePos_	= GameMap_mainMap->getEaglePos();
	nPlayer_	= int_nPlayer;
	mainMap_	= GameMap_mainMap;
	player_		= Player_player;
}

int WachDog::wach() {
	if (mainMap_->getElement(eaglePos_.posX, eaglePos_.posY) == 'd')
		return WIN_EMINEM;

	if (nPlayer_ == 2)
	{
		if ((player_[0].getLife() == 0) && (player_[1].getLife() == 0))
			return WIN_EMINEM;
	}
	else
	{
		if (player_[0].getLife() == 0)
			return WIN_EMINEM;
	}

	if (player_[0].getLeftTank() == 0)
		return WIN_PLAYER;

	return WIN_NONE;
}