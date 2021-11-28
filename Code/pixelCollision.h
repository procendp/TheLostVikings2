#pragma once
#include "gameNode.h"


//��ȣ���� - �ϴ� ���� ������		--> ����� ���漱�� �� cpp���Ͽ� include
class player;

class pixelCollision : public gameNode
{
private:
	image* _background;
	//image* _ball;

	player* _player;		//���漱�� ������ ��� ����

	int r;
	int g;
	int b;

	float mapMaxTop;
	float mapMaxBottom;

	float a;
	RECT _rc;
	float _x, _y;
	int _probeY; //probe == Ž��

public:
	pixelCollision();
	~pixelCollision();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayerAddressLink(player* player) { _player = player; }		//�� ���õ� ���� �󲮵��⿴�� _player�� �� �ּҸ� �ް� ��. ��ũ ����

	float getY() { return a; }
	int getR()	{ return r; }
	int getG()	{ return g; };
	int getB()	{ return b; };
};