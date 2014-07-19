#include "Component_Animation.h"
#include "Component_Physical.h"
#include "Game.h"
#include "IFilesystem.h"
#include "IGraphics.h"
#include "ITexture.h"
#include "IResourceManager.h"
#include "StringUtils.h"
#include "XML.h"

#define ANIMCONF_DEFAULT_NAME "animConf"

CComponent_Animation::CComponent_Animation()
{
	currentFrame = 0;
	physical = NULL;
}

void CComponent_Animation::Initialize(CEntity *parent)
{
	CComponentBase::Initialize(parent);

	physical = parent->GetComponents()->Get<CComponent_Physical>();
}

void CComponent_Animation::Load(const std::string &filepath)
{
	TiXmlDocument doc;
	if (!doc.LoadFile((StrUtl::FormatString("%s/data/res/tex/%s/%s", fileSystem->GetBasePath().c_str(), filepath.c_str(), ANIMCONF_DEFAULT_NAME)).c_str())) {
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
			frame.texture = resMgr->GetTexture(StrUtl::FormatString("data/res/tex/%s/%s", filepath.c_str(), path.c_str()), CColor(255, 0, 255));

			std::string flags;

			if (frameElem->Attribute("Flags") != NULL) {
				flags = frameElem->Attribute("Flags");
			}

			if(flags.find("hrev") != std::string::npos) {
				frame.hrev = true;
			}

			if (frameElem->Attribute("OffsetX") != NULL) {
				frame.offsetX = (float)atoi(frameElem->Attribute("OffsetX"));
			}

			if (frameElem->Attribute("OffsetY") != NULL) {
				frame.offsetY = (float)atoi(frameElem->Attribute("OffsetY"));
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
	if(currentFrame == animMap[currentAnimState].maxFrames) {
		currentFrame = 0;
	}
}

void CComponent_Animation::ChangeAnimationState(const std::string &name)
{
	if(currentAnimState == name) {
		return;
	}
	currentFrame = 0;
	currentAnimState = name;
}

void CComponent_Animation::Draw()
{
	frame_t frame = animMap[currentAnimState].frames[currentFrame];

	if (frame.hrev) {
		graphics->SetOrtho(graphics->GetWidth(), 0, 0, graphics->GetHeight());
	}

	CVector2f pos = (physical->rect.pos + CVector2f(frame.offsetX, frame.offsetY)) - game_local.GetViewRect().pos;

	graphics->DrawTexture(frame.texture, pos);

	if (frame.hrev) {
		graphics->ResetOrtho();
	}
}