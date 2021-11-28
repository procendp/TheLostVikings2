#pragma once
#include "gameNode.h"
#include "pulley.h"
#include "awl.h"
#include "box.h"
#include "door.h"
#include "fire.h"
#include "ladder.h"
#include "rope.h"
#include "stone.h"
#include "witch.h"
#include <vector>

//투명렉트용
#define MAXAWL 12
#define MAXLADDER 8
#define MAXROPE 5

//투명렉트용
struct tagTrans
{
	RECT rc;

	float x, y;
};

class player;

class obstacleManager :public gameNode
{
private:
	typedef vector<obstacle*>					vObstacle;
	typedef vector<obstacle*>::iterator			viObstacle;

private:
	vObstacle _vBox;
	viObstacle _viBox;

	vObstacle _vDoor;
	viObstacle _viDoor;

	vObstacle _vFire;
	viObstacle _viFire;

	vObstacle _vPulley;
	viObstacle _viPulley;

	vObstacle _vStone;
	viObstacle _viStone;

	vObstacle _vWitch;
	viObstacle _viWitch;

	//투명렉트용
	tagTrans _obstacleAwl[MAXAWL];
	tagTrans _obstacleLadder[MAXLADDER];
	tagTrans _obstacleRope[MAXROPE];

	//전방선언
	player* _player;

	bool isDebug;

public:
	obstacleManager() {};
	~obstacleManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setObstacleImageBundle();		//image 모음

	void setBox();			//박스 3가지
	void setDoor();			//문짝 좌우
	void setFire();			//불1, 불3
	void setPulley();		//도르레 5개
	void setStone();		//움직이는 돌 2개
	void setAwl();			//송곳 12개(rect만 입히기)
	void setLadder();		//사다리 8개(rect만 입히기)
	void setRope();			//로프 5개(rect? pixel?)
	void setWitch();

	void updateBox();		
	void updateDoor();		
	void updateFire();		
	void updatePulley();		
	void updateStone();
	void updateWitch();
	
	//update, render 필요없음
	void updateAwl();				
	void updateLadder();		
	void updateRope();		

	void renderBox();
	void renderDoor();
	void renderFire();
	void renderPulley();
	void renderStone();
	//update, render 필요없음
	void renderAwl();
	void renderLadder();
	void renderRope();
	void renderWitch();

	void changeBOX();		//폭탄 터지면 같이 사라짐
	void changeDoor();		//상호작용하면 문 열림(이미지 바뀜)
	void moveStone();		//밀면 돌 밀리기(바닥 픽셀충돌)

	void collisionPulley();				//플레이어 올라와서 UP키하면 올라감,	중간에 수평잡기

	void motionPulley(int arrNum);		//순서에 맞게 움직이기, 해당 풀리만


	//참고참고
	//get
		//배열 인덱스 하나를 가져온 것.
	//inline tagObject getPulley(int ArrNum) { return _objectPulley[ArrNum]; }
	/*inline RECT getPulley() { return _objectPulley[0].rc; }*/
		//배열 통째로 보내기
	//tagObject* getPulley() { return _objectPulley; }

	

	//get!
	vector<obstacle*> getVPulley() { return _vPulley; }
	vector<obstacle*>::iterator getVIPulley() { return _viPulley; }


	vector<obstacle*> getVBox() { return _vBox; }
	vector<obstacle*>::iterator getVIBox() { return _viBox; }

	vector<obstacle*> getVDoor() { return _vDoor; }
	vector<obstacle*>::iterator getVIDoor() { return _viDoor; }

	vector<obstacle*> getVFire() { return _vFire; }
	vector<obstacle*>::iterator getVIFire() { return _viFire; }
	vector<obstacle*> getVStone() { return _vStone; }
	vector<obstacle*>::iterator getVIStone() { return _viStone; }

	vector<obstacle*> getVWitch() { return _vWitch; }
	vector<obstacle*>::iterator getVIWitch() { return _viWitch; }

	//get
	RECT getRopeRC() { return _obstacleRope->rc; }
	RECT getAwlRC() { return _obstacleAwl->rc; }

	//tagTrans* getAwl() { return _obstacleAwl; }		//배열 통째로 보내기?
	inline RECT getAwl0() { return _obstacleAwl[0].rc; }
	inline RECT getAwl1() { return _obstacleAwl[1].rc; }
	inline RECT getAwl2() { return _obstacleAwl[2].rc; }
	inline RECT getAwl3() { return _obstacleAwl[3].rc; }
	inline RECT getAwl4() { return _obstacleAwl[4].rc; }
	inline RECT getAwl5() { return _obstacleAwl[5].rc; }

	//set
	void setRopeRC(RECT ropeRC) { _obstacleRope->rc = ropeRC; }
	void setAwlRC(RECT awlRC) { _obstacleAwl->rc = awlRC; }




	void setPlayerMemoryAddressLink(player* player) { _player = player; }
};

