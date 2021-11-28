#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemy.h"
#include "item.h"

#include "obstacleManager.h"

class playGround : public gameNode
{
private:
	player* _player;		//player에서 값 받아와
	enemy* _enemy;
	item* _item;

	obstacleManager* _om;

	bool isDebug;
	
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void debug();
	
	
};

