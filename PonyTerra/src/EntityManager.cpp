#include "Entity.h"
#include "EntityManager.h"
#include "Game.h"
#include "Component_Physical.h"
#include "IGraphics.h"
#include "MathUtil.h"

CEntityManager entityMgr;

CEntityManager::CEntityManager()
{
	for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
		entities[i] = NULL;
	}
	count = 0;
}

CEntityManager::~CEntityManager()
{
}

void CEntityManager::AddEntity(CEntity *entity)
{
	for(unsigned int i = 0; i < MAX_ENTITIES; i++) {
		if(entities[i] == NULL) {
			entities[i] = entity;
			entity->id = i;
			count++;
			return;
		}
	}
}

void CEntityManager::RemoveAll()
{
    for(unsigned int i = 0; i < MAX_ENTITIES; i++) {
        if(entities[i] != NULL) {
            entities[i]->Destroy();
            delete entities[i];
            entities[i] = NULL;
        }
    }
	count = 0;
}

void CEntityManager::RemoveEntity(unsigned int id)
{
	if(entities[id] != NULL)
	{
		entities[id]->Destroy();
		delete entities[id];
		entities[id] = NULL;
		count--;
	}
}

void CEntityManager::UpdateAll(float dtTime)
{
	for(unsigned int i = 0; i < MAX_ENTITIES; i++) {
		if(entities[i] != NULL) {
			entities[i]->Update(dtTime);
			if(entities[i]->signalDeath) {
				RemoveEntity(i);
				continue;
			}

			for(unsigned int j = 0; j < MAX_ENTITIES; j++) {
				if(entities[j] != NULL) {
					/* Do not compare to itself */
					if(entities[j] == entities[i]) {
						continue;
					}
					auto phys = GetComponent<CComponent_Physical>(entities[i]);
					if(phys) {
						auto entityPhys = GetComponent<CComponent_Physical>(entities[j]);
						if(entityPhys) {
							if(entityPhys->rect.Collides(phys->rect)) {
								CMessage_CollideWithEntity msg;
								msg.entity = entities[j];
								entities[i]->GetComponents()->HandleMessage(&msg);
							}
						}
					}
				}
			}
		}
	}
}

void CEntityManager::DrawAll()
{
	for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
		if (entities[i] != NULL) {
			entities[i]->Draw();
			auto phys = GetComponent<CComponent_Physical>(entities[i]);
			if(phys && game_local.showBoundingBoxes) {
				graphics->DrawRect(CRect(phys->rect.pos - game_local.GetViewRect().pos, phys->rect.width, phys->rect.height), CColor(255, 0, 255, 128));
			}
		}
	}
}

CEntity *CEntityManager::GetNearbyEntity(CEntity *entity, float radius)
{
	for(unsigned int i = 0; i < MAX_ENTITIES; i++) {
		if(entities[i] != NULL) {
			/* Do not compare to itself */
			if(entities[i] == entity) {
				continue;
			}
			auto phys = GetComponent<CComponent_Physical>(entities[i]);
			if(phys) {
				auto entityPhys = GetComponent<CComponent_Physical>(entity);
				if(entityPhys) {
					float xdist = entityPhys->rect.pos.x - phys->rect.pos.x;
					float ydist = entityPhys->rect.pos.y - phys->rect.pos.y;
					float dist = Math::Sqrtf(std::powf(xdist, 2) + std::powf(ydist, 2));
					if(dist <= radius) {
						return entities[i];
					}
				}
			}
		}
	}
	return nullptr;
}