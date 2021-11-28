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

	//���漱��
	player* _IPplayer;

public:
	item();
	~item();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void itemImageBundle();

	//��ȣ �浹
	void itemPlayerCollision();


	//���� ����
	void setPlayerMemoryAddressLink(player* IPplayer) { _IPplayer = IPplayer; }
};

