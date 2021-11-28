#include "stdafx.h"
#include "playGround.h"



playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init(true);
	
	IMAGEMANAGER->addImage("���", "IMAGE/background.bmp", 3168, 2298, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ȼ�", "IMAGE/backgroundPixel.bmp", 3168, 2298, true, RGB(255, 0, 255));

	_player = new player;	//�����Ҵ�
	_player->init();		//player���� �״�� ������ �����Ҵ� ��, init, update, render �� ���ְ� �����ؾ���

	_enemy = new enemy;
	_enemy->init();

	_om = new obstacleManager;
	_om->init();

	//_item = new item;
	//_item->init();


	//���漱������ ����
	_player->setEnemyMemoryAddressLink(_enemy);
	_enemy->setPlayerMemoryAddressLink(_player);
	
	_player->setOmMemoryAddressLink(_om);
	_om->setPlayerMemoryAddressLink(_player);

	//_player->setItemMemoryAddressLink(_item);
	//_item->setPlayerMemoryAddressLink(_player);

	
	isDebug = false;

	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
void playGround::release()
{
	gameNode::release();

	//SAFE_DELETE(_ship);		//�� init���� �����Ҵ� �������ϱ� ����.

}

//���⿡�� �����ϼ��� ������
void playGround::update()
{
	gameNode::update();

	_player->update();
	_enemy->update();
	//_item->update();

	_om->update();

	int playerNum = _player->getCount();	//count �ְ� ī�޶� �ٸ� ĳ���ͷ� ������Ʈ
	
	switch (playerNum)
	{
	case 1:
		CAMERAMANAGER->updateScreen(_player->getErikX(), _player->getErikY());	//player���� erik�� ��ǥ�� ���� �ʹٸ� player.h���� �ۺ� ����
		break;
	case 2:
		CAMERAMANAGER->updateScreen(_player->getOlafX(), _player->getOlafY());
		break;
	case 3:
		CAMERAMANAGER->updateScreen(_player->getBaleogX(), _player->getBaleogY());
		break;
	}
}

//���⿡�� �׷��� ��! ��!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================

	IMAGEMANAGER->findImage("���")->render(getMemDC(), 0, 0);
	
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		isDebug = false;
		IMAGEMANAGER->findImage("����ȼ�")->render(getMemDC(), 0, 0);
	}
		
		
	_om->render();
	_player->render();
	_enemy->render();

	//_item->render();



	/*
	<ī��Ʈ üũ��>
	char str[128];
	sprintf_s(str, "count : %d", _player->getCount());
	TextOut(getMemDC(), CAMERAMANAGER->getScreen().left + 20, CAMERAMANAGER->getScreen().top + 20, str, strlen(str));
	*/

	//==================================================
	//���⵵ �ǵ�������
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	
	//getMemDC���� �����ؿ� ��, camera�� screen�� ������ ��
    CAMERAMANAGER->render(getHDC(), 0, 0, getMemDC());/*, 1.0f*/		//1.0f�� �� ������   
}											//getMemDC() ��ü�� backBuffer()���� �������°Ŷ�   getBackBuffer()->getMemDC() �̷��� �� ��  �൵ �ɵ� 

void playGround::debug()
{
}
 