#ifndef __UNIT_H
#define __UNIT_H

#include "../Object/Object.h"
#include "../ObjectGUID.h"

class		Object;

class Unit : public Object
{
public:
	Unit();
	virtual ~Unit();
	void AddToWorld() override;
	void RemoveFromWorld() override;
	virtual void Update(DWORD time) override;

	/*virtual bool UpdateStats(Stats stat) = 0;
	virtual bool UpdateAllStats() = 0;
	virtual void UpdateResistances(uint32 school) = 0;
	virtual void UpdateAllResistances();
	virtual void UpdateArmor() = 0;
	virtual void UpdateMaxHealth() = 0;
	virtual void UpdateMaxPower(Powers power) = 0;
	virtual void UpdateAttackPowerAndDamage(bool ranged = false) = 0;
	virtual void UpdateDamagePhysical(WeaponAttackType attType);
	float GetTotalAttackPowerValue(WeaponAttackType attType) const;
	float GetWeaponDamageRange(WeaponAttackType attType, WeaponDamageRange type) const;
	void SetBaseWeaponDamage(WeaponAttackType attType, WeaponDamageRange damageRange, float value) { m_weaponDamage[attType][damageRange] = value; }
	virtual void CalculateMinMaxDamage(WeaponAttackType attType, bool normalized, bool addTotalPct, float& minDamage, float& maxDamage) = 0;
	uint32 CalculateDamage(WeaponAttackType attType, bool normalized, bool addTotalPct);*/
};

#endif