#pragma once
#include "gameNode.h"
#include <vector>

#define JUMPPOWER 7.0f
#define GRAVITY 0.3f
//#define GRAVITYMAX 1.0f
#define MAPMAXX 3168
#define MAPMAXY 2298

enum class ERIKSTATE		//enum으로만 하면 오류남..밑에 다른 것들과 겹치는 이름 많아서 -> 재정의: 이전 정의는 '열거자'입니다.	.. 이렇게 enum class화 하면 괜찮음.
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

	float probeB;	//rect 밑면 
	float probeT;	//rect 윗면 
	float probeL;	//rect 왼쪽면 
	float probeR;	//rect 오른쪽면 

	float mapMaxTop;
	float mapMaxBottom;
	float mapMaxLeft;
	float mapMaxRight;

	bool isJump;			//점프함?
	bool isJumpDouble;		//더블점프함?

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

	float probeB;	//rect 밑면 
	float probeT;	//rect 윗면 
	float probeL;	//rect 왼쪽면 
	float probeR;	//rect 오른쪽면 

	float mapMaxTop;
	float mapMaxBottom;
	float mapMaxLeft;
	float mapMaxRight;

	bool isDownJump;	//다운 점프함?

	float jumpPower;
	bool isJump;		//점프함?

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
	
	float probeB;	//rect 밑면 
	float probeT;	//rect 윗면 
	float probeL;	//rect 왼쪽면 
	float probeR;	//rect 오른쪽면 

	float mapMaxTop;
	float mapMaxBottom;
	float mapMaxLeft;
	float mapMaxRight;

	bool isattach;		//가제트 팔 붙었어?

	float jumpPower;
	bool isJump;

	int frameCount;
	int frameIndex;

	BALEOGSTATE state;
};

//전방선언
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

	int count;		//캐릭터 카메라 카운트

	

	RECT boundary;

	//전방선언
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

	void playerImageBundle();	//player 이미지 다 넣기

	void switchCameraPlayer();		//player 바꾸기(카메라)

	void setPlayerErik();		//Erik 기본set
	void setPlayerOlaf();		//Olaf 기본set
	void setPlayerBaleog();		//Baleog 기본set

	void moveErik();			//Erik 움직임
	void moveOlaf();			//Olaf 움직임
	void moveBaleog();			//Baleog 움직임

	//픽셀 충돌
	void  erikPixelCollision();
	void  olafPixelCollision();
	void  baleogPixelCollision();

	//상호 충돌
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




	//get		//받아와
	float getErikX() { return _erik.x;}		//private -> public 해서 public에 에릭의 x, y좌표 선언
	float getErikY() { return _erik.y;}		//이거 있으면 리턴 값을 platGround처럼 다른 함수에서 쓸 수 있게 됨.
	float getErikJumpPower() { return _erik.jumpPower; }
	float getEriGravity() { return _erik.gravity; }
	bool getErikIsJump() { return _erik.isJump; }

	float getOlafX() { return _olaf.x;}
	float getOlafY() { return _olaf.y;}

	float getBaleogX() { return _baleog.x;}
	float getBaleogY() { return _baleog.y;}

	int getCount() { return count; }		//캐릭터 변화 count

	RECT getErikRC() { return _erik.rc; }
	RECT getOlafRC() { return _olaf.rc; }
	RECT getBaleogRC() { return _baleog.rc; }

	//set		//갱신해
	void setErikY(float erikY) { _erik.y = erikY; }
	void setErikRC(RECT erikRC) { _erik.rc = erikRC; }
	void setErikJumpPower(float erikJumpPower) { _erik.jumpPower = erikJumpPower; }
	void setErikGravity(float erikGravity) { _erik.gravity = erikGravity; }
	void setErikIsJump(bool erikIsJump) { _erik.isJump = erikIsJump; }



	//전방 선언
	void setEnemyMemoryAddressLink(enemy* PEenemy) { _PEenemy = PEenemy; }
	void setItemMemoryAddressLink(item* PIitem) { _PIitem = PIitem; }

	void setOmMemoryAddressLink(obstacleManager* om) { _om = om; }
};

