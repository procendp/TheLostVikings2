#pragma once
#include "gameNode.h"
#include <vector>

#define JUMPPOWER 7.0f
#define GRAVITY 0.3f
//#define GRAVITYMAX 1.0f
#define MAPMAXX 3168
#define MAPMAXY 2298

enum class ERIKSTATE		//enum���θ� �ϸ� ������..�ؿ� �ٸ� �͵�� ��ġ�� �̸� ���Ƽ� -> ������: ���� ���Ǵ� '������'�Դϴ�.	.. �̷��� enum classȭ �ϸ� ������.
{
	IDLE_RIGHT,
	IDLE_LEFT,
	RUN_RIGHT,
	RUN_LEFT,
	DASH_RIGHT,
	DASH_LEFT,
	JUMP_RIGHT,
	JUMP_LEFT,
	JUMP_DOUBLE_RIGHT,
	JUMP_DOUBLE_LEFT,
	PUSH_RIGHT,
	PUSH_LEFT,
	LADDER,
	ROPE_RIGHT,
	ROPE_LEFT,
	SWIM_IDLE_RIGHT,
	SWIM_IDLE_LEFT,
	SWIM_DASH_RIGHT,
	SWIM_DASH_LEFT,
	DAMAGE_DEFAULT_RIGHT,
	DAMAGE_DEFAULT_LEFT,
	DAMAGE_FALLING_RIGHT,
	DAMAGE_FALLING_LEFT,
	DAMAGE_FIRE_RIGHT,
	DAMAGE_FIRE_LEFT,
	DEATH_RIGHT,
	DEATH_LEFT

};
enum class OLAFSTATE
{
	IDLE_RIGHT,
	IDLE_LEFT,
	IDLE_TOP_RIGHT,
	IDLE_TOP_LEFT,
	RUN_RIGHT,
	RUN_LEFT,
	RUN_TOP_RIGHT,
	RUN_TOP_LEFT,
	LADDER,
	PUSH_RIGHT,
	PUSH_LEFT,
	DOWN_IDLE_RIGHT,
	DOWN_IDLE_LEFT,
	DOWN_FAST_RIGHT,
	DOWN_FAST_LEFT,
	DOWN_NOSHIELD_RIGHT,
	DOWN_NOSHIELD_LEFT,
	SMALL_IDLE_RIGHT,
	SMALL_IDLE_LEFT,
	SMALL_RUN_RIGHT,
	SMALL_RUN_LEFT,
	DAMAGE_DEFAULT_RIGHT,
	DAMAGE_DEFAULT_LEFT,
	DAMAGE_FALLING_RIGHT,
	DAMAGE_FALLING_LEFT,
	DAMAGE_FIRE_RIGHT,
	DAMAGE_FIRE_LEFT,
	DEATH_RIGHT,
	DEATH_LEFT

};
enum class BALEOGSTATE
{
	IDLE_RIGHT,
	IDLE_LEFT,
	RUN_RIGHT,
	RUN_LEFT,
	ATTACK_SWORD_RIGHT,
	ATTACK_SWORD_LEFT,
	LADDER,
	PUSH_RIGHT,
	PUSH_LEFT,
	ROPE_IDLE_RIGHT,
	ROPE_IDLE_LEFT,
	ROPE_MOVE_RIGHT,
	ROPE_MOVE_LEFT,
	PUNCH_RIGHT,
	PUNCH_LEFT,
	PUNCH_TOP_RIGHT,
	PUNCH_TOP_LEFT,
	PUNCH_DIAGONAL_RIGHT,
	PUNCH_DIAGONAL_LEFT,
	SWING_RIGHT,
	SWING_LEFT,
	FALLING_RIGHT,
	FALLING_LEFT,
	DAMAGE_DEFAULT_RIGHT,
	DAMAGE_DEFAULT_LEFT,
	DAMAGE_FALLING_RIGHT,
	DAMAGE_FALLING_LEFT,
	DAMAGE_FIRE_RIGHT,
	DAMAGE_FIRE_LEFT,
	DEATH_RIGHT,
	DEATH_LEFT
};

struct tagErik
{
	image* img;
	RECT rc;

	int jumpCount;
	float jumpPower;
	float gravity;
	float x, y;
	float speed;

	float probeB;	//rect �ظ� 
	float probeT;	//rect ���� 
	float probeL;	//rect ���ʸ� 
	float probeR;	//rect �����ʸ� 

	float mapMaxTop;
	float mapMaxBottom;
	float mapMaxLeft;
	float mapMaxRight;

	bool isJump;			//������?
	bool isJumpDouble;		//����������?

	int frameCount;
	int frameIndex;

	ERIKSTATE state;
};
struct tagOlaf
{
	image* img;
	RECT rc;
	
	float gravity;
	
	float x, y;
	float speed;

	float probeB;	//rect �ظ� 
	float probeT;	//rect ���� 
	float probeL;	//rect ���ʸ� 
	float probeR;	//rect �����ʸ� 

	float mapMaxTop;
	float mapMaxBottom;
	float mapMaxLeft;
	float mapMaxRight;

	bool isDownJump;	//�ٿ� ������?

	float jumpPower;
	bool isJump;		//������?

	int frameCount;
	int frameIndex;

	OLAFSTATE state;
};
struct tagBaleog
{
	image* img;
	RECT rc;

	float x, y;
	float speed;
	float gravity;
	
	float probeB;	//rect �ظ� 
	float probeT;	//rect ���� 
	float probeL;	//rect ���ʸ� 
	float probeR;	//rect �����ʸ� 

	float mapMaxTop;
	float mapMaxBottom;
	float mapMaxLeft;
	float mapMaxRight;

	bool isattach;		//����Ʈ �� �پ���?

	float jumpPower;
	bool isJump;

	int frameCount;
	int frameIndex;

	BALEOGSTATE state;
};

//���漱��
class enemy;
class object;
class item;

class obstacleManager;

class player : public gameNode
{
//private:
//	typedef vector<player>				vPlayer;
//	typedef vector<player>::iterator	viPlayer;
//
private:
	
	tagErik _erik;
	tagOlaf _olaf;
	tagBaleog _baleog;

	int count;		//ĳ���� ī�޶� ī��Ʈ

	

	RECT boundary;

	//���漱��
	enemy*	_PEenemy;
	item *  _PIitem;

	obstacleManager* _om;

	bool isDebug;

public:
	player();
	~player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void playerImageBundle();	//player �̹��� �� �ֱ�

	void switchCameraPlayer();		//player �ٲٱ�(ī�޶�)

	void setPlayerErik();		//Erik �⺻set
	void setPlayerOlaf();		//Olaf �⺻set
	void setPlayerBaleog();		//Baleog �⺻set

	void moveErik();			//Erik ������
	void moveOlaf();			//Olaf ������
	void moveBaleog();			//Baleog ������

	//�ȼ� �浹
	void  erikPixelCollision();
	void  olafPixelCollision();
	void  baleogPixelCollision();

	//��ȣ �浹
	void playerEnemyCollision();
	void playerObstacleCollision();
	void playerItemCollision();

	//frame
	void frameUpdateErik();
	void frameUpdateOlaf();
	void frameUpdateBaleog();

	//enumSet
	void changeStateErik(ERIKSTATE state);
	void changeStateOlaf(OLAFSTATE state);
	void changeStateBaleog(BALEOGSTATE state);

	void pulleyPlayerCollision();




	//get		//�޾ƿ�
	float getErikX() { return _erik.x;}		//private -> public �ؼ� public�� ������ x, y��ǥ ����
	float getErikY() { return _erik.y;}		//�̰� ������ ���� ���� platGroundó�� �ٸ� �Լ����� �� �� �ְ� ��.
	float getErikJumpPower() { return _erik.jumpPower; }
	float getEriGravity() { return _erik.gravity; }
	bool getErikIsJump() { return _erik.isJump; }

	float getOlafX() { return _olaf.x;}
	float getOlafY() { return _olaf.y;}

	float getBaleogX() { return _baleog.x;}
	float getBaleogY() { return _baleog.y;}

	int getCount() { return count; }		//ĳ���� ��ȭ count

	RECT getErikRC() { return _erik.rc; }
	RECT getOlafRC() { return _olaf.rc; }
	RECT getBaleogRC() { return _baleog.rc; }

	//set		//������
	void setErikY(float erikY) { _erik.y = erikY; }
	void setErikRC(RECT erikRC) { _erik.rc = erikRC; }
	void setErikJumpPower(float erikJumpPower) { _erik.jumpPower = erikJumpPower; }
	void setErikGravity(float erikGravity) { _erik.gravity = erikGravity; }
	void setErikIsJump(bool erikIsJump) { _erik.isJump = erikIsJump; }



	//���� ����
	void setEnemyMemoryAddressLink(enemy* PEenemy) { _PEenemy = PEenemy; }
	void setItemMemoryAddressLink(item* PIitem) { _PIitem = PIitem; }

	void setOmMemoryAddressLink(obstacleManager* om) { _om = om; }
};

