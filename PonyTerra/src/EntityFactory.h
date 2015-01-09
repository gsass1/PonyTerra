#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

class CEntity;

class CEntityFactory
{
public:
                CEntityFactory();
                ~CEntityFactory();

    CEntity *   CreatePlayer();
};

extern CEntityFactory entityFactory;

#endif
