#ifndef COMPONENT_ATTRIBUTES_H
#define COMPONENT_ATTRIBUTES_H

#include "Entity.h"

class CComponent_Attributes : public CComponentBase {
public:
	CComponent_Attributes(int maxHealth = 100, int maxMana = 100);

	void Initialize(CEntity *parent);

	void AddHealth(int health);
	void AddMana(int mana);
	
	bool UseHealth(int health);
	bool UseMana(int mana);

	float GetHealthPercentage() const;
	float GetManaPercentage() const;

	int currentHealth;
	int currentMana;
	int maxHealth;
	int maxMana;
};

#endif