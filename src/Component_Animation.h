#ifndef COMPONENT_ANIMATION
#define COMPONENT_ANIMATION

#include "Entity.h"

#include <map>
#include <string>
#include <vector>

enum EAnimationState {
	IDLE,
	WALK_LEFT,
	WALK_RIGHT,
};

class ITexture;

class CComponent_Animation : public CComponentBase
{
public:
					CComponent_Animation();

	void			Load(const std::string &filepath);
	void			Destroy();

	void			AdvanceFrame();
	void			ChangeAnimationState(EAnimationState newAnimState);

	EAnimationState animState;
	int				currentFrame;

	struct animation_t {
		std::vector<ITexture *>	frames;
		int						maxFrames;
	};

	typedef std::map<EAnimationState, animation_t> animMap_t;
	animMap_t animMap;
};

#endif