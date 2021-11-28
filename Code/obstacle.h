#pragma once
#include "gameNode.h"

class obstacle : public gameNode
{
protected:
	image* _imageName;

	RECT _rc;

	//RECT _rcAwl;
	//RECT _rcLadder;
	//RECT _rcRope;

	int _currentFrameX;
	int _currentFrameY;

	int _count;

	float _x, _y;

public:
	obstacle() {};
	~obstacle() {};		//{} 해주면 여기에 선언

	virtual HRESULT init();
	//virtual HRESULT init(POINT position);							//rect만 그려주기용
	virtual HRESULT init(const char* imageName, POINT position);	//img + rect
	virtual void release();
	virtual void update();
	virtual void render();

	void draw();

	void playerPulleyMove(RECT rc);

	float getMoveY() { return _y; }

	void setRcMoveY(float rcY) { _y = rcY; }

	RECT getRect() { return _rc; }

	//RECT getRectAwl() { return _rcAwl; }
	//RECT getRectLadder() { return _rcLadder; }
	//RECT getRectRope() { return _rcRope; }


};