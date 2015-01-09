#ifndef COMPONENT_ANIMATION
#define COMPONENT_ANIMATION

#include "Entity.h"

#include <map>
#include <string>
#include <vector>

class CComponent_Physical;
class ITexture;

class CComponent_Animation : public CComponentBase
{
public:
					CComponent_Animation();

	void			Initialize(CEntity *parent);

	void			Load(const std::string &filepath);

	void			AdvanceFrame();
	void			ChangeAnimationState(const std::string &name);

	void			Draw();

	std::string		currentAnimState;
	int				currentFrame;

	CComponent_Physical *physical;

	struct frame_t
	{
		frame_t()
		{
			id = 0;
			texture = NULL;
			hrev = false;
			offsetX = 0.0f;
			offsetY = 0.0f;
		}

		int			id;
		ITexture *	texture;
		bool		hrev;

		float		offsetX;
		float		offsetY;
	};

	struct animation_t
	{
		animation_t()
		{
			maxFrames = 0;
			frameInterval = 0;
		}

		typedef std::pair<int, frame_t> framePair_t;
		std::map<int, frame_t>			frames;
		int								maxFrames;
		int								frameInterval;
	};

	typedef std::pair<std::string, animation_t> animMapPair_t;
	typedef std::map<std::string, animation_t>	animMap_t;
	animMap_t									animMap;
	unsigned int								lastFrameTicks;
};

#endif