#pragma once
#include "gameNode.h"
#include "player.h"
#include <vector>

#define MAXAWL 12
#define MAXLADDER 8
#define MAXROPE 5
#define MAXPULLEY 5

struct tagObject
{
	image* img;
	RECT rc;

	float x, y;
	
	//stone용
	float probeB;	//rect 밑면 
	float probeL;	//rect 왼쪽면 
	float probeR;	//rect 오른쪽면 

};

class player;

class object : public gameNode
{
private:
	typedef vector<object*>						vObject;
	typedef vector<object*>::iterator			viObject;

private:
	vObject _vPulley;
	viObject _viPulley;

	tagObject _objectBox[3];
	tagObject _objectDoor[3];
	tagObject _objectFire[4];
	//tagObject _objectPulley[5];
	tagObject _objectStone[2];
	tagObject _objectAwl[MAXAWL];
	tagObject _objectLadder[MAXLADDER];
	//tagObject _objectRope[MAXROPE];

	//전방선언
	player* _OPplayer;

public:
	object();
	~object();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void objectImageBundle();

	void setObjectBox();		//박스 3가지
	void setObjectDoor();		//문짝 좌우
	void setObjectFire();		//불1, 불3
	void setObjectPulley();		//도르레 5개
	void setObjectStone();		//움직이는 돌 2개
	void setObjectAwl();		//송곳 12개(rect만 입히기)
	void setObjectLadder();		//사다리 8개(rect만 입히기)
	//void setObjectRope();		//로프 5개(rect? pixel?)

	void changeBOX();	//폭탄 터지면 같이 사라짐
	void changeDoor();	//상호작용하면 문 열림(이미지 바뀜)
	void movePulley();	//플레이어 올라와서 UP키하면 올라감,	중간에 수평잡기
	void moveStone();	//밀면 돌 밀리기(바닥 픽셀충돌)

	//void pixelRope(); //로프 뭐로 상호작용할래?		..rect & UP키?

	//상호 충돌
	void objectPlayerCollision();

	//get
	//배열 인덱스 하나를 가져온 것.
	//inline tagObject getPulley(int ArrNum) { return _objectPulley[ArrNum]; }
	/*inline RECT getPulley() { return _objectPulley[0].rc; }*/

	//배열 통째로 보내기
	//tagObject* getPulley() { return _objectPulley; }


	//전방 선언
	void setPlayerMemoryAddressLink(player* OPplayer) { _OPplayer = OPplayer; }
};

