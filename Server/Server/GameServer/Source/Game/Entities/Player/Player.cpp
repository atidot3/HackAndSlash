#include "Player.h"

Player::Player() : Unit()
{
	m_objectTypeId = TYPEID_PLAYER;
	disconnected = true;
	life = 100;
	level = 1;
	classe = 0;
}
void Player::AddToWorld()
{
	Unit::AddToWorld();
}
void Player::RemoveFromWorld()
{
	Unit::RemoveFromWorld();
}
void Player::Update(DWORD p_time)
{
	if (!IsInWorld())
		return;
	Unit::Update(p_time);
}