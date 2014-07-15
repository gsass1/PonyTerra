#include "Component_Animation.h"
#include "ITexture.h"
#include "IResourceManager.h"
#include "StringUtils.h"
#include "XML.h"

#define ANIMCONF_DEFAULT_NAME "animConf"

CComponent_Animation::CComponent_Animation()
{
	currentFrame = 0;
}

void CComponent_Animation::Load(const std::string &filepath)
{
	TiXmlDocument doc;
	if (!doc.LoadFile(StrUtl::FormatString("data/res/tex/%s/%s", filepath.c_str(), ANIMCONF_DEFAULT_NAME).c_str())) {
		// ASSERT pls
		return;
	}

	TiXmlElement *animRoot = (TiXmlElement *)doc.FirstChild();

	std::string animName = animRoot->Attribute("Name");

	TiXmlElement *sequence;
	FOR_EACH_ELEM(animRoot, sequence) {
		animation_t animation;

		std::string sequenceName = sequence->Attribute("Name");

		TiXmlElement *frameElem;
		FOR_EACH_ELEM(sequence, frameElem) {
			int id = atoi(frameElem->Attribute("ID"));
			std::string path = frameElem->Attribute("Path");

			frame_t frame;
			frame.id = id;
			frame.texture = resMgr->GetTexture(path);

			std::string flags;

			if (frameElem->Attribute("Flags") != NULL) {
				flags = frameElem->Attribute("Flags");
			}

			if(flags.find("hrev") != std::string::npos) {
				frame.hrev = true;
			}

			animation_t::framePair_t framePair(id, frame);
			animation.frames.insert(framePair);
		}

		animation.maxFrames = (int)animation.frames.size();
		animMap.insert(animMapPair_t(sequenceName, animation));
	}
}

void CComponent_Animation::AdvanceFrame()
{
	currentFrame++;
	if(currentFrame > animMap[currentAnimState].maxFrames) {
		currentFrame = 0;
	}
}

void CComponent_Animation::ChangeAnimationState(const std::string &name)
{
	currentFrame = 0;
	currentAnimState = name;
}

void CComponent_Animation::Draw()
{
	// TODO
}