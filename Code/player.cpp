#include "stdafx.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "object.h"

#include "obstacleManager.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{
	playerImageBundle();	//플레이어 이미지 다 가져오기

	setPlayerErik();		//에릭 기초 세팅
	setPlayerOlaf();		//올라프 기초 세팅
	setPlayerBaleog();		//벨로그 기초 세팅

	count = 1;		//erik


	//프레임 카운터랑 인덱스 다 따로 주자!!!!!
	_erik.frameCount = 0;
	_erik.frameIndex = 0;

	_olaf.frameCount = 0;
	_olaf.frameIndex = 0;

	_baleog.frameCount = 0;
	_baleog.frameIndex = 0;

	isDebug = false;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	switchCameraPlayer();

	//캐릭터 상태변화frame
	frameUpdateErik();
	frameUpdateOlaf();
	frameUpdateBaleog();

	erikPixelCollision();
	olafPixelCollision();
	baleogPixelCollision();
	
	//캐릭터 상태변화key	..무조건 픽셀보다 아래에 두자
	moveErik();
	moveOlaf();
	moveBaleog();

	//playerEnemyCollision();
	
	//갱신
	_erik.rc = RectMake(_erik.x, _erik.y, 90, 90);
	_olaf.rc = RectMake(_olaf.x, _olaf.y, 90, 90);
	_baleog.rc = RectMake(_baleog.x, _baleog.y, 90, 90);
}

void player::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		isDebug = true;
		Rectangle(getMemDC(), _erik.rc);									//HDC, rc			//erik에 씌울 렉트
		Rectangle(getMemDC(), _olaf.rc);									//HDC, rc			//olaf에 씌울 렉트
		Rectangle(getMemDC(), _baleog.rc);									//HDC, rc			//baleog에 씌울 렉트

	}
	_erik.img->frameRender(getMemDC(), _erik.x, _erik.y);				//HDC, left, top	//erik 이미지
	_olaf.img->frameRender(getMemDC(), _olaf.x, _olaf.y);				//HDC, left, top	//olaf 이미지
	_baleog.img->frameRender(getMemDC(), _baleog.x, _baleog.y);			//HDC, left, top	//baleog 이미지
	

	
/*
<캐릭터 좌표 확인용>
char up[128];
char up_p[128];
char down[128];
char down_p[128];
char left[128];
char left_p[128];
char right[128];
char right_p[128];


sprintf_s(up,"위쪽닿았어? %f" , _erik.mapMaxTop);
sprintf_s(up_p, "캐릭터 위쪽부분 %f", _erik.probeTM);
sprintf_s(down, "아래쪽 닿앗어? %f", _erik.mapMaxBottom);
sprintf_s(down_p, "캐릭터 아래쪽 %f", _erik.probeBM);
sprintf_s(left,"왼쪽 닿앗어? %f" , _erik.mapMaxLeft);
sprintf_s(left_p, "캐릭터 왼쪽 %f", _erik.probeLM);
sprintf_s(right, "오른쪽 닿앗어? %f", _erik.mapMaxRight);
sprintf_s(right_p, "캐릭터 오른쪽 %f", _erik.probeRM);


TextOut(getMemDC(), _erik.x - 240, _erik.y - 240, up, strlen(up));
TextOut(getMemDC(), _erik.x - 240, _erik.y - 220, up_p, strlen(up_p));
TextOut(getMemDC(), _erik.x - 240, _erik.y - 200, down, strlen(down));
TextOut(getMemDC(), _erik.x - 240, _erik.y - 180, down_p, strlen(down_p));
TextOut(getMemDC(), _erik.x - 240, _erik.y - 160, left, strlen(left));
TextOut(getMemDC(), _erik.x - 240, _erik.y - 140, left_p, strlen(left_p));
TextOut(getMemDC(), _erik.x - 240, _erik.y - 120, right, strlen(right));
TextOut(getMemDC(), _erik.x - 240, _erik.y - 100, right_p, strlen(right_p));
*/
}

//굿
void player::playerImageBundle()
{
	//erik
	IMAGEMANAGER->addFrameImage("ErikIdle", "IMAGE/ErikIdle.bmp", 435, 180, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikRun", "IMAGE/ErikRun.bmp", 720, 180, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikDash", "IMAGE/ErikDash.bmp", 1344, 180, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikJump", "IMAGE/ErikJump.bmp", 360, 180, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikJumpDouble", "IMAGE/ErikJumpDouble.bmp", 810, 180, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikLadder", "IMAGE/ErikLadder.bmp", 462, 90, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikPush", "IMAGE/ErikPush.bmp", 360, 180, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikRope", "IMAGE/ErikRope.bmp", 720, 180, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikSwimIdle", "IMAGE/ErikSwimIdle.bmp", 372, 180, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikSwimDash", "IMAGE/ErikSwimDash.bmp", 930, 180, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikDamageDefault", "IMAGE/ErikDamageDefault.bmp", 180, 90, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikDamageFalling", "IMAGE/ErikDamageFalling.bmp", 960, 180, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikDamageFire", "IMAGE/ErikDamageFire.bmp", 180, 180, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ErikDeath", "IMAGE/ErikDeath.bmp", 360, 180, 4, 2, true, RGB(255, 0, 255));

	//olaf
	IMAGEMANAGER->addFrameImage("OlafIdle", "IMAGE/OlafIdle.bmp", 88, 180, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafIdleTop", "IMAGE/OlafIdleTop.bmp", 78, 180, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafRun", "IMAGE/OlafRun.bmp", 713, 180, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafRunTop", "IMAGE/OlafRunTop.bmp", 727, 180, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafDownFast", "IMAGE/OlafDownFast.bmp", 182, 180, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafDownIdle", "IMAGE/OlafDownIdle.bmp", 182, 180, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafDownNoShield", "IMAGE/OlafDownNoShield.bmp", 455, 180, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafLadder", "IMAGE/OlafLadder.bmp", 477, 90, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafPush", "IMAGE/OlafPush.bmp", 352, 180, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafDamageDefault", "IMAGE/OlafDamageDefault.bmp", 87, 180, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafDamageFalling", "IMAGE/OlafDamageFalling.bmp", 706, 180, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafDamageFire", "IMAGE/OlafDamageFire.bmp", 176, 180, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafSmallIdle", "IMAGE/OlafSmallIdle.bmp", 297, 180, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafSmallRun", "IMAGE/OlafSmallRun.bmp", 268, 116, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("OlafDeath", "IMAGE/OlafDeath.bmp", 352, 180, 4, 2, true, RGB(255, 0, 255));

	//baleog
	IMAGEMANAGER->addFrameImage("BaleogIdle", "IMAGE/BaleogIdle.bmp", 450, 180, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogRun", "IMAGE/BaleogRun.bmp", 720, 180, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogAttackSword", "IMAGE/BaleogAttackSword.bmp", 540, 180, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogFalling", "IMAGE/BaleogFalling.bmp", 180, 180, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogRopeIdle", "IMAGE/BaleogRopeIdle.bmp", 270, 180, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogRopeMove", "IMAGE/BaleogRopeMove.bmp", 540, 180, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogPush", "IMAGE/BaleogPush.bmp", 360, 180, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogLadder", "IMAGE/BaleogLadder.bmp", 540, 90, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogPunch", "IMAGE/BaleogPunch.bmp", 360, 180, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogPunchDiagonal", "IMAGE/BaleogPunchDiagonal.bmp", 270, 180, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogPunchTop", "IMAGE/BaleogPunchTop.bmp", 450, 180, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogSwing", "IMAGE/BaleogSwing.bmp", 720, 180, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogPunchHand", "IMAGE/BaleogPunchHand.bmp", 62, 75, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogPunchRing", "IMAGE/BaleogPunchRing.bmp", 32, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogDamageDefault", "IMAGE/BaleogDamageDefault.bmp", 180, 90, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogDamageFalling", "IMAGE/BaleogDamageFalling.bmp", 720, 180, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogDamageFire", "IMAGE/BaleogDamageFire.bmp", 180, 180, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BaleogDeath", "IMAGE/BaleogDeath.bmp", 360, 180, 4, 2, true, RGB(255, 0, 255));
}		

//굿
void player::switchCameraPlayer()		//카메라 바꾸며 캐릭터 바꾸기
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		count++;
	}
	if (count > 3)
	{
		count = 1;
	}
}

//굿
void player::setPlayerErik()	//에릭 초기 세팅
{
	_erik.img = IMAGEMANAGER->findImage("ErikIdle");
	_erik.state = ERIKSTATE::IDLE_RIGHT;
	//changeStateErik(ERIKSTATE::IDLE_RIGHT);

	_erik.x = 175;
	_erik.y = 900;	//에릭 시작 좌표
	_erik.rc = RectMake(_erik.x, _erik.y, 90, 90);
	//_erik.img->setX(_erik.x / 2);
	//_erik.img->setY(_erik.y / 2);

	_erik.jumpPower = 0;
	_erik.jumpCount = 0;
	_erik.gravity = GRAVITY;
	
	_erik.isJump = false;
	_erik.isJumpDouble = false;

	//카메라 경계
	//boundary = RectMakeCenter(_erik.x, _erik.y, 150, 150);
	//mapMaxTop = MAPMAXX;
	//mapMaxBottom = MAPMAXY;

}
void player::setPlayerOlaf()	//올라프 초기 세팅
{
	_olaf.img = IMAGEMANAGER->findImage("OlafIdle");
	_olaf.state = OLAFSTATE::IDLE_RIGHT;
	//changeStateOlaf(OLAFSTATE::IDLE_RIGHT);

	_olaf.x = 85;
	_olaf.y = 900;	//에릭 시작 좌표
	_olaf.rc = RectMake(_olaf.x, _olaf.y, 90, 90);

	_olaf.jumpPower = 0;
	_olaf.gravity = GRAVITY;

	_olaf.isJump = false;
}
void player::setPlayerBaleog()	//벨로그 초기 세팅
{
	_baleog.img = IMAGEMANAGER->findImage("BaleogIdle");
	_baleog.state = BALEOGSTATE::IDLE_RIGHT;

	_baleog.x = 265;
	_baleog.y = 900;	//에릭 시작 좌표
	_baleog.rc = RectMake(_baleog.x, _baleog.y, 90, 90);

	_baleog.gravity = GRAVITY;

}


void player::moveErik()
{
	//중력
	if (_erik.isJump)
	{
		_erik.y -= _erik.jumpPower;
		_erik.jumpPower -= _erik.gravity;
		_erik.img->setY(_erik.y);

	}
	if (count == 1)	//erik 선택되었을 때
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_erik.x -= 5;
			changeStateErik(ERIKSTATE::RUN_LEFT);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_erik.x += 5;
			changeStateErik(ERIKSTATE::RUN_RIGHT);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_erik.isJump = true;
			_erik.jumpPower = JUMPPOWER;
			_erik.gravity = GRAVITY;
			_erik.y -= 0.5f;		//눈속임
		}
		

		
			//_erik.jumpCount++;

		//if (_erik.jumpCount <= 2)		_erik.isJump = true;
		//else if (_erik.jumpCount > 2)	_erik.isJump = false;

		//if (_erik.jumpCount == 2)
		//{
		//	_erik.isJump = false;
		//	_erik.jumpCount = 1;
		//}
		

		/*if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			changeStateErik(ERIKSTATE::JUMP_RIGHT);
			_erik.x += 3;
			if (_erik.jumpCount == 2)
			{
				changeStateErik(ERIKSTATE::JUMP_DOUBLE_RIGHT);
				_erik.isJump = false;
				_erik.jumpCount = 1;
			}
			
			_erik.jumpCount = 1;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			changeStateErik(ERIKSTATE::JUMP_LEFT);
			if (_erik.jumpCount == 2)
			{
				changeStateErik(ERIKSTATE::JUMP_DOUBLE_LEFT);
				_erik.isJump = false;
				_erik.jumpCount = 1;
			}

			_erik.jumpCount = 1;
		}*/


		//맵 나가면
		if (_erik.x < 0)				_erik.x += 5;
		if (_erik.x > MAPMAXX - 90)		_erik.x -= 5;
		if (_erik.y < 0)				_erik.y += 5;
		if (_erik.y > MAPMAXY - 90)		_erik.y -= 5;
	}
	
}
void player::moveOlaf()
{
	//중력 주고 시작
	_olaf.y -= _olaf.jumpPower;
	_olaf.jumpPower -= _olaf.gravity;
	_olaf.img->setY(_olaf.y);

	if (count == 2)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_olaf.x -= 5;
			changeStateOlaf(OLAFSTATE::RUN_LEFT);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_olaf.x += 5;
			changeStateOlaf(OLAFSTATE::RUN_RIGHT);
			
			if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				changeStateOlaf(OLAFSTATE::IDLE_RIGHT);
			}
		}

		//맵 나가면
		if (_olaf.x < 0)				_olaf.x += 5;
		if (_olaf.x > MAPMAXX - 90)		_olaf.x -= 5;
		if (_olaf.y < 0)				_olaf.y += 5;
		if (_olaf.y > MAPMAXY - 90)		_olaf.y -= 5;
	}
}
void player::moveBaleog()
{
	//중력 주고 시작
	_baleog.y -= _baleog.jumpPower;
	_baleog.jumpPower -= _baleog.gravity;
	_baleog.img->setY(_baleog.y);

	if (count == 3)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_baleog.x -= 5;
			changeStateBaleog(BALEOGSTATE::RUN_LEFT);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_baleog.x += 5;
			changeStateBaleog(BALEOGSTATE::RUN_RIGHT);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			
		}

		//맵 나가면
		if (_baleog.x < 0)				_baleog.x += 5;
		if (_baleog.x > MAPMAXX - 90)	_baleog.x -= 5;
		if (_baleog.y < 0)				_baleog.y += 5;
		if (_baleog.y > MAPMAXY - 90)	_baleog.y -= 5;
	}
}

//굿	
void player::frameUpdateErik()
{
	_erik.frameCount++;

	if (_erik.frameCount % 10 == 0)
	{
		if (_erik.state == ERIKSTATE::IDLE_RIGHT)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 4) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::IDLE_LEFT)
		{
			_erik.img->setFrameY(1);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 4) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::RUN_RIGHT)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 7) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::RUN_LEFT)
		{
			_erik.img->setFrameY(1);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 7) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::DASH_RIGHT)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 13) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::DASH_LEFT)
		{
			_erik.img->setFrameY(1);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 13) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::JUMP_RIGHT)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 3) _erik.frameIndex = 0;
		}

		if (_erik.state == ERIKSTATE::JUMP_LEFT)
		{
			_erik.img->setFrameY(1);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 3) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::JUMP_DOUBLE_RIGHT)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 8) _erik.frameIndex = 0;
		}

		if (_erik.state == ERIKSTATE::JUMP_DOUBLE_LEFT)
		{
			_erik.img->setFrameY(1);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 8) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::PUSH_RIGHT)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 3) _erik.frameIndex = 0;
		}

		if (_erik.state == ERIKSTATE::PUSH_LEFT)
		{
			_erik.img->setFrameY(1);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 3) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::LADDER)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 5) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::ROPE_RIGHT)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 7) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::ROPE_LEFT)
		{
			_erik.img->setFrameY(1);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 7) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::SWIM_IDLE_RIGHT)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 3) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::SWIM_IDLE_LEFT)
		{
			_erik.img->setFrameY(1);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 3) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::SWIM_DASH_RIGHT)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 9) _erik.frameIndex = 0;
		}

		if (_erik.state == ERIKSTATE::SWIM_DASH_LEFT)
		{
			_erik.img->setFrameY(1);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 9) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::DAMAGE_DEFAULT_RIGHT)	
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 0) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::DAMAGE_DEFAULT_LEFT)	
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 1) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::DAMAGE_FALLING_RIGHT)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 9) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::DAMAGE_FALLING_LEFT)
		{
			_erik.img->setFrameY(1);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 9) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::DAMAGE_FIRE_RIGHT)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 1) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::DAMAGE_FIRE_LEFT)
		{
			_erik.img->setFrameY(1);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 1) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::DEATH_RIGHT)
		{
			_erik.img->setFrameY(0);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 3) _erik.frameIndex = 0;
		}
		if (_erik.state == ERIKSTATE::DEATH_LEFT)
		{
			_erik.img->setFrameY(1);
			_erik.img->setFrameX(_erik.frameIndex);
			_erik.frameIndex++;

			if (_erik.frameIndex >= 3) _erik.frameIndex = 0;
		}

		_erik.frameCount = 0;
	}
}
void player::frameUpdateOlaf()
{
	_olaf.frameCount++;
	if (_olaf.frameCount % 10 == 0)
	{
		if (_olaf.state == OLAFSTATE::IDLE_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 0) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::IDLE_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 0) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::IDLE_TOP_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 0) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::IDLE_TOP_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 0) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::RUN_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 7) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::RUN_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 7) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::RUN_TOP_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 7) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::RUN_TOP_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 7) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::LADDER)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 5) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::PUSH_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 3) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::PUSH_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 3) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::DOWN_IDLE_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 1) _olaf.frameIndex = 0;
		}

		if (_olaf.state == OLAFSTATE::DOWN_IDLE_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 1) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::DOWN_FAST_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 1) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::DOWN_FAST_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 1) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::DOWN_NOSHIELD_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 4) _olaf.frameIndex = 0;
		}

		if (_olaf.state == OLAFSTATE::DOWN_NOSHIELD_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 4) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::SMALL_IDLE_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 3) _olaf.frameIndex = 0;
		}

		if (_olaf.state == OLAFSTATE::SMALL_IDLE_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 3) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::SMALL_RUN_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 3) _olaf.frameIndex = 0;
		}

		if (_olaf.state == OLAFSTATE::SMALL_RUN_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 3) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::DAMAGE_DEFAULT_RIGHT)		
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 0) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::DAMAGE_DEFAULT_LEFT)		
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 0) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::DAMAGE_FALLING_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 7) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::DAMAGE_FALLING_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 7) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::DAMAGE_FIRE_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 1) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::DAMAGE_FIRE_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 1) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::DEATH_RIGHT)
		{
			_olaf.img->setFrameY(0);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 3) _olaf.frameIndex = 0;
		}
		if (_olaf.state == OLAFSTATE::DEATH_LEFT)
		{
			_olaf.img->setFrameY(1);
			_olaf.img->setFrameX(_olaf.frameIndex);
			_olaf.frameIndex++;

			if (_olaf.frameIndex >= 3) _olaf.frameIndex = 0;
		}

		_olaf.frameCount = 0;
	}
}
void player::frameUpdateBaleog()
{
	_baleog.frameCount++;
	if (_baleog.frameCount % 10 == 0)
	{
		if (_baleog.state == BALEOGSTATE::IDLE_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 4) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::IDLE_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 4) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::RUN_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 7) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::RUN_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 7) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::ATTACK_SWORD_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 5) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::ATTACK_SWORD_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 5) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::LADDER)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 5) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::PUSH_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 3) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::PUSH_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 3) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::ROPE_IDLE_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 2) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::ROPE_IDLE_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 2) _baleog.frameIndex = 0;
		}
		
		
		if (_baleog.state == BALEOGSTATE::ROPE_MOVE_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 5) _baleog.frameIndex = 0;
		}

		if (_baleog.state == BALEOGSTATE::ROPE_MOVE_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 5) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::PUNCH_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 3) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::PUNCH_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 3) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::PUNCH_TOP_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 1) _baleog.frameIndex = 0;
		}

		if (_baleog.state == BALEOGSTATE::PUNCH_TOP_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 1) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::PUNCH_DIAGONAL_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 2) _baleog.frameIndex = 0;
		}

		if (_baleog.state == BALEOGSTATE::PUNCH_DIAGONAL_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 2) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::SWING_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 7) _baleog.frameIndex = 0;
		}

		if (_baleog.state == BALEOGSTATE::SWING_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 7) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::FALLING_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 1) _baleog.frameIndex = 0;
		}

		if (_baleog.state == BALEOGSTATE::FALLING_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 1) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::DAMAGE_DEFAULT_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 0) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::DAMAGE_DEFAULT_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 0) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::DAMAGE_FALLING_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 7) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::DAMAGE_FALLING_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 7) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::DAMAGE_FIRE_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 1) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::DAMAGE_FIRE_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 1) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::DEATH_RIGHT)
		{
			_baleog.img->setFrameY(0);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 3) _baleog.frameIndex = 0;
		}
		if (_baleog.state == BALEOGSTATE::DEATH_LEFT)
		{
			_baleog.img->setFrameY(1);
			_baleog.img->setFrameX(_baleog.frameIndex);
			_baleog.frameIndex++;

			if (_baleog.frameIndex >= 3) _baleog.frameIndex = 0;
		}

		_baleog.frameCount = 0;
	}
}

void player::erikPixelCollision()
{
	_erik.probeB = _erik.rc.bottom;
	_erik.probeT = _erik.rc.top;
	_erik.probeL = (_erik.rc.left + _erik.rc.right) / 2 - 45;
	_erik.probeR = (_erik.rc.left + _erik.rc.right) / 2 + 45;

	_erik.mapMaxBottom = MAPMAXY;
	_erik.mapMaxTop = 0;
	_erik.mapMaxLeft = 0;
	_erik.mapMaxRight = MAPMAXX;

	//탐사쓰
	//아랫면
	for (int i = _erik.probeB - 20; i < _erik.probeB + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), (_erik.rc.left + _erik.rc.right) / 2 - 30, i);		//x축 - 30, y축(i)

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 254 && b == 0)	//노(바닥)
		{
			if (_erik.mapMaxBottom > i)
			{
				_erik.mapMaxBottom = i;
			}
		}
		color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), (_erik.rc.left + _erik.rc.right) / 2 + 30, i);		//x축 + 30, y축(i)

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 254 && b == 0)	//노(바닥)
		{
			if (_erik.mapMaxBottom > i)
			{
				_erik.mapMaxBottom = i;
			}
		}
	}
	//아랫면충돌쓰
	if (_erik.mapMaxBottom <= _erik.probeB)
	{
		_erik.y = _erik.mapMaxBottom - 90/*_erik.rc.bottom *//* - _erik.rc.top*/;
		_erik.isJump = false;
		_erik.gravity = 0;
		_erik.jumpPower = 0;
	}
	//바닥 벗어나면 중력값 주기
	if (_erik.mapMaxBottom > _erik.probeB && _erik.isJump == false)
	{
		_erik.gravity = GRAVITY;
		_erik.isJump = true;
	}
	//윗면
	for (int i = _erik.probeT - 20; i < _erik.probeT + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), (_erik.rc.left + _erik.rc.right) / 2 - 30, i);		//x축 - 30, y축(i)

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 1 && g == 1 && b == 255)	//파(윗면)
		{
			if (_erik.mapMaxTop < i)
			{
				_erik.mapMaxTop = i;
			}
		}
		color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), (_erik.rc.left + _erik.rc.right) / 2 + 30, i);		//x축 + 30, y축(i)

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 1 && g == 1 && b == 255)	//파(윗면)
		{
			if (_erik.mapMaxTop < i)
			{
				_erik.mapMaxTop = i;
			}
		}
	}
	//윗면 충돌쓰
	if (_erik.mapMaxTop >= _erik.probeT)
	{
		_erik.y = _erik.mapMaxTop;
	}
	//왼쪽면
	for (int i = _erik.probeL - 20; i < _erik.probeL + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, (_erik.rc.bottom + _erik.rc.top) / 2 - 30);		//x축(i), y축 - 30

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 1 && b == 1)	//빨(좌우)
		{
			if (_erik.mapMaxLeft < i)
			{
				_erik.mapMaxLeft = i;
			}
		}

		color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, (_erik.rc.bottom + _erik.rc.top) / 2 + 30);		//x축(i), y축 + 30

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 1 && b == 1)	//빨(좌우)
		{
			if (_erik.mapMaxLeft < i)
			{
				_erik.mapMaxLeft = i;
			}
		}

	}
	//왼쪽면 충돌쓰
	if (_erik.mapMaxLeft >= _erik.probeL)
	{
		_erik.x = _erik.mapMaxLeft ;
	}
	//오른쪽면
	for (int i = _erik.probeR - 20; i < _erik.probeR + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, (_erik.rc.bottom + _erik.rc.top) / 2 - 30 );		//x축(i), y축 - 30

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 1 && b == 1)	//빨(좌우)
		{
			if (_erik.mapMaxRight > i)
			{
				_erik.mapMaxRight = i;
			}
		}
		color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, (_erik.rc.bottom + _erik.rc.top) / 2 + 30);		//x축(i), y축 + 30

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 1 && b == 1)	//빨(좌우)
		{
			if (_erik.mapMaxRight > i)
			{
				_erik.mapMaxRight = i;
			}
		}
	}
	//오른쪽면 충돌쓰
	if (_erik.mapMaxRight <= _erik.probeR)
	{
		_erik.x = _erik.mapMaxRight - 90;		//left, top 기준이니까!!! 90이하(몸통크기)의 값을 빼주면 오른쪽으로 훅훅 넘어갈거야. 꼭 90 넘게 주자
	}
}
void player::olafPixelCollision()
{
	_olaf.probeB = _olaf.rc.bottom;
	_olaf.probeT = _olaf.rc.top;
	_olaf.probeL = (_olaf.rc.left + _olaf.rc.right) / 2 - 45;
	_olaf.probeR = (_olaf.rc.left + _olaf.rc.right) / 2 + 45;

	_olaf.mapMaxBottom = MAPMAXY;
	_olaf.mapMaxTop = 0;
	_olaf.mapMaxLeft = 0;
	_olaf.mapMaxRight = MAPMAXX;

	//탐사쓰
	//아랫면
	for (int i = _olaf.probeB - 20; i < _olaf.probeB + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), (_olaf.rc.left + _olaf.rc.right) / 2 - 30, i);		//x축 - 30, y축(i)

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 254 && b == 0)	//노(바닥)
		{
			if (_olaf.mapMaxBottom > i)
			{
				_olaf.mapMaxBottom = i;
			}
		}
		color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), (_olaf.rc.left + _olaf.rc.right) / 2 + 30, i);		//x축 + 30, y축(i)

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 254 && b == 0)	//노(바닥)
		{
			if (_olaf.mapMaxBottom > i)
			{
				_olaf.mapMaxBottom = i;
			}
		}
	}
	//아랫면충돌쓰
	if (_olaf.mapMaxBottom <= _olaf.probeB)
	{
		_olaf.y = _olaf.mapMaxBottom - (_olaf.rc.bottom - _olaf.rc.top);
		_olaf.isJump = false;
		_olaf.gravity = 0;
		_olaf.jumpPower = 0;
	}
	//바닥 벗어나면 중력값 주기
	if (_olaf.mapMaxBottom > _olaf.probeB && _olaf.isJump == false)
	{
		_olaf.gravity = GRAVITY;
		_olaf.isJump = true;
	}
	//윗면
	for (int i = _olaf.probeT - 20; i < _olaf.probeT + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), (_olaf.rc.left + _olaf.rc.right) / 2 - 30, i);		//x축 - 30, y축(i)

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 1 && g == 1 && b == 255)	//파(윗면)
		{
			if (_olaf.mapMaxTop < i)
			{
				_olaf.mapMaxTop = i;
			}
		}
		color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), (_olaf.rc.left + _olaf.rc.right) / 2 + 30, i);		//x축 + 30, y축(i)

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 1 && g == 1 && b == 255)	//파(윗면)
		{
			if (_olaf.mapMaxTop < i)
			{
				_olaf.mapMaxTop = i;
			}
		}
	}
	//윗면 충돌쓰
	if (_olaf.mapMaxTop >= _olaf.probeT)
	{
		_olaf.y = _olaf.mapMaxTop;
	}
	//왼쪽면
	for (int i = _olaf.probeL - 20; i < _olaf.probeL + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, (_olaf.rc.bottom + _olaf.rc.top) / 2 - 30);		//x축(i), y축 - 30

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 1 && b == 1)	//빨(좌우)
		{
			if (_olaf.mapMaxLeft < i)
			{
				_olaf.mapMaxLeft = i;
			}
		}

		color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, (_olaf.rc.bottom + _olaf.rc.top) / 2 + 30);		//x축(i), y축 + 30

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 1 && b == 1)	//빨(좌우)
		{
			if (_olaf.mapMaxLeft < i)
			{
				_olaf.mapMaxLeft = i;
			}
		}

	}
	//왼쪽면 충돌쓰
	if (_olaf.mapMaxLeft >= _olaf.probeL)
	{
		_olaf.x = _olaf.mapMaxLeft;
	}
	//오른쪽면
	for (int i = _olaf.probeR - 20; i < _olaf.probeR + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, (_olaf.rc.bottom + _olaf.rc.top) / 2 - 30);		//x축(i), y축 - 30

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 1 && b == 1)	//빨(좌우)
		{
			if (_olaf.mapMaxRight > i)
			{
				_olaf.mapMaxRight = i;
			}
		}
		color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, (_olaf.rc.bottom + _olaf.rc.top) / 2 + 30);		//x축(i), y축 + 30

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 1 && b == 1)	//빨(좌우)
		{
			if (_olaf.mapMaxRight > i)
			{
				_olaf.mapMaxRight = i;
			}
		}
	}
	//오른쪽면 충돌쓰
	if (_olaf.mapMaxRight <= _olaf.probeR)
	{
		_olaf.x = _olaf.mapMaxRight - 90;		//left, top 기준이니까!!! 90이하(몸통크기)의 값을 빼주면 오른쪽으로 훅훅 넘어갈거야. 꼭 90 넘게 주자
	}
}
void player::baleogPixelCollision()
{
	_baleog.probeB = _baleog.rc.bottom;
	_baleog.probeT = _baleog.rc.top;
	_baleog.probeL = (_baleog.rc.left + _baleog.rc.right) / 2 - 45;
	_baleog.probeR = (_baleog.rc.left + _baleog.rc.right) / 2 + 45;

	_baleog.mapMaxBottom = MAPMAXY;
	_baleog.mapMaxTop = 0;
	_baleog.mapMaxLeft = 0;
	_baleog.mapMaxRight = MAPMAXX;

	//탐사쓰
	//아랫면
	for (int i = _baleog.probeB - 20; i < _baleog.probeB + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), (_baleog.rc.left + _baleog.rc.right) / 2 - 30, i);		//x축 - 30, y축(i)

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 254 && b == 0)	//노(바닥)
		{
			if (_baleog.mapMaxBottom > i)
			{
				_baleog.mapMaxBottom = i;
			}
		}
		color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), (_baleog.rc.left + _baleog.rc.right) / 2 + 30, i);		//x축 + 30, y축(i)

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 254 && b == 0)	//노(바닥)
		{
			if (_baleog.mapMaxBottom > i)
			{
				_baleog.mapMaxBottom = i;
			}
		}
	}
	//아랫면충돌쓰
	if (_baleog.mapMaxBottom <= _baleog.probeB)
	{
		_baleog.y = _baleog.mapMaxBottom - (_baleog.rc.bottom - _baleog.rc.top);
		_baleog.isJump = false;
		_baleog.gravity = 0;
		_baleog.jumpPower = 0;
	}
	//바닥 벗어나면 중력값 주기
	if (_baleog.mapMaxBottom > _baleog.probeB && _baleog.isJump == false)
	{
		_baleog.gravity = GRAVITY;
		_baleog.isJump = true;
	}
	//윗면
	for (int i = _baleog.probeT - 20; i < _baleog.probeT + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), (_baleog.rc.left + _baleog.rc.right) / 2 - 30, i);		//x축 - 30, y축(i)

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 1 && g == 1 && b == 255)	//파(윗면)
		{
			if (_baleog.mapMaxTop < i)
			{
				_baleog.mapMaxTop = i;
			}
		}
		color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), (_baleog.rc.left + _baleog.rc.right) / 2 + 30, i);		//x축 + 30, y축(i)

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 1 && g == 1 && b == 255)	//파(윗면)
		{
			if (_baleog.mapMaxTop < i)
			{
				_baleog.mapMaxTop = i;
			}
		}
	}
	//윗면 충돌쓰
	if (_baleog.mapMaxTop >= _baleog.probeT)
	{
		_baleog.y = _baleog.mapMaxTop;
	}
	//왼쪽면
	for (int i = _baleog.probeL - 20; i < _baleog.probeL + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, (_baleog.rc.bottom + _baleog.rc.top) / 2 - 30);		//x축(i), y축 - 30

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 1 && b == 1)	//빨(좌우)
		{
			if (_baleog.mapMaxLeft < i)
			{
				_baleog.mapMaxLeft = i;
			}
		}

		color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, (_baleog.rc.bottom + _baleog.rc.top) / 2 + 30);		//x축(i), y축 + 30

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 1 && b == 1)	//빨(좌우)
		{
			if (_baleog.mapMaxLeft < i)
			{
				_baleog.mapMaxLeft = i;
			}
		}

	}
	//왼쪽면 충돌쓰
	if (_baleog.mapMaxLeft >= _baleog.probeL)
	{
		_baleog.x = _baleog.mapMaxLeft;
	}
	//오른쪽면
	for (int i = _baleog.probeR - 20; i < _baleog.probeR + 20; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, (_baleog.rc.bottom + _baleog.rc.top) / 2 - 30);		//x축(i), y축 - 30

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 1 && b == 1)	//빨(좌우)
		{
			if (_baleog.mapMaxRight > i)
			{
				_baleog.mapMaxRight = i;
			}
		}
		color = GetPixel(IMAGEMANAGER->findImage("배경픽셀")->getMemDC(), i, (_baleog.rc.bottom + _baleog.rc.top) / 2 + 30);		//x축(i), y축 + 30

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 1 && b == 1)	//빨(좌우)
		{
			if (_baleog.mapMaxRight > i)
			{
				_baleog.mapMaxRight = i;
			}
		}
	}
	//오른쪽면 충돌쓰
	if (_baleog.mapMaxRight <= _baleog.probeR)
	{
		_baleog.x = _baleog.mapMaxRight - 90;		//left, top 기준이니까!!! 90이하(몸통크기)의 값을 빼주면 오른쪽으로 훅훅 넘어갈거야. 꼭 90 넘게 주자
	}
}


void player::playerEnemyCollision()
{
	//for (int i = 0; i < _om->getVPulley().size(); i++)
	//{
	//	RECT temp;
	//	RECT rc = _om->getVPulley()[i]->getRect();

	//	if (IntersectRect(&temp, &_erik.rc, &rc))
	//	{ 
	//		if (_erik.rc.bottom >= rc.top)	//pulley 윗면이면
	//		{
	//			_erik.y = _erik.rc.bottom - (temp.bottom - temp.top) - 90;
	//			_erik.isJump = false;
	//			_erik.gravity = 0;
	//			_erik.jumpPower = 0;
	//		}
	//	}

	//}

}
void player::playerObstacleCollision()
{

	//배열 어떻게 불러오는거야........


	//RECT temp;
	//RECT rc = _om->getAwl0;
	//if (IntersectRect(&temp, &_erik.rc, &rc))
	//{
	//	if (_erik.rc.bottom >= rc.top)
	//	{
	//		_erik.y += 10;
	//		/*if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	//		{
	//			changeStateErik(ERIKSTATE::DEATH_RIGHT);
	//		}
	//		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	//		{
	//			changeStateErik(ERIKSTATE::DEATH_LEFT);
	//		}*/
	//	}
	//}
	//for (int i = 0; i < MAXAWL; i++)
	//{
	//	RECT temp;
	//	RECT rc = _om->getAwl[i];
	//	if (IntersectRect(&temp, &_erik.rc, &rc))
	//	{
	//		if (_erik.rc.bottom >= _om->getAwl[i])
	//		{
	//			_erik.y += 10;
	//			/*if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	//			{
	//				changeStateErik(ERIKSTATE::DEATH_RIGHT);
	//			}
	//			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	//			{
	//				changeStateErik(ERIKSTATE::DEATH_LEFT);
	//			}*/
	//		}

	//	}
	//}
	
	//rope
	/*for (int i = 0; i < MAXROPE; i++)
	{
		RECT temp;
		RECT rc = _om->getRopeRC();

		if (IntersectRect(&temp, &_erik.rc, &rc))
		{
			if (_erik.rc.top <= _om->getRopeRC().bottom)
			{
				_erik.y = _om->getRopeRC().bottom - (temp.bottom - temp.top) - 90;
				_erik.jumpPower = 0;
				_erik.gravity = 0;
				_erik.isJump = false;

				if (KEYMANAGER->isToggleKey(VK_UP))
				{
					_erik.rc.top = _om->getRopeRC().bottom;
				}
			}
		}
	}*/

	//if (_erik.rc.top <= _om->getRopeRC().bottom)
	//{
	//	//_erik.state = IDLE_RIGHT;
	//	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	//	{
	//		_erik.rc.top = _om->getRopeRC().bottom;
	//	}
	//}
}
void player::playerItemCollision()
{
}


void player::changeStateErik(ERIKSTATE state)
{
	_erik.state = state;
	switch (state)
	{
	case ERIKSTATE::RUN_RIGHT:
	case ERIKSTATE::RUN_LEFT:
		_erik.img = IMAGEMANAGER->findImage("ErikRun");
		break;
	case ERIKSTATE::DASH_RIGHT:
	case ERIKSTATE::DASH_LEFT:
		_erik.img = IMAGEMANAGER->findImage("ErikDash");
		break;
	case ERIKSTATE::JUMP_RIGHT:
	case ERIKSTATE::JUMP_LEFT:
		_erik.img = IMAGEMANAGER->findImage("ErikJump");
		break;
	case ERIKSTATE::JUMP_DOUBLE_RIGHT:
	case ERIKSTATE::JUMP_DOUBLE_LEFT:
		_erik.img = IMAGEMANAGER->findImage("ErikJumpDouble");
		break;
	case ERIKSTATE::PUSH_RIGHT:
	case ERIKSTATE::PUSH_LEFT:
		_erik.img = IMAGEMANAGER->findImage("ErikPush");
		break;
	case ERIKSTATE::LADDER:
		_erik.img = IMAGEMANAGER->findImage("ErikLadder");
		break;
	case ERIKSTATE::ROPE_RIGHT:
	case ERIKSTATE::ROPE_LEFT:
		_erik.img = IMAGEMANAGER->findImage("ErikRope");
		break;
	case ERIKSTATE::SWIM_IDLE_RIGHT:
	case ERIKSTATE::SWIM_IDLE_LEFT:
		_erik.img = IMAGEMANAGER->findImage("ErikSwimIdle");
		break;
	case ERIKSTATE::SWIM_DASH_RIGHT:
	case ERIKSTATE::SWIM_DASH_LEFT:
		_erik.img = IMAGEMANAGER->findImage("ErikSwimDash");
		break;
	case ERIKSTATE::DAMAGE_DEFAULT_RIGHT:
	case ERIKSTATE::DAMAGE_DEFAULT_LEFT:
		_erik.img = IMAGEMANAGER->findImage("ErikDamageDefault");
		break;
	case ERIKSTATE::DAMAGE_FALLING_RIGHT:
	case ERIKSTATE::DAMAGE_FALLING_LEFT:
		_erik.img = IMAGEMANAGER->findImage("ErikDamageFalling");
		break;
	case ERIKSTATE::DAMAGE_FIRE_RIGHT:
	case ERIKSTATE::DAMAGE_FIRE_LEFT:
		_erik.img = IMAGEMANAGER->findImage("ErikDamageFire");
		break;
	case ERIKSTATE::DEATH_RIGHT:
	case ERIKSTATE::DEATH_LEFT:
		_erik.img = IMAGEMANAGER->findImage("ErikDeath");
		break;
	default:
		_erik.img = IMAGEMANAGER->findImage("ErikIdle");
		break;
	
	}
}
void player::changeStateOlaf(OLAFSTATE state)
{
	_olaf.state = state;
	switch (state)
	{
	case OLAFSTATE::IDLE_TOP_RIGHT:
	case OLAFSTATE::IDLE_TOP_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafIdleTop");
		break;
	case OLAFSTATE::RUN_RIGHT:
	case OLAFSTATE::RUN_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafRun");
		break;
	case OLAFSTATE::RUN_TOP_RIGHT:
	case OLAFSTATE::RUN_TOP_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafRunTop");
		break;
	case OLAFSTATE::LADDER:
		_olaf.img = IMAGEMANAGER->findImage("OlafLadder");
		break;
	case OLAFSTATE::PUSH_RIGHT:
	case OLAFSTATE::PUSH_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafPush");
		break;
	case OLAFSTATE::DOWN_IDLE_RIGHT:
	case OLAFSTATE::DOWN_IDLE_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafDownIdle");
		break;
	case OLAFSTATE::DOWN_FAST_RIGHT:
	case OLAFSTATE::DOWN_FAST_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafDownFast");
		break;
	case OLAFSTATE::DOWN_NOSHIELD_RIGHT:
	case OLAFSTATE::DOWN_NOSHIELD_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafDownNoShield");
		break;
	case OLAFSTATE::SMALL_IDLE_RIGHT:
	case OLAFSTATE::SMALL_IDLE_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafSmallIdle");
		break;
	case OLAFSTATE::SMALL_RUN_RIGHT:
	case OLAFSTATE::SMALL_RUN_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafSmallRun");
		break;
	case OLAFSTATE::DAMAGE_DEFAULT_RIGHT:
	case OLAFSTATE::DAMAGE_DEFAULT_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafDamageDefault");
		break;
	case OLAFSTATE::DAMAGE_FALLING_RIGHT:
	case OLAFSTATE::DAMAGE_FALLING_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafDamageFalling");
		break;
	case OLAFSTATE::DAMAGE_FIRE_RIGHT:
	case OLAFSTATE::DAMAGE_FIRE_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafDamageFire");
		break;
	case OLAFSTATE::DEATH_RIGHT:
	case OLAFSTATE::DEATH_LEFT:
		_olaf.img = IMAGEMANAGER->findImage("OlafDeath");
		break;
	default:
		_olaf.img = IMAGEMANAGER->findImage("olafIdle");
		break;
	}
}
void player::changeStateBaleog(BALEOGSTATE state)
{
	_baleog.state = state;
	switch (state)
	{
	case BALEOGSTATE::RUN_RIGHT:
	case BALEOGSTATE::RUN_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogRun");
		break;
	case BALEOGSTATE::ATTACK_SWORD_RIGHT:
	case BALEOGSTATE::ATTACK_SWORD_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogAttackSword");
		break;
	case BALEOGSTATE::LADDER:
		_baleog.img = IMAGEMANAGER->findImage("BaleogLadder");
		break;
	case BALEOGSTATE::PUSH_RIGHT:
	case BALEOGSTATE::PUSH_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogPush");
		break;
	case BALEOGSTATE::ROPE_IDLE_RIGHT:
	case BALEOGSTATE::ROPE_IDLE_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogRopeIdle");
		break;
	case BALEOGSTATE::ROPE_MOVE_RIGHT:
	case BALEOGSTATE::ROPE_MOVE_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogRopeMove");
		break;
	case BALEOGSTATE::PUNCH_RIGHT:
	case BALEOGSTATE::PUNCH_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogPunch");
		break;
	case BALEOGSTATE::PUNCH_TOP_RIGHT:
	case BALEOGSTATE::PUNCH_TOP_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogPunchTop");
		break;
	case BALEOGSTATE::PUNCH_DIAGONAL_RIGHT:
	case BALEOGSTATE::PUNCH_DIAGONAL_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogPunchDiagonal");
		break;
	case BALEOGSTATE::SWING_RIGHT:
	case BALEOGSTATE::SWING_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogSwing");
		break;
	case BALEOGSTATE::FALLING_RIGHT:
	case BALEOGSTATE::FALLING_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogFalling");
		break;
	case BALEOGSTATE::DAMAGE_DEFAULT_RIGHT:
	case BALEOGSTATE::DAMAGE_DEFAULT_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogDamageDefault");
		break;
	case BALEOGSTATE::DAMAGE_FALLING_RIGHT:
	case BALEOGSTATE::DAMAGE_FALLING_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogDamageFalling");
		break;
	case BALEOGSTATE::DAMAGE_FIRE_RIGHT:
	case BALEOGSTATE::DAMAGE_FIRE_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogDamageFire");
		break;
	case BALEOGSTATE::DEATH_RIGHT:
	case BALEOGSTATE::DEATH_LEFT:
		_baleog.img = IMAGEMANAGER->findImage("BaleogDeath");
		break;
	default:
		_baleog.img = IMAGEMANAGER->findImage("BaleogIdle");
	}
}

void player::pulleyPlayerCollision()
{
}