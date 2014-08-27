#ifndef DRAWQUERY_H
#define DRAWQUERY_H

#include "Rect.h"
#include "Vector2.h"

#include <vector>

#define QLAYER_FRONT	0
#define QLAYER_GUI		50
#define QLAYER_PLAYER	100
#define QLAYER_ENTITY	150
#define QLAYER_LEVEL	200

#define MAX_QUERIES 1024

class ITexture;

class CDrawQuery
{
public:
					CDrawQuery();
					~CDrawQuery();

	void			Query(ITexture *tex, CRect rect, unsigned char layer);

	void			BeginFrame();

	void			EndFrame();

	void			DrawAll();

private:
	struct query_t
	{
		ITexture *tex;
		CRect rect;
		unsigned char layer;
	};

	query_t			queries[MAX_QUERIES];

	unsigned int	queriesAddedThisFrame;
};

extern CDrawQuery *drawQuery;

#endif