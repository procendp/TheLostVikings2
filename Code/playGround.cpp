#include "stdafx.h"
#include "playGround.h"



playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);
	
	IMAGEMANAGER->addImage("배경", "IMAGE/background.bmp", 3168, 2298, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경픽셀", "IMAGE/backgroundPixel.bmp", 3168, 2298, true, RGB(255, 0, 255));

	_player = new player;	//동적할당
	_player->init();		//player꺼를 그대로 쓰려면 동적할당 후, init, update, render 다 해주고 시작해야지

	_enemy = new enemy;
	_enemy->init();

	_om = new obstacleManager;
	_om->init();

	//_item = new item;
	//_item->init();


	//전방선언으로 소통
	_player->setEnemyMemoryAddressLink(_enemy);
	_enemy->setPlayerMemoryAddressLink(_player);
	
	_player->setOmMemoryAddressLink(_om);
	_om->setPlayerMemoryAddressLink(_player);

	//_player->setItemMemoryAddressLink(_item);
	//_item->setPlayerMemoryAddressLink(_player);

	
	isDebug = false;

	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();

	//SAFE_DELETE(_ship);		//앞 init에서 동적할당 해줬으니까 해제.

}

//여기에다 연산하세요 제에발
void playGround::update()
{
	gameNode::update();

	_player->update();
	_enemy->update();
	//_item->update();

	_om->update();

	int playerNum = _player->getCount();	//count 주고 카메라 다른 캐릭터로 업데이트
	
	switch (playerNum)
	{
	case 1:
		CAMERAMANAGER->updateScreen(_player->getErikX(), _player->getErikY());	//player에서 erik의 좌표를 쓰고 싶다면 player.h에서 퍼블릭 선언
		break;
	case 2:
		CAMERAMANAGER->updateScreen(_player->getOlafX(), _player->getOlafY());
		break;
	case 3:
		CAMERAMANAGER->updateScreen(_player->getBaleogX(), _player->getBaleogY());
		break;
	}
}

//여기에다 그려라 좀! 쫌!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// 위에 건들지마라
	//================제발 이 사이에 좀 그립시다==========================

	IMAGEMANAGER->findImage("배경")->render(getMemDC(), 0, 0);
	
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		isDebug = false;
		IMAGEMANAGER->findImage("배경픽셀")->render(getMemDC(), 0, 0);
	}
		
		
	_om->render();
	_player->render();
	_enemy->render();

	//_item->render();



	/*
	<카운트 체크용>
	char str[128];
	sprintf_s(str, "count : %d", _player->getCount());
	TextOut(getMemDC(), CAMERAMANAGER->getScreen().left + 20, CAMERAMANAGER->getScreen().top + 20, str, strlen(str));
	*/

	//==================================================
	//여기도 건들지마라
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	
	//getMemDC에서 복사해올 때, camera의 screen을 복사해 옴
    CAMERAMANAGER->render(getHDC(), 0, 0, getMemDC());/*, 1.0f*/		//1.0f는 줌 사이즈   
}											//getMemDC() 자체가 backBuffer()에서 가져오는거라   getBackBuffer()->getMemDC() 이렇게 안 써  줘도 될듯 

void playGround::debug()
{
}
 