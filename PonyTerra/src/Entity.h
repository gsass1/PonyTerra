#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include <typeinfo>

enum class EMessageType
{
	NONE,
};

class CMessage
{
public:
						CMessage();
						~CMessage();

	EMessageType		GetType() const;

private:
	EMessageType		type;
};

class CEntity;

class CComponentBase
{
public:
						CComponentBase();
	virtual				~CComponentBase();

	virtual void		Initialize(CEntity *parent);

	virtual void		Destroy();

	virtual void		Update(float dtTime);

	virtual void		Draw();

	CEntity *			GetParent() const;

	virtual void		HandleMessage(const CMessage *msg);

protected:
	CEntity *			parent;

	bool				signalDeath;

	friend class		CComponentContainer;
};

class CComponentContainer
{
public:
						CComponentContainer(CEntity *parent);
						~CComponentContainer();

	void				CoupleAll();

	template<class T>
	void				Add(T *component)
	{
		Add(component, typeid(component).name());
	}

	void				Add(CComponentBase *component, std::string key);

	template<class T>
	void				Remove()
	{
		Remove(typeid(T).name());
	}

	void				Remove(const std::string &id);

	void				DestroyAll();

	template<class T> T *Get()
	{
		return dynamic_cast<T *>(Get(typeid(T*).name()));
	}

	template<class T> const T *Get() const
	{
		return dynamic_cast<T *>(Get(typeid(T*).name()));
	}

	CComponentBase *	Get(const std::string &id);
	const CComponentBase *	Get(const std::string &id) const;

	void				UpdateAll(float dtTime);

	void				DrawAll();

	void				HandleMessage(const CMessage *msg);

private:
	CEntity *			parent;
	typedef std::map<std::string, CComponentBase *> componentList_t;
	typedef componentList_t::iterator componentListItr_t;
	typedef std::pair<std::string, CComponentBase *> componentPair_t;
	componentList_t		componentList;
};

class CEntity
{
public:
						CEntity();
						~CEntity();

	void				Initialize();

	void				Destroy();

	void				Update(float dtTime);

	void				Draw();

	CComponentContainer *GetComponents();
	const CComponentContainer *GetComponents() const;

	unsigned int		GetID() const;

	void				AddAttribute(std::string attr);
	bool				HasAttribute(std::string attr) const;
	void				RemoveAttribute(std::string attr);

	void				SignalDeath();

private:
	friend class		CEntityManager;

	unsigned int		id;

	CComponentContainer *componentContainer;

	std::vector<std::string> attributes;

	bool				signalDeath;
};

template<typename T>
T *GetComponent(CEntity *entity)
{
	return entity->GetComponents()->Get<T>();
}

template<typename T>
const T *GetComponent(const CEntity *entity)
{
	return entity->GetComponents()->Get<T>();
}

#endif