#pragma once
#include "GameNode.h"
#include "stdafx.h"




struct  tagPalette
{
	RECT rc;
	int paletteFrameX;
	int paletteFrameY;

};

class tileMapNode : public GameNode
{
private:
	tagPalette _sampleTile;

public:


};

