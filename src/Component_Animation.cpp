#include "Component_Animation.h"
#include "ITexture.h"
#include "IResourceManager.h"
#include "XML.h"

CComponent_Animation::CComponent_Animation()
{
	animState = EAnimationState::IDLE;
	currentFrame = 0;
}

void CComponent_Animation::Load(const std::string &filepath)
{
	TiXmlDocument doc;
	if(!doc.LoadFile(filepath.c_str())) {
		// ded
		return;
	}


}

void CComponent_Animation::Destroy()
{
	
}