#ifndef COMPONENT_GAMEENTITY_H
#define COMPONENT_GAMEENTITY_H

#include "Entity.h"
#include "Rect.h"

//
// Holds basic entity information
//
class CComponent_GameEntity : public CComponentBase
{
public:
	const std::string &GetID() const
	{
		return "GameEntity";
	}

	CRect rect;
	CVector2f velocity;
};

#endif