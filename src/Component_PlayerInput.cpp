#include "Component_PlayerInput.h"
#include "Component_Physical.h"
#include "IInput.h"

CComponent_PlayerInput::CComponent_PlayerInput()
{
	physical = NULL;
}

void CComponent_PlayerInput::Initialize(CEntity *parent)
{
	CComponentBase::Initialize(parent);

	physical = parent->GetComponents()->Get<CComponent_Physical>(COMPONENT_PHYSICAL);
}

void CComponent_PlayerInput::Update(float dtTime)
{
	if(input->KeyPressed(NSKey::NSK_a)) {

		physical->AddVelocity(CVector2f(-1000.0f, 0.0f));

	} else if (input->KeyPressed(NSKey::NSK_d)) {

		physical->AddVelocity(CVector2f(1000.0f, 0.0f));

	}
}

std::string CComponent_PlayerInput::GetID() const
{
	return COMPONENT_PLAYERINPUT;
}