#include "Precompiled.h"

#include "Component_Animation.h"
#include "Component_PlayerInput.h"
#include "Component_Physical.h"
#include "IInput.h"
#include "Game.h"

CComponent_PlayerInput::CComponent_PlayerInput()
{
	animation = NULL;
	physical = NULL;
	noclip = false;
}

void CComponent_PlayerInput::Initialize(CEntity *parent)
{
	CComponentBase::Initialize(parent);

	animation = parent->GetComponents()->Get<CComponent_Animation>();
	physical = parent->GetComponents()->Get<CComponent_Physical>();
	
	animation->ChangeAnimationState("Idle_Left");
}

void CComponent_PlayerInput::Update(float dtTime)
{
	if(noclip) {
		UpdateNoClip(dtTime);
		return;
	}

	if(game_local.KeyPressedIngame(NSKey::NSK_a)) {

		physical->AddVelocity(CVector2f(-100.0f, 0.0f));
		animation->ChangeAnimationState("Walk_Left");
		animation->AdvanceFrame();

    } else if(game_local.KeyPressedIngame(NSKey::NSK_d)) {

		physical->AddVelocity(CVector2f(100.0f, 0.0f));
		animation->ChangeAnimationState("Walk_Right");
		animation->AdvanceFrame();

	} else {
		
		if (animation->currentAnimState == "Walk_Left") {
			animation->ChangeAnimationState("Idle_Left");
		} else if (animation->currentAnimState == "Walk_Right") {
			animation->ChangeAnimationState("Idle_Right");
		}

	}

    if(game_local.KeyPressedIngame(NSKey::NSK_SPACE)) {
		
		if(!physical->isInAir) {
			physical->AddVelocity(CVector2f(0.0f, 2000.0f));
		}

	}
}

void CComponent_PlayerInput::SetNoClip(bool noclip)
{
	this->noclip = noclip;
    physical->disableMotion = noclip;
}

bool CComponent_PlayerInput::ToggleNoClip() {
	SetNoClip(!noclip);
	return noclip;
}

void CComponent_PlayerInput::UpdateNoClip(float dtTime)
{
    if(game_local.KeyPressedIngame(NSKey::NSK_a)) {
		physical->rect.pos += CVector2f(-2500.0f * dtTime, 0.0f);
    } else if(game_local.KeyPressedIngame(NSKey::NSK_d)) {
		physical->rect.pos += CVector2f(2500.0f * dtTime, 0.0f);
	}

    if(game_local.KeyPressedIngame(NSKey::NSK_w)) {
		physical->rect.pos += CVector2f(0.0f, 2500.0f * dtTime);
    } else if(game_local.KeyPressedIngame(NSKey::NSK_s)) {
		physical->rect.pos += CVector2f(0.0f, -2500.0f * dtTime);
	}
}