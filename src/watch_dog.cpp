#include "../include/obj.hpp"

WatchDog::WatchDog(GameMap *GameMap_mainMap, Player *Player_player, int int_nPlayer)
{
	nPlayer_	= int_nPlayer;
	mainMap_	= GameMap_mainMap;
	player_		= Player_player;
}

int WatchDog::wach()
{
	if (mainMap_->getElement(mainMap_->getEaglePos().posX, mainMap_->getEaglePos().posY) == 'd')
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