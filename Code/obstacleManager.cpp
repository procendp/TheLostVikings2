#include "stdafx.h"
#include "obstacleManager.h"
#include "player.h"

HRESULT obstacleManager::init()
{
	setObstacleImageBundle();

	setBox();
	setDoor();
	setFire();
	setPulley();
	setStone();
	setWitch();

	//투명렉트용
	setAwl();
	setLadder();
	setRope();

	isDebug = false;


	return S_OK;
}

void obstacleManager::release()
{
}

void obstacleManager::update()
{

	updateBox();
	updateDoor();
	updateFire();
	updatePulley();
	updateStone();
	updateWitch();
	
	//투명렉트용
	updateAwl();
	updateLadder();
	updateRope();

	collisionPulley();

	
	
}

void obstacleManager::render()
{
	renderBox();
	renderDoor();
	renderFire();
	renderWitch();
	renderPulley();
	renderStone();

	//투명렉트용

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		isDebug = true;
		renderAwl();
		renderLadder();
		renderRope();

	}

}


//image 모음
void obstacleManager::setObstacleImageBundle()
{
	IMAGEMANAGER->addFrameImage("objectBox2_4x1", "IMAGE/objectBOX4x1.bmp", 0, 0, 384, 48, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("objectBox3_2x3", "IMAGE/objectBOX2x3.bmp", 0, 0, 192, 144, 2, 1, true, RGB(255, 0, 255));
				  
	IMAGEMANAGER->addFrameImage("objectDoor1_LtoR", "IMAGE/objectDoorLtoR.bmp", 0, 0, 96, 144, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("objectDoor2_Open", "IMAGE/objectDoorOpen.bmp", 0, 0, 204, 144, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("objectDoor3_RtoL", "IMAGE/objectDoorRtoL.bmp", 0, 0, 96, 144, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("objectPulley", "IMAGE/objectPulley.bmp", 0, 0, 192, 48, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("objectMovingStone", "IMAGE/objectMovingStone.bmp", 0, 0, 192, 96, 2, 1, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("Fire1", "IMAGE/objectFire1Frame.bmp", 0, 0, 324, 93, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Fire3", "IMAGE/objectFire3Frame.bmp", 0, 0, 864, 96, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("witchDefault", "IMAGE/witchDefault.bmp", 0, 0, 270, 90, 3, 1, true, RGB(255, 0, 255));
}

//init()
void obstacleManager::setBox()
{
	obstacle* _box;

	_box = new box;
	_box->init("objectBox2_4x1", PointMake(2497, 430));
	_vBox.push_back(_box);

	_box = new box;
	_box->init("objectBox3_2x3", PointMake(2548, 1917));
	_vBox.push_back(_box);
	
	
	/*for (int i = 0; i < 2; i++)
	{
		_objectBox[1].img = IMAGEMANAGER->findImage("objectBox2_4x1");
		_objectBox[1].x = 2497;
		_objectBox[1].y = 430;

		_objectBox[2].img = IMAGEMANAGER->findImage("objectBox3_2x3");
		_objectBox[2].x = 2548;
		_objectBox[2].y = 1917;
	}*/
}
void obstacleManager::setDoor()
{
	
	obstacle* _door;

	_door = new door;
	_door->init("objectDoor1_LtoR", PointMake(2976, 669));	//2시
	_vDoor.push_back(_door);

	_door = new door;
	_door->init("objectDoor3_RtoL", PointMake(1967, 1389));	//6시 중간
	_vDoor.push_back(_door);

	_door = new door;
	_door->init("objectDoor3_RtoL", PointMake(2928, 1916));	//5시
	_vDoor.push_back(_door);

	////3번째는 열린거
	//if (2시꺼 반응하면)
	//{
	//	//바꿔
	//	_door = new door;
	//	_door->init("objectDoor2_Open", PointMake(2976, 669));	//2시
	//	_vDoor.push_back(_door);
	//	//기존꺼 사라지게
	//}
	//else if (6시꺼 반응하면 )
	//{
	//	//바꿔
	//	_door = new door;
	//	_door->init("objectDoor2_Open", PointMake(1967, 1389));	//6시
	//	_vDoor.push_back(_door);
	//	//기존꺼 사라지게
	//}
	//else if (5시꺼 반응하면)
	//{
	//	//바꿔
	//	_door = new door;
	//	_door->init("objectDoor2_Open", PointMake(2928, 1916));	//5시
	//	_vDoor.push_back(_door);
	//	//기존꺼 사라지게
	//}
}
void obstacleManager::setFire()
{
	obstacle* _fire;

	//fire1
	_fire = new stone;
	_fire->init("Fire1", PointMake(2782, 142));
	_vFire.push_back(_fire);

	//fire3
	_fire = new stone;
	_fire->init("Fire3", PointMake(2638, 1347));
	_vFire.push_back(_fire);

	_fire = new stone;
	_fire->init("Fire3", PointMake(2783, 1581));
	_vFire.push_back(_fire);

	_fire = new stone;
	_fire->init("Fire3", PointMake(2638, 1826));
	_vFire.push_back(_fire);
}
void obstacleManager::setPulley()
{
	//벡터에 담았다 5개
	obstacle* _pulley;

	_pulley = new pulley;
	_pulley->init("objectPulley", PointMake(960, 236));		//12시
	_vPulley.push_back(_pulley);

	_pulley = new pulley;
	_pulley->init("objectPulley", PointMake(2016, 946));	//drrL
	_vPulley.push_back(_pulley);

	_pulley = new pulley;
	_pulley->init("objectPulley", PointMake(2305, 946));	//drrR
	_vPulley.push_back(_pulley);

	_pulley = new pulley;
	_pulley->init("objectPulley", PointMake(3026, 813));	//2시		//3026, 813			//왜 사이즈 달라지고 프레임 드랍 심하지
	_vPulley.push_back(_pulley);
	
	_pulley = new pulley;
	_pulley->init("objectPulley", PointMake(2448, 2110));		//5시		//2448, 2110
	_vPulley.push_back(_pulley);	//vPulley라는 벡터에 풀리를 넣은거임

	
}
void obstacleManager::setStone()
{
	obstacle* _stone;

	_stone = new stone;
	_stone->init("objectMovingStone", PointMake(1104, 1245));
	_vStone.push_back(_stone);

	_stone = new stone;
	_stone->init("objectMovingStone", PointMake(1775, 1005));
	_vStone.push_back(_stone);
	
}
void obstacleManager::setAwl()
{
	for (int i = 0; i < MAXAWL; i++)
	{
		_obstacleAwl[0].x = 1201;
		_obstacleAwl[0].y = 1629;

		_obstacleAwl[1].x = 1249;
		_obstacleAwl[1].y = 1629;
		
		_obstacleAwl[2].x = 1632;
		_obstacleAwl[2].y = 1629;
		
		_obstacleAwl[3].x = 1680;
		_obstacleAwl[3].y = 1677;
		
		_obstacleAwl[4].x = 1728;
		_obstacleAwl[4].y = 1725;
		
		_obstacleAwl[5].x = 1776;
		_obstacleAwl[5].y = 1773;
		
		_obstacleAwl[6].x = 1824;
		_obstacleAwl[6].y = 1821;
		
		_obstacleAwl[7].x = 1872;
		_obstacleAwl[7].y = 1917;
		
		_obstacleAwl[8].x = 1920;
		_obstacleAwl[8].y = 1917;
		
		_obstacleAwl[9].x = 1968;
		_obstacleAwl[9].y = 1917;
		
		_obstacleAwl[10].x = 2016;
		_obstacleAwl[10].y = 1917;
		
		_obstacleAwl[11].x = 2064;
		_obstacleAwl[11].y = 1917;
	}
}
void obstacleManager::setLadder()
{
	for (int i = 0; i < MAXLADDER; i++)		//MAXLADDER 8
	{
		_obstacleLadder[0].x = 816;
		_obstacleLadder[0].y = 669;

		_obstacleLadder[1].x = 1200;
		_obstacleLadder[1].y = 236;

		_obstacleLadder[2].x = 1295;
		_obstacleLadder[2].y = 380;

		_obstacleLadder[3].x = 1535;
		_obstacleLadder[3].y = 908;

		_obstacleLadder[4].x = 1679;
		_obstacleLadder[4].y = 236;

		_obstacleLadder[5].x = 2638;
		_obstacleLadder[5].y = 1100;

		_obstacleLadder[6].x = 2736;
		_obstacleLadder[6].y = 477;

		_obstacleLadder[7].x = 3022;
		_obstacleLadder[7].y = 236;
	}

}
void obstacleManager::setRope()
{
	for (int i = 0; i < MAXROPE; i++)		//MAXLADDER 5
	{
		_obstacleRope[0].x = 333;
		_obstacleRope[0].y = 1485;

		_obstacleRope[1].x = 1200;
		_obstacleRope[1].y = 140;

		_obstacleRope[2].x = 2257;
		_obstacleRope[2].y = 93;

		_obstacleRope[3].x = 1400;
		_obstacleRope[3].y = 380;
	}
}
void obstacleManager::setWitch()
{
	obstacle* _witch;

	_witch = new witch;
	_witch->init("witchDefault", PointMake(2200, 1490));
	_vWitch.push_back(_witch);
}

//update()
void obstacleManager::updateBox()
{
	for (_viBox = _vBox.begin(); _viBox != _vBox.end(); ++_viBox)
	{
		(*_viBox)->update();
	}
}
void obstacleManager::updateDoor()
{
	for (_viDoor = _vDoor.begin(); _viDoor != _vDoor.end(); ++_viDoor)
	{
		(*_viDoor)->update();
	}
}
void obstacleManager::updateFire()
{
	for (_viFire = _vFire.begin(); _viFire != _vFire.end(); ++_viFire)
	{
		(*_viFire)->update();
	}
}
void obstacleManager::updatePulley()		//update
{
	for (_viPulley = _vPulley.begin(); _viPulley != _vPulley.end(); ++_viPulley)
	{
		(*_viPulley)->update();
		//해당되는 애한테 하는 명령
	}
}
void obstacleManager::updateStone()
{
	for (_viStone = _vStone.begin(); _viStone != _vStone.end(); ++_viStone)
	{
		(*_viStone)->update();
	}
}
void obstacleManager::updateAwl()
{
	for (int i = 0; i < MAXAWL; i++)	//MAXAWL 12
	{
		_obstacleAwl[0].rc = RectMake(_obstacleAwl[0].x, _obstacleAwl[0].y, 48, 96);
		_obstacleAwl[1].rc = RectMake(_obstacleAwl[1].x, _obstacleAwl[1].y, 48, 96);
		_obstacleAwl[2].rc = RectMake(_obstacleAwl[2].x, _obstacleAwl[2].y, 48, 96);
		_obstacleAwl[3].rc = RectMake(_obstacleAwl[3].x, _obstacleAwl[3].y, 48, 96);
		_obstacleAwl[4].rc = RectMake(_obstacleAwl[4].x, _obstacleAwl[4].y, 48, 96);
		_obstacleAwl[5].rc = RectMake(_obstacleAwl[5].x, _obstacleAwl[5].y, 48, 96);
		_obstacleAwl[6].rc = RectMake(_obstacleAwl[6].x, _obstacleAwl[6].y, 48, 96);
		_obstacleAwl[7].rc = RectMake(_obstacleAwl[7].x, _obstacleAwl[7].y, 48, 96);
		_obstacleAwl[8].rc = RectMake(_obstacleAwl[8].x, _obstacleAwl[8].y, 48, 96);
		_obstacleAwl[9].rc = RectMake(_obstacleAwl[9].x, _obstacleAwl[9].y, 48, 96);
		_obstacleAwl[10].rc = RectMake(_obstacleAwl[10].x, _obstacleAwl[10].y, 48, 96);
		_obstacleAwl[11].rc = RectMake(_obstacleAwl[11].x, _obstacleAwl[11].y, 48, 96);
	}
}
void obstacleManager::updateLadder()
{
	for (int i = 0; i < MAXLADDER; i++)	//MAXLADDER 8		//좌에서 우 순서
	{
		_obstacleLadder[0].rc = RectMake(_obstacleLadder[0].x, _obstacleLadder[0].y, 98, 96);
		_obstacleLadder[1].rc = RectMake(_obstacleLadder[1].x, _obstacleLadder[1].y, 98, 145);
		_obstacleLadder[2].rc = RectMake(_obstacleLadder[2].x, _obstacleLadder[2].y, 98, 288);
		_obstacleLadder[3].rc = RectMake(_obstacleLadder[3].x, _obstacleLadder[3].y, 98, 192);
		_obstacleLadder[4].rc = RectMake(_obstacleLadder[4].x, _obstacleLadder[4].y, 98, 145);
		_obstacleLadder[5].rc = RectMake(_obstacleLadder[5].x, _obstacleLadder[5].y, 98, 140);
		_obstacleLadder[6].rc = RectMake(_obstacleLadder[6].x, _obstacleLadder[6].y, 98, 336);
		_obstacleLadder[7].rc = RectMake(_obstacleLadder[7].x, _obstacleLadder[7].y, 98, 241);
	}
}
void obstacleManager::updateRope()
{
	for (int i = 0; i < MAXROPE; i++)	//MAXROPE 5
	{
		_obstacleRope[0].rc = RectMake(_obstacleRope[0].x, _obstacleRope[0].y, 625, 13);
		_obstacleRope[1].rc = RectMake(_obstacleRope[1].x, _obstacleRope[1].y, 960, 13);
		_obstacleRope[2].rc = RectMake(_obstacleRope[2].x, _obstacleRope[2].y, 585, 13);
		_obstacleRope[3].rc = RectMake(_obstacleRope[3].x, _obstacleRope[3].y, 1105, 13);
	}
}
void obstacleManager::updateWitch()
{
	for (_viWitch = _vWitch.begin(); _viWitch != _vWitch.end(); ++_viWitch)
	{
		(*_viWitch)->update();
	}
}

//render()
void obstacleManager::renderBox()
{
	for (_viBox = _vBox.begin(); _viBox != _vBox.end(); ++_viBox)
	{
		(*_viBox)->render();
	}
}
void obstacleManager::renderDoor()
{
	for (_viDoor = _vDoor.begin(); _viDoor != _vDoor.end(); ++_viDoor)
	{
		(*_viDoor)->render();
	}
}
void obstacleManager::renderFire()
{
	for (_viFire = _vFire.begin(); _viFire != _vFire.end(); ++_viFire)
	{
		(*_viFire)->render();
	}
}
void obstacleManager::renderPulley()
{
	for (_viPulley = _vPulley.begin(); _viPulley != _vPulley.end(); ++_viPulley)
	{
		(*_viPulley)->render();
	}
}
void obstacleManager::renderStone()
{
	for (_viStone = _vStone.begin(); _viStone != _vStone.end(); ++_viStone)
	{
		(*_viStone)->render();
	}
}
void obstacleManager::renderAwl()
{
	for (int i = 0; i < MAXAWL; i++)
	{
		//img->render 필요없지
		Rectangle(getMemDC(), _obstacleAwl[0].rc);
		Rectangle(getMemDC(), _obstacleAwl[1].rc);
		Rectangle(getMemDC(), _obstacleAwl[2].rc);
		Rectangle(getMemDC(), _obstacleAwl[3].rc);
		Rectangle(getMemDC(), _obstacleAwl[4].rc);
		Rectangle(getMemDC(), _obstacleAwl[5].rc);
		Rectangle(getMemDC(), _obstacleAwl[6].rc);
		Rectangle(getMemDC(), _obstacleAwl[7].rc);
		Rectangle(getMemDC(), _obstacleAwl[8].rc);
		Rectangle(getMemDC(), _obstacleAwl[9].rc);
		Rectangle(getMemDC(), _obstacleAwl[10].rc);
		Rectangle(getMemDC(), _obstacleAwl[11].rc);
	}
}
void obstacleManager::renderLadder()
{
	//ladder	//투명렉트니까 나중에 주석
	for (int i = 0; i < MAXLADDER; i++)		//MAXLADDER 8
	{
		//img->render 필요없지
		Rectangle(getMemDC(), _obstacleLadder[0].rc);
		Rectangle(getMemDC(), _obstacleLadder[1].rc);
		Rectangle(getMemDC(), _obstacleLadder[2].rc);
		Rectangle(getMemDC(), _obstacleLadder[3].rc);
		Rectangle(getMemDC(), _obstacleLadder[4].rc);
		Rectangle(getMemDC(), _obstacleLadder[5].rc);
		Rectangle(getMemDC(), _obstacleLadder[6].rc);
		Rectangle(getMemDC(), _obstacleLadder[7].rc);
	}
}
void obstacleManager::renderRope()
{
	//Rope	//투명렉트니까 나중에 주석
	for (int i = 0; i < MAXROPE; i++)		//MAXROPE 5
	{
		//img->render 필요없지
		Rectangle(getMemDC(), _obstacleRope[0].rc);
		Rectangle(getMemDC(), _obstacleRope[1].rc);
		Rectangle(getMemDC(), _obstacleRope[2].rc);
		Rectangle(getMemDC(), _obstacleRope[3].rc);
	}
}
void obstacleManager::renderWitch()
{
	for (_viWitch = _vWitch.begin(); _viWitch != _vWitch.end(); ++_viWitch)
	{
		(*_viWitch)->render();
	}
}


void obstacleManager::collisionPulley()
{
	for (int i = 0; i < _vPulley.size(); i++)
	{
		RECT temp;
		RECT rc = _vPulley[i]->getRect();
		
		if (IntersectRect(&temp, &_player->getErikRC(), &rc))
		{
			if (_player->getErikRC().bottom >= rc.top)	//erik이 도르레 윗면에서 부딪힐 때
			{
				_player->setErikY(_player->getErikRC().bottom - (temp.bottom - temp.top) - 90);		//쥰내 신기
				_player->setErikJumpPower(0);
				_player->setErikGravity(0);
				_player->setErikIsJump(false);

				if (KEYMANAGER->isToggleKey(VK_UP))
				{
					_vPulley[i]->setRcMoveY(_vPulley[i]->getMoveY() - 3);
				}
				/*else if (KEYMANAGER->isToggleKey(VK_DOWN))
				{
					_player->setErikY(_player->getErikRC().bottom + 3);
					_player->setErikY(_player->getErikRC().top+ 3);
				}*/
			}

			////erik이 도르레 아랫면에 충돌할 때
			//if (_player->getErikRC().top < rc.bottom)	
			//{
			//	_player->setErikY(_player->getErikRC().top + (temp.bottom - temp.top));		//쥰내 신기
			//	_player->setErikJumpPower(0);
			//	_player->setErikGravity(0);
			//	_player->setErikIsJump(false);

			//	
			//	/*else if (KEYMANAGER->isToggleKey(VK_DOWN))
			//	{
			//		_player->setErikY(_player->getErikRC().bottom + 3);
			//		_player->setErikY(_player->getErikRC().top+ 3);
			//	}*/
			//}

		}
	}
}

void obstacleManager::motionPulley(int arrNum)
{
	//(*_vPulley.begin() + arrNum)->playerPulleyMove((*_vPulley.begin() + arrNum)->getRect());
}

//void obstacleManager::removePulley(int arrNum)
//{
//	_vPulley.erase(_vPulley.begin() + arrNum);
//}
