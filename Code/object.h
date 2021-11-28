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
	
	//stone��
	float probeB;	//rect �ظ� 
	float probeL;	//rect ���ʸ� 
	float probeR;	//rect �����ʸ� 

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

	//���漱��
	player* _OPplayer;

public:
	object();
	~object();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void objectImageBundle();

	void setObjectBox();		//�ڽ� 3����
	void setObjectDoor();		//��¦ �¿�
	void setObjectFire();		//��1, ��3
	void setObjectPulley();		//������ 5��
	void setObjectStone();		//�����̴� �� 2��
	void setObjectAwl();		//�۰� 12��(rect�� ������)
	void setObjectLadder();		//��ٸ� 8��(rect�� ������)
	//void setObjectRope();		//���� 5��(rect? pixel?)

	void changeBOX();	//��ź ������ ���� �����
	void changeDoor();	//��ȣ�ۿ��ϸ� �� ����(�̹��� �ٲ�)
	void movePulley();	//�÷��̾� �ö�ͼ� UPŰ�ϸ� �ö�,	�߰��� �������
	void moveStone();	//�и� �� �и���(�ٴ� �ȼ��浹)

	//void pixelRope(); //���� ���� ��ȣ�ۿ��ҷ�?		..rect & UPŰ?

	//��ȣ �浹
	void objectPlayerCollision();

	//get
	//�迭 �ε��� �ϳ��� ������ ��.
	//inline tagObject getPulley(int ArrNum) { return _objectPulley[ArrNum]; }
	/*inline RECT getPulley() { return _objectPulley[0].rc; }*/

	//�迭 ��°�� ������
	//tagObject* getPulley() { return _objectPulley; }


	//���� ����
	void setPlayerMemoryAddressLink(player* OPplayer) { _OPplayer = OPplayer; }
};

