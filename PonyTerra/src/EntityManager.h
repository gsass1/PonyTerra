#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#define MAX_ENTITIES 1024

class CEntity;

class CEntityManager
{
public:
            CEntityManager();
            ~CEntityManager();

    void    AddEntity(CEntity *entity);

    void    RemoveAll();

    void    RemoveEntity(unsigned int id);

    void    UpdateAll(float dtTime);

    void    DrawAll();

private:
    CEntity *entities[MAX_ENTITIES];
};

extern CEntityManager entityMgr;

#endif