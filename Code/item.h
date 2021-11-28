#pragma once
#include "gameNode.h"
#include "player.h"
#include <vector>

struct tagItem
{
	image* img;
	RECT rc;

	float x,  y;
};

class player;

class item : public gameNode
{
private:

	//전방선언
	player* _IPplayer;

public:
	item();
	~item();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void itemImageBundle();

	//상호 충돌
	void itemPlayerCollision();


	//전방 선언
	void setPlayerMemoryAddressLink(player* IPplayer) { _IPplayer = IPplayer; }
};

