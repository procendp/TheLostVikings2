#include "stdafx.h"
#include "spaceShip.h"

spaceShip::spaceShip()
{
}

spaceShip::~spaceShip()
{
}

HRESULT spaceShip::init()
{
	_ship = IMAGEMANAGER->addImage("플레이어", "rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_ship->setX(WINSIZEX / 2);
	_ship->setY(WINSIZEY / 2 + 200);

	_missile = new missile;
	_missile->init(30, 400);

	_hm = new hyunMoo;
	_hm->init(100, WINSIZEY);

	return S_OK;
}

void spaceShip::release()
{
	
}

void spaceShip::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _ship->getX() > 0)
	{
		_ship->setX(_ship->getX() - 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _ship->getX() + _ship->getWidth() < WINSIZEX)
	{
		_ship->setX(_ship->getX() + 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _ship->getY() > 0)
	{
		_ship->setY(_ship->getY() - 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _ship->getY() + _ship->getHeight() < WINSIZEY)
	{
		_ship->setY(_ship->getY() + 5);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_missile->fire(_ship->getCenterX(), _ship->getCenterY() - 15);	//15정도 떨어진 곳에서 쏘기 시작
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_hm->fire(_ship->getCenterX(), _ship->getCenterY() - 15);
	}



	_missile->update();		//missile(bullet)이 spaceShip에 걸려 있으니 spaceShip.cpp update()에 적어주는 게 맞아
	_hm->update();
}

void spaceShip::render()
{
	_ship->render(getMemDC(), _ship->getX(), _ship->getY());	//지워주면 안되나?
	_missile->render();
	_hm->render();
}
