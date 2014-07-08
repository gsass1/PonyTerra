#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

class IEntity;

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

	virtual void		Destroy() = 0;

	virtual void		Update(float dtTime) = 0;

	virtual void		Draw() = 0;

	CEntity *			GetParent() const;

	virtual const std::string &GetID() const = 0;

	virtual void		HandleMessage(const CMessage *msg) = 0;

protected:
	CEntity *			parent;
};

class CComponentContainer
{
public:
						CComponentContainer(CEntity *parent);
						~CComponentContainer();

	void				CoupleAll();

	void				Add(CComponentBase *component);

	void				Remove(const std::string &id);

	void				DestroyAll();

	CComponentBase *	Get(const std::string &id);

	template<class T> T *Get(const std::string &id)
	{
		return (T *)Get(id);
	}

	void				UpdateAll(float dtTime);

	void				DrawAll();

	void				HandleMessage(const CMessage *msg);

private:
	CEntity *			parent;
	std::vector<CComponentBase *> components;
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

private:
	CComponentContainer *componentContainer;
};

#endif