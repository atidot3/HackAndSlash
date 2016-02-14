#include "Unit.h"

Unit::Unit() : Object()
{
	
}
void Unit::AddToWorld()
{
	if (!IsInWorld())
	{
		Object::AddToWorld();
	}
}
void Unit::RemoveFromWorld()
{
	if (IsInWorld())
	{
		Object::RemoveFromWorld();
	}
}
void Unit::Update(DWORD p_time)
{
	if (!IsInWorld())
		return;
}
Unit::~Unit()
{
}