#pragma once
#include "gameNode.h"
#include "player.h"

#define BOMBMAX 1	//��..

enum class PIRATESTATE
{
	MOVE_RIGHT,
	MOVE_LEFT,
	ATTACK_RIGHT,
	ATTACK_LEFT,
	DEATH_RIGHT,
	DEATH_LEFT
};
enum class SKELETONSTATE
{
	MOVE_RIGHT,
	MOVE_LEFT,
	ATTACK_RIGHT,
	ATTACK_LEFT,
	DEATH_RIGHT,
	DEATH_LEFT
};

struct tagPirate
{
	image* img;
	RECT rc;

	float x, y;
	float gravity;

	//�����ӿ�
	int frameCount;
	int frameIndex;

	bool moveFirst;

	PIRATESTATE state;
};
struct tagSkeleton
{
	image* img;
	RECT rc;

	float x, y;
	float gravity;

	//�����ӿ�
	int frameCount;
	int frameIndex;

	bool moveFirst;

	SKELETONSTATE state;
};
struct tagTankBomb
{
	image* img;
	RECT rc;

	float x, y;		//�Ѿ� ����
	float gravity;
	float speed;

	bool isFire;
};

class player;

class enemy :public gameNode
{
private:
	tagPirate	_pirate;
	tagSkeleton _skeleton;
	tagTankBomb _tankBomb1[BOMBMAX];
	tagTankBomb _tankBomb2[BOMBMAX];
	
	//���漱��
	player* _EPplayer;

	bool isDebug;


public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void enemyImageBundle();

	void setEnemyPirate();
	void setEnemySkeleton();
	void setEnemyTankBomb1();
	void setEnemyTankBomb2();

	//frame
	void frameUpdatePirate();
	void frameUpdateSkeleton();

	void movePirate();
	void moveSkeleton();

	void fireTankBomb1();
	void moveTankBomb1();
	void fireTankBomb2();
	void moveTankBomb2();

	void changeStatePirate(PIRATESTATE state);
	void changeStateSkeleton(SKELETONSTATE state);

	//��ȣ �浹
	void enemyPlayerCollision();


	//���� ����
	void setPlayerMemoryAddressLink(player* EPplayer) { _EPplayer = EPplayer; }
};

