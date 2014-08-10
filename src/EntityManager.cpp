#include "Entity.h"
#include "EntityManager.h"

CEntityManager entityMgr;

CEntityManager::CEntityManager()
{
	for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
		entities[i] = NULL;
	}
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
}

void CEntityManager::RemoveEntity(unsigned int id)
{
	if(entities[id] != NULL)
	{
		entities[id]->Destroy();
		delete entities[id];
		entities[id] = NULL;
	}
}

void CEntityManager::UpdateAll(float dtTime)
{
	for(unsigned int i = 0; i < MAX_ENTITIES; i++) {
		if(entities[i] != NULL) {
			entities[i]->Update(dtTime);
		}
	}
}

void CEntityManager::DrawAll()
{
	for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
		if (entities[i] != NULL) {
			entities[i]->Draw();
		}
	}
}