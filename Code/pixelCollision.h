#pragma once
#include "gameNode.h"


//상호참조 - 일단 먼저 실행해		--> 헤더에 전방선언 후 cpp파일에 include
class player;

class pixelCollision : public gameNode
{
private:
	image* _background;
	//image* _ball;

	player* _player;		//전방선언 했으니 사용 가능

	int r;
	int g;
	int b;

	float mapMaxTop;
	float mapMaxBottom;

	float a;
	RECT _rc;
	float _x, _y;
	int _probeY; //probe == 탐사

public:
	pixelCollision();
	~pixelCollision();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayerAddressLink(player* player) { _player = player; }		//이 역시도 위에 빈껍데기였던 _player도 원 주소를 받게 됨. 링크 연결

	float getY() { return a; }
	int getR()	{ return r; }
	int getG()	{ return g; };
	int getB()	{ return b; };
};