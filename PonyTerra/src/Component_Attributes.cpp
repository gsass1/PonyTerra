#include "Component_Attributes.h"

CComponent_Attributes::CComponent_Attributes(int maxHealth, int maxMana) : maxHealth(maxHealth), maxMana(maxMana) {
	currentHealth = maxHealth;
	currentMana = maxMana;
}

void CComponent_Attributes::Initialize(CEntity *parent) {
	CComponentBase::Initialize(parent);
}

void CComponent_Attributes::AddHealth(int health) {
	currentHealth += health;
	if(currentHealth > maxHealth) {
		currentHealth = maxHealth;
	}
}

void CComponent_Attributes::AddMana(int mana) {
	currentMana += mana;
	if(currentMana > maxMana) {
		currentMana = maxMana;
	}
}

bool CComponent_Attributes::UseHealth(int health) {
	if(currentHealth >= health) {
		currentHealth -= health;
		return true;
	} else {
		return false;
	}
}

bool CComponent_Attributes::UseMana(int mana) {
	if(currentMana >= mana) {
		currentMana -= mana;
		return true;
	}
	else {
		return false;
	}
}