#include "Component_Animation.h"
#include "Component_PlayerInput.h"
#include "Component_Physical.h"
#include "IInput.h"

CComponent_PlayerInput::CComponent_PlayerInput()
{
	animation = NULL;
	physical = NULL;
}

void CComponent_PlayerInput::Initialize(CEntity *parent)
{
	CComponentBase::Initialize(parent);

	animation = parent->GetComponents()->Get<CComponent_Animation>();
	physical = parent->GetComponents()->Get<CComponent_Physical>();
}

void CComponent_PlayerInput::Update(float dtTime)
{
	if(input->KeyPressed(NSKey::NSK_a)) {

		physical->AddVelocity(CVector2f(-100.0f, 0.0f));
		animation->ChangeAnimationState("Walk_Left");
		animation->AdvanceFrame();

	} else if (input->KeyPressed(NSKey::NSK_d)) {

		physical->AddVelocity(CVector2f(100.0f, 0.0f));
		animation->ChangeAnimationState("Walk_Right");
		animation->AdvanceFrame();

	} else {
		
		animation->ChangeAnimationState("Idle_Left");

	}

	if(input->KeyPressed(NSKey::NSK_SPACE)) {
		
		if(!physical->isInAir) {
			physical->AddVelocity(CVector2f(0.0f, 2000.0f));
		}

	}
}