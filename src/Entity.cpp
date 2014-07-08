#include "Entity.h"

CMessage::CMessage()
{
}

CMessage::~CMessage()
{
}

EMessageType CMessage::GetType() const
{
	return type;
}

//-------------------------------------------------

CComponentBase::CComponentBase()
{
	parent = NULL;
}

CComponentBase::~CComponentBase()
{
}

void CComponentBase::Initialize(CEntity *parent)
{
	this->parent = parent;
}

void CComponentBase::Destroy()
{
}

void CComponentBase::Update(float dtTime)
{
}

void CComponentBase::Draw()
{
}

CEntity *CComponentBase::GetParent() const
{
	return parent;
}

void CComponentBase::HandleMessage(const CMessage *msg)
{
}

//-------------------------------------------------

CComponentContainer::CComponentContainer(CEntity *parent)
{
	this->parent = parent;
}

CComponentContainer::~CComponentContainer()
{
	DestroyAll();
}

void CComponentContainer::CoupleAll()
{
	for (std::vector<CComponentBase *>::iterator itr = components.begin();
		itr != components.end();
		itr++)
	{
		(*itr)->Initialize(parent);
	}
}

void CComponentContainer::Add(CComponentBase *component)
{
	components.push_back(component);
}

void CComponentContainer::Remove(const std::string &id)
{
	for (std::vector<CComponentBase *>::iterator itr = components.begin();
		itr != components.end();
		itr++)
	{
		if((*itr)->GetID() == id) {
			(*itr)->Destroy();
			delete (*itr);
			components.erase(itr);
			return;
		}
	}
}

void CComponentContainer::DestroyAll()
{
	for (std::vector<CComponentBase *>::iterator itr = components.begin();
		itr != components.end();
		itr++)
	{
		(*itr)->Destroy();
		delete (*itr);
		return;
	}
	components.clear();
}

void CComponentContainer::UpdateAll(float dtTime)
{
	for (std::vector<CComponentBase *>::iterator itr = components.begin();
		itr != components.end();
		itr++)
	{
		(*itr)->Update(dtTime);
	}
}

void CComponentContainer::DrawAll()
{
	for (std::vector<CComponentBase *>::iterator itr = components.begin();
		itr != components.end();
		itr++)
	{
		(*itr)->Draw();
	}
}

void CComponentContainer::HandleMessage(const CMessage *msg)
{
	for (std::vector<CComponentBase *>::iterator itr = components.begin();
		itr != components.end();
		itr++)
	{
		(*itr)->HandleMessage(msg);
	}
}

//-------------------------------------------------

CEntity::CEntity()
{
	id = 0;
	componentContainer = new CComponentContainer(this);
}

CEntity::~CEntity()
{
	Destroy();
}

void CEntity::Initialize()
{
	componentContainer->CoupleAll();
}

void CEntity::Destroy()
{
	delete componentContainer;
}

void CEntity::Update(float dtTime)
{
	componentContainer->UpdateAll(dtTime);
}

void CEntity::Draw()
{
	componentContainer->DrawAll();
}

CComponentContainer *CEntity::GetComponents()
{
	return componentContainer;
}

const CComponentContainer *CEntity::GetComponents() const
{
	return componentContainer;
}

unsigned int CEntity::GetID() const
{
	return id;
}