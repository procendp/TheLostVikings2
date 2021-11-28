#include "stdafx.h"
#include "pixelcollision.h"
#include "player.h"


pixelCollision::pixelCollision()
{
}


pixelCollision::~pixelCollision()
{
}

HRESULT pixelCollision::init()
{
	//IMAGEMANAGER->addImage("¾ð´ö", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//_ball = IMAGEMANAGER->addImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	//_x = WINSIZEX / 2 - 150;
	//_y = WINSIZEY / 2 + 80;

	//_rc = RectMakeCenter(_x, _y, _player->_erikX->getWidth(), _player->_erikY->getHeight());
	//_probeY = _y + _player->_erikY->getHeight() / 2;
	
	//_probeY = _y + _player->_erikY() / 2;

	_player = new player;
	//_player->init();

	a = 0;
	r = 0;
	g = 0;
	b = 0;
	mapMaxTop = 0;
	mapMaxBottom = 2298;




	return S_OK;
}

void pixelCollision::release()
{


}

void pixelCollision::update()
{
	
	//_player->update();

	//if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 3;
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 3;

	_probeY = _player->_erikRC().bottom;

	for (int i = _probeY - 50; i < _probeY + 50; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("¹è°æÇÈ¼¿")->getMemDC(), _player->_erikX(), i);		//_xÃà, yÃà(i)

		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		//if (!(r == 255 && g == 1 && b == 1))	//»¡(¿·)
		//{
		//	
		//	break;
		//}
		//if (!(r == 1 && g == 1 && b == 255))	//ÆÄ(À§)
		//{
		//	break;
		//}
		if (r == 255 && g == 254 && b == 0)	//³ë(¹Ù´Ú)
		{
			//a = i - (_player->_erikRC().bottom - _player->_erikRC().top) / 2;

			if (mapMaxBottom > i)
			{
				mapMaxBottom = i;
			}
			//_y = i - _player->_erikY->getHeight() / 2;
			break;
		}

	}

	if (mapMaxBottom <= _probeY)
	{
		a = mapMaxBottom - (_player->_erikRC().bottom - _player->_erikRC().top) / 2;
	}

	//_rc = RectMakeCenter(_x, _y, _player->_erikX->getWidth(), _player->_erikY->getHeight());
}

void pixelCollision::render()
{
	//_player->render();
	//IMAGEMANAGER->findImage("¹è°æ")->render(getMemDC());
	//_ball->render(getMemDC(), _rc.left, _rc.top);
	//_player->_erikImg->render(getMemDC(), _rc.left, _rc.top);
	//_player->_erik.render(getMemDC(), _rc.left, _rc.top);
	//_player->_erikRC();

}