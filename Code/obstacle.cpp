#include "stdafx.h"
#include "obstacle.h"

HRESULT obstacle::init()
{
	return S_OK;
}

//HRESULT obstacle::init(POINT position)	//rect
//{
//
//	_currentFrameX = _currentFrameY = 0;
//	_count = 0;
//
//	//rectAwl
//	_rcAwl = RectMake(position.x, position.y, 48, 96);
//	//rectLadder
//	//_rcLadder = RectMake(position.x, position.y, 48, 96);		//ÁÂÇ¥ ¾î¶±ÇÒ·¡
//	//rectRope
//	//_rcRope = RectMake(position.x, position.y, 48, 96);		//ÁÂÇ¥ ¾î¶±ÇÒ·¡
//													
//	_x = position.x;
//	_y = position.y;
//
//	return S_OK;
//}

HRESULT obstacle::init(const char * imageName, POINT position)	//img + rect
{
	_currentFrameX = _currentFrameY = 0;
	_count = 0;

	_imageName = IMAGEMANAGER->findImage(imageName);


	_x = position.x;
	_y = position.y;

	//_imageName->setX(_x);
	//_imageName->setY(_y);

	_rc = RectMake(position.x, position.y, _imageName->getFrameWidth(), _imageName->getFrameHeight());
	//_rcAwl = RectMake(position.x, position.y, 48, 96);

	return S_OK;
}

void obstacle::release()
{
}

void obstacle::update()
{
	_count++;
	if (_count % 10 == 0)		//ÇÁ·¹ÀÓ ¼Óµµ Á¶Àý
	{
		if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
		_imageName->setFrameX(_currentFrameX);
		_currentFrameX++;

		_count = 0;
	}

	_rc = RectMake(_x, _y, _imageName->getFrameWidth(), _imageName->getFrameHeight());
	//_rcAwl = RectMake(_x, _y, 48, 96);

	//_imageName->setX(_x);
	//_imageName->setY(_y);

}

void obstacle::render()
{
	draw();
	
}

void obstacle::draw()
{
	_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

//void obstacle::playerPulleyMove(RECT rc)
//{
//	_rc = rc;
//
//	_rc.bottom -= 5;
//	_rc.top -= 5;
//
//	_rc = RectMakeCenter(_rc.left, _rc.top, _currentFrameX, _currentFrameY);
//}
