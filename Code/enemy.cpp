#include "stdafx.h"
#include "enemy.h"
#include "player.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init()
{
	enemyImageBundle();

	setEnemyPirate();
	setEnemySkeleton();
	setEnemyTankBomb1();
	setEnemyTankBomb2();

	fireTankBomb1();
	fireTankBomb2();

	_pirate.frameCount = 0;
	_pirate.frameIndex = 0;

	_skeleton.frameCount = 0;
	_skeleton.frameIndex = 0;

	isDebug = false;

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	frameUpdatePirate();
	frameUpdateSkeleton();

	movePirate();
	moveSkeleton();
	moveTankBomb1();
	moveTankBomb2();

	fireTankBomb1();
	fireTankBomb2();

	
	_pirate.rc = RectMake(_pirate.x, _pirate.y, 90, 90);
	_skeleton.rc = RectMake(_skeleton.x, _skeleton.y, 90, 90);
	
}

void enemy::render()
{

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		isDebug = true;

		Rectangle(getMemDC(), _pirate.rc);
		Rectangle(getMemDC(), _skeleton.rc);
		for (int i = 0; i < BOMBMAX; i++)
		{
			if (!_tankBomb1[i].isFire) continue;
			Rectangle(getMemDC(), _tankBomb1[i].rc);

			if (!_tankBomb2[i].isFire) continue;
			Rectangle(getMemDC(), _tankBomb2[i].rc);
		}

	}


	//pirate
	_pirate.img->frameRender(getMemDC(), _pirate.x, _pirate.y);

	//skeleton
	_skeleton.img->frameRender(getMemDC(), _skeleton.x, _skeleton.y);

	//tankBomb1
	for (int i = 0; i < BOMBMAX; i++)
	{
		if (!_tankBomb1[i].isFire) continue;
		_tankBomb1[i].img->render(getMemDC(), _tankBomb1[i].x, _tankBomb1[i].y);
	}

	//tankBomb2
	for (int i = 0; i < BOMBMAX; i++)
	{
		if (!_tankBomb2[i].isFire) continue;
		_tankBomb2[i].img->render(getMemDC(), _tankBomb2[i].x, _tankBomb2[i].y);
	}

	
}

void enemy::enemyImageBundle()
{
	IMAGEMANAGER->addFrameImage("PirateMove", "IMAGE/pirateMove.bmp", 180, 180, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PirateAttack", "IMAGE/PirateAttack.bmp", 450, 180, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SkeletonMove", "IMAGE/skeletonMove.bmp", 360, 180, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SkeletonAttack", "IMAGE/SkeletonAttack.bmp", 270, 180, 3, 2, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("enemyTankBomb", "IMAGE/enemyTankBomb.bmp", 45, 45, true, RGB(255, 0, 255));
}

void enemy::setEnemyPirate()
{
	_pirate.img = IMAGEMANAGER->findImage("PirateMove");
	changeStatePirate(PIRATESTATE::MOVE_RIGHT);
	_pirate.x = 1550;
	_pirate.y = 150;
	_pirate.moveFirst = false;
}
void enemy::setEnemySkeleton()
{
	_skeleton.img = IMAGEMANAGER->findImage("SkeletonMove");
	changeStateSkeleton(SKELETONSTATE::MOVE_RIGHT);
	_skeleton.x = 1210;
	_skeleton.y = 870;
	_skeleton.moveFirst = false;
}
//시작하자마자 움직이기 위함.

void enemy::setEnemyTankBomb1()
{
	//tankBomb1
	for (int i = 0; i < BOMBMAX; i++)
	{
		_tankBomb1[i].img = IMAGEMANAGER->findImage("enemyTankBomb");
		_tankBomb1[i].x = 1172;
		_tankBomb1[i].y = 1155;
		_tankBomb1[i].isFire = false;
		_tankBomb1[i].speed = 3;
	}
}
void enemy::setEnemyTankBomb2()
{
	//tankBomb2
	for (int i = 0; i < BOMBMAX; i++)
	{
		_tankBomb2[i].img = IMAGEMANAGER->findImage("enemyTankBomb");
		_tankBomb2[i].x = 1453;
		_tankBomb2[i].y = 1485;
		_tankBomb2[i].isFire = false;
		_tankBomb2[i].speed = 3;
	}
}

void enemy::frameUpdatePirate()
{
	_pirate.frameCount++;

	if (_pirate.frameCount % 5 == 0)
	{
		if (_pirate.state == PIRATESTATE::MOVE_RIGHT)
		{
			_pirate.img->setFrameY(0);
			_pirate.img->setFrameX(_pirate.frameIndex);
			_pirate.frameIndex++;

			if (_pirate.frameIndex >= 1) _pirate.frameIndex = 0;
		}
		if (_pirate.state == PIRATESTATE::MOVE_LEFT)
		{
			_pirate.img->setFrameY(1);
			_pirate.img->setFrameX(_pirate.frameIndex);
			_pirate.frameIndex++;

			if (_pirate.frameIndex >= 1) _pirate.frameIndex = 0;
		}

		if (_pirate.state == PIRATESTATE::ATTACK_RIGHT)
		{
			_pirate.img->setFrameY(0);
			_pirate.img->setFrameX(_pirate.frameIndex);
			_pirate.frameIndex++;

			if (_pirate.frameIndex >= 4) _pirate.frameIndex = 0;
		}
		if (_pirate.state == PIRATESTATE::ATTACK_LEFT)
		{
			_pirate.img->setFrameY(1);
			_pirate.img->setFrameX(_pirate.frameIndex);
			_pirate.frameIndex++;

			if (_pirate.frameIndex >= 4) _pirate.frameIndex = 0;
		}
		if (_pirate.state == PIRATESTATE::DEATH_RIGHT)
		{
			_pirate.img->setFrameY(0);
			_pirate.img->setFrameX(_pirate.frameIndex);
			_pirate.frameIndex++;

			if (_pirate.frameIndex >= 4) _pirate.frameIndex = 0;
		}
		if (_pirate.state == PIRATESTATE::DEATH_LEFT)
		{
			_pirate.img->setFrameY(0);
			_pirate.img->setFrameX(_pirate.frameIndex);
			_pirate.frameIndex++;

			if (_pirate.frameIndex >= 4) _pirate.frameIndex = 0;
		}
		
		_pirate.frameCount = 0;
	}
}
void enemy::frameUpdateSkeleton()
{
	_skeleton.frameCount++;

	if (_skeleton.frameCount % 10 == 0)
	{
		if (_skeleton.state == SKELETONSTATE::MOVE_RIGHT)
		{
			_skeleton.img->setFrameY(0);
			_skeleton.img->setFrameX(_skeleton.frameIndex);
			_skeleton.frameIndex++;

			if (_skeleton.frameIndex >= 1) _skeleton.frameIndex = 0;
		}
		if (_skeleton.state == SKELETONSTATE::MOVE_LEFT)
		{
			_skeleton.img->setFrameY(1);
			_skeleton.img->setFrameX(_skeleton.frameIndex);
			_skeleton.frameIndex++;

			if (_skeleton.frameIndex >= 1) _skeleton.frameIndex = 0;
		}

		if (_skeleton.state == SKELETONSTATE::ATTACK_RIGHT)
		{
			_skeleton.img->setFrameY(0);
			_skeleton.img->setFrameX(_skeleton.frameIndex);
			_skeleton.frameIndex++;

			if (_skeleton.frameIndex >= 4) _skeleton.frameIndex = 0;
		}
		if (_skeleton.state == SKELETONSTATE::ATTACK_LEFT)
		{
			_skeleton.img->setFrameY(1);
			_skeleton.img->setFrameX(_skeleton.frameIndex);
			_skeleton.frameIndex++;

			if (_skeleton.frameIndex >= 4) _skeleton.frameIndex = 0;
		}
		if (_skeleton.state == SKELETONSTATE::DEATH_RIGHT)
		{
			_skeleton.img->setFrameY(0);
			_skeleton.img->setFrameX(_skeleton.frameIndex);
			_skeleton.frameIndex++;

			if (_skeleton.frameIndex >= 4) _skeleton.frameIndex = 0;
		}
		if (_skeleton.state == SKELETONSTATE::DEATH_LEFT)
		{
			_skeleton.img->setFrameY(0);
			_skeleton.img->setFrameX(_skeleton.frameIndex);
			_skeleton.frameIndex++;

			if (_skeleton.frameIndex >= 4) _skeleton.frameIndex = 0;
		}

		_skeleton.frameCount = 0;
	}
}

void enemy::movePirate()
{
	if (!_pirate.moveFirst)		//false
	{
		_pirate.x += 2;
		changeStatePirate(PIRATESTATE::MOVE_RIGHT);

		//patrol
		if (_pirate.x + 90 >= 1800)	//오른쪽 끝까지 갔으면
		{
			changeStatePirate(PIRATESTATE::MOVE_LEFT);
			_pirate.moveFirst = true;
		}
	}
	if (_pirate.moveFirst)
	{
		_pirate.x -= 2;

		if(_pirate.x <= 1400)	//왼쪽 끝까지 갔으면
		{
			changeStatePirate(PIRATESTATE::MOVE_RIGHT);
			_pirate.moveFirst = false;
		}
	}
	//플레이어와 충돌
	//Pirate <-> Erik
	//RECT temp;
	//if (IntersectRect(&temp, &_EPplayer->getErikRC(), &_pirate.rc) && _pirate.moveFirst)
	//{
	//	///이 부분 해결하자
	//	///_EPplayer->_erikX -= 3;
	//	//_player->setErikStruct( _player->getErikStruct().x -= _player->getErikStruct().jumpPower);
	//	//_player->ErikStruct().jumpPower -= _player->ErikStruct().gravity;
	//	//_erik.img->setY(_erik.y);
	//	//_pirate._moveFirst = false;
	//}
	////Pirate <-> Olaf
	//if (IntersectRect(&temp, &_EPplayer->getOlafRC(), &_pirate.rc) && _pirate.moveFirst)
	//{
	//	///_player->_olafX -= 3;
	//	//_pirate._moveFirst = false;
	//}
	////Pirate <-> Baleog
	//if (IntersectRect(&temp, &_EPplayer->getBaleogRC(), &_pirate.rc) && _pirate.moveFirst)
	//{
	//	///_player->_baleogX -= 3;
	//	//_pirate._moveFirst = false;
	//}

}
void enemy::moveSkeleton()
{
	if (!_skeleton.moveFirst)		//false
	{
		_skeleton.x += 1;

		//patrol
		if (_skeleton.x + 90 >= 1441)	//오른쪽 끝까지 갔으면
		{
			_skeleton.img = IMAGEMANAGER->findImage("SkeletonMove");
			changeStateSkeleton(SKELETONSTATE::MOVE_LEFT);
			_skeleton.moveFirst = true;
		}
	}
	if (_skeleton.moveFirst)
	{
		_skeleton.x -= 1;

		if (_skeleton.x <= 1099)	//왼쪽 끝까지 갔으면
		{
			_skeleton.img = IMAGEMANAGER->findImage("SkeletonMove");
			changeStateSkeleton(SKELETONSTATE::MOVE_RIGHT);
			_skeleton.moveFirst = false;
		}
	}
	//플레이어와 충돌
	//Skeleton <-> Erik
	RECT temp;
	if (IntersectRect(&temp, &_EPplayer->getErikRC(), &_skeleton.rc) && _skeleton.moveFirst)
	{
		_skeleton.moveFirst = false;
	}
	//Skeleton <-> Olaf
	if (IntersectRect(&temp, &_EPplayer->getOlafRC(), &_skeleton.rc) && _skeleton.moveFirst)
	{
		_skeleton.moveFirst = false;
	}
	//Skeleton <-> Baleog
	if (IntersectRect(&temp, &_EPplayer->getBaleogRC(), &_skeleton.rc) && _skeleton.moveFirst)
	{
		_skeleton.moveFirst = false;
	}
}

void enemy::fireTankBomb1()
{
	for (int  i = 0; i < BOMBMAX; i++)
	{
		if (_tankBomb1[i].isFire) continue;
		
		_tankBomb1[i].x = 1172;
		_tankBomb1[i].y = 1155;
		_tankBomb1[i].rc = RectMake(_tankBomb1[i].x, _tankBomb1[i].y, 45, 45);
		_tankBomb1[i].isFire = true;
		break;
	}
}
void enemy::moveTankBomb1()
{
	for (int i = 0; i < BOMBMAX; i++)
	{
		if (!_tankBomb1[i].isFire) continue;

		_tankBomb1[i].x -= _tankBomb1[i].speed;		//speed = 3
		_tankBomb1[i].rc = RectMake(_tankBomb1[i].x, _tankBomb1[i].y, 45, 45);

		//벽 충돌하면 사라지기
		if (_tankBomb1[i].x < 766)
		{
			_tankBomb1[i].isFire = false;
		}

		//플레이어와 충돌하면 사라지기
		//TankBomb1 <-> Erik
		RECT temp;
		if (IntersectRect(&temp, &_EPplayer->getErikRC(), &_tankBomb1[i].rc) && _tankBomb1[i].isFire)
		{
			_tankBomb1[i].isFire = false;
			break;
		}
		//TankBomb1 <-> Olaf
		if (IntersectRect(&temp, &_EPplayer->getOlafRC(), &_tankBomb1[i].rc) && _tankBomb1[i].isFire)
		{
			_tankBomb1[i].isFire = false;
			break;
		}
		//TankBomb1 <-> Baleog
		if (IntersectRect(&temp, &_EPplayer->getBaleogRC(), &_tankBomb1[i].rc) && _tankBomb1[i].isFire)
		{
			_tankBomb1[i].isFire = false;
			break;
		}
	}
}
void enemy::fireTankBomb2()
{
	for (int i = 0; i < BOMBMAX; i++)
	{
		if (_tankBomb2[i].isFire) continue;

		_tankBomb2[i].img = IMAGEMANAGER->findImage("enemyTankBomb");
		_tankBomb2[i].x = 1453;
		_tankBomb2[i].y = 1485;
		_tankBomb2[i].rc = RectMake(_tankBomb2[i].x, _tankBomb2[i].y, 45, 45);
		_tankBomb2[i].isFire = true;
		break;
	}
}
void enemy::moveTankBomb2()
{
	for (int i = 0; i < BOMBMAX; i++)
	{
		if (!_tankBomb2[i].isFire) continue;
		
		_tankBomb2[i].x -= _tankBomb2[i].speed;		//speed = 3
		_tankBomb2[i].rc = RectMake(_tankBomb2[i].x, _tankBomb2[i].y, 45, 45);

		//벽 충돌하면 사라지기
		if (_tankBomb2[i].x < 960)	
		{
			_tankBomb2[i].isFire = false;
		}

		//플레이어와 충돌하면 사라지기
		//TankBomb2 <-> Erik
		RECT temp;
		if (IntersectRect(&temp, &_EPplayer->getErikRC(), &_tankBomb2[i].rc) && _tankBomb2[i].isFire)
		{
			_tankBomb2[i].isFire = false;
			break;
		}
		//TankBomb2 <-> Olaf
		if (IntersectRect(&temp, &_EPplayer->getOlafRC(), &_tankBomb2[i].rc) && _tankBomb2[i].isFire)
		{
			_tankBomb2[i].isFire = false;
			break;
		}
		//TankBomb2 <-> Baleog
		if (IntersectRect(&temp, &_EPplayer->getBaleogRC(), &_tankBomb2[i].rc) && _tankBomb2[i].isFire)
		{
			_tankBomb2[i].isFire = false;
			break;
		}
	}
}

void enemy::changeStatePirate(PIRATESTATE state)
{
	_pirate.state = state;
	switch (state)
	{
	case PIRATESTATE::MOVE_RIGHT:
	case PIRATESTATE::MOVE_LEFT:
		_pirate.img = IMAGEMANAGER->findImage("PirateMove");
		break;
	case PIRATESTATE::ATTACK_RIGHT:
	case PIRATESTATE::ATTACK_LEFT:
		_pirate.img = IMAGEMANAGER->findImage("PirateAttack");
		break;
	case PIRATESTATE::DEATH_RIGHT:
	case PIRATESTATE::DEATH_LEFT:
		_pirate.img = IMAGEMANAGER->findImage("enemyTankBomb");
		break;
	}
}
void enemy::changeStateSkeleton(SKELETONSTATE state)
{
	_skeleton.state = state;
	switch (state)
	{
	case SKELETONSTATE::MOVE_RIGHT:
	case SKELETONSTATE::MOVE_LEFT:
		_skeleton.img = IMAGEMANAGER->findImage("SkeletonMove");
		break;
	case SKELETONSTATE::ATTACK_RIGHT:
	case SKELETONSTATE::ATTACK_LEFT:
		_skeleton.img = IMAGEMANAGER->findImage("SkeletonAttack");
		break;
	case SKELETONSTATE::DEATH_RIGHT:
	case SKELETONSTATE::DEATH_LEFT:
		_skeleton.img = IMAGEMANAGER->findImage("enemyTankBomb");
		break;
	}

}

void enemy::enemyPlayerCollision()
{
}
