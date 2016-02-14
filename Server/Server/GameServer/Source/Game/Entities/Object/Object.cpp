#include "Object.h"
#include "../Player/Player.h"

Object::Object()
{
	m_objectTypeId = TYPEID_OBJECT;

	m_inWorld = false;
}
Object::~Object()
{
	
}
void Object::AddToWorld()
{
	if (m_inWorld)
		return;

	m_inWorld = true;
}
void Object::RemoveFromWorld()
{
	if (!m_inWorld)
		return;

	m_inWorld = false;
}
void Object::DestroyForPlayer(Player* target) const
{
	CNtlPacket packet(sizeof(0));

	target->getClient()->getSession()->SendPacket(&packet);
}
