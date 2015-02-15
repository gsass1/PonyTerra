#include "Entity.h"
#include <algorithm>

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
	signalDeath = false;
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
	for (componentListItr_t itr = componentList.begin();
		itr != componentList.end();
		itr++)
	{
		itr->second->Initialize(parent);
	}
}

void CComponentContainer::Add(CComponentBase *component, std::string id)
{
	componentList.insert(componentPair_t(id, component));
}

void CComponentContainer::Remove(const std::string &id)
{
	componentListItr_t itr = componentList.find(id);
	if(itr != componentList.end()) {
		itr->second->Destroy();
		delete itr->second;
		componentList.erase(itr);
	}
}

void CComponentContainer::DestroyAll()
{
	for (componentListItr_t itr = componentList.begin();
		itr != componentList.end();
		itr++)
	{
		itr->second->Destroy();
		//delete itr->second;
	}
	componentList.clear();
}

CComponentBase *CComponentContainer::Get(const std::string &id)
{
	componentListItr_t itr = componentList.find(id);
	if(itr != componentList.end()) {
		return itr->second;
	}
	else {
		return NULL;
	}
}

const CComponentBase *CComponentContainer::Get(const std::string &id) const
{
	componentList_t::const_iterator itr = componentList.find(id);
	if(itr != componentList.end()) {
		return itr->second;
	}
	else {
		return NULL;
	}
}

void CComponentContainer::UpdateAll(float dtTime)
{
	for (componentListItr_t itr = componentList.begin();
		itr != componentList.end();
		itr++)
	{
		itr->second->Update(dtTime);
	}
}

void CComponentContainer::DrawAll()
{
	for (componentListItr_t itr = componentList.begin();
		itr != componentList.end();
		itr++)
	{
		itr->second->Draw();
	}
}

void CComponentContainer::HandleMessage(const CMessage *msg)
{
	for (componentListItr_t itr = componentList.begin();
		itr != componentList.end();
		itr++)
	{
		itr->second->HandleMessage(msg);
	}
}

//-------------------------------------------------

CEntity::CEntity()
{
	id = 0;
	componentContainer = new CComponentContainer(this);
	signalDeath = false;
}

CEntity::~CEntity()
{
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

void CEntity::AddAttribute(std::string attr)
{
	attributes.push_back(attr);
}

bool CEntity::HasAttribute(std::string attr) const
{
	return std::find(attributes.begin(), attributes.end(), attr) != attributes.end();
}

void CEntity::RemoveAttribute(std::string attr)
{
	attributes.erase(std::remove(attributes.begin(), attributes.end(), attr), attributes.end());
}

void CEntity::SignalDeath()
{
	signalDeath = true;
}