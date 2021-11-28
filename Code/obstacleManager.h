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

//����Ʈ��
#define MAXAWL 12
#define MAXLADDER 8
#define MAXROPE 5

//����Ʈ��
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

	//����Ʈ��
	tagTrans _obstacleAwl[MAXAWL];
	tagTrans _obstacleLadder[MAXLADDER];
	tagTrans _obstacleRope[MAXROPE];

	//���漱��
	player* _player;

	bool isDebug;

public:
	obstacleManager() {};
	~obstacleManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setObstacleImageBundle();		//image ����

	void setBox();			//�ڽ� 3����
	void setDoor();			//��¦ �¿�
	void setFire();			//��1, ��3
	void setPulley();		//������ 5��
	void setStone();		//�����̴� �� 2��
	void setAwl();			//�۰� 12��(rect�� ������)
	void setLadder();		//��ٸ� 8��(rect�� ������)
	void setRope();			//���� 5��(rect? pixel?)
	void setWitch();

	void updateBox();		
	void updateDoor();		
	void updateFire();		
	void updatePulley();		
	void updateStone();
	void updateWitch();
	
	//update, render �ʿ����
	void updateAwl();				
	void updateLadder();		
	void updateRope();		

	void renderBox();
	void renderDoor();
	void renderFire();
	void renderPulley();
	void renderStone();
	//update, render �ʿ����
	void renderAwl();
	void renderLadder();
	void renderRope();
	void renderWitch();

	void changeBOX();		//��ź ������ ���� �����
	void changeDoor();		//��ȣ�ۿ��ϸ� �� ����(�̹��� �ٲ�)
	void moveStone();		//�и� �� �и���(�ٴ� �ȼ��浹)

	void collisionPulley();				//�÷��̾� �ö�ͼ� UPŰ�ϸ� �ö�,	�߰��� �������

	void motionPulley(int arrNum);		//������ �°� �����̱�, �ش� Ǯ����


	//��������
	//get
		//�迭 �ε��� �ϳ��� ������ ��.
	//inline tagObject getPulley(int ArrNum) { return _objectPulley[ArrNum]; }
	/*inline RECT getPulley() { return _objectPulley[0].rc; }*/
		//�迭 ��°�� ������
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

	//tagTrans* getAwl() { return _obstacleAwl; }		//�迭 ��°�� ������?
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

