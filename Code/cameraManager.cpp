#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init(int width, int height)
{	
	//backDC�� frontDCũ�� ����
	_backWidth = width;
	_backHeight = height;
	_frontWidth = WINSIZEX;
	_frontHeight = WINSIZEY;
	//ȭ�� Rect ����
	_screen = RectMake(0, 0, WINSIZEX, WINSIZEY);	//�츮�� �÷����ϴ� ȭ�� ũ��� ���� ũ���� ��Ʈ ����
	_zoom = RectMake(0, 0, WINSIZEX, WINSIZEY);

	_count = 0;

	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::updateScreen(float standardX, float standardY,
	float ratioX, float ratioY, float zoom)
{
	//�÷��̾� �������� ȭ��(_screen)����
	//playground.cpp�� update()���� ��� �������ָ� ��
	//�μ��� ������ �Ǵ� ��ü�� x, y��ǥ�� ����(����� player�� x, y)
	float x = standardX;
	float y = standardY;

	//X�� (��, ��)
	if (x - _frontWidth * ratioX < 0)
		x = 0;
	else if (x + _frontWidth * (1 - ratioX) > _backWidth)
		x = _backWidth - _frontWidth;
	else
		x -= _frontWidth * ratioX;
	//Y�� (��, ��)
	if (y - _frontHeight * ratioY < 0)
		y = 0;
	else if (y + _frontHeight * (1 - ratioY) > _backHeight)
		y = _backHeight - _frontHeight;
	else
		y -= _frontHeight * ratioY;

	//����
	_screen = RectMake(x, y, _frontWidth, _frontHeight);

	if (zoom != 1.0) {
		x = standardX;
		y = standardY;
		float width = _frontWidth * zoom;
		float height = _frontHeight * zoom;

		//X�� (��, ��)
		if (x - width * ratioX < 0)
			x = 0;
		else if (x + width * (1 - ratioX) > _backWidth)
			x = _backWidth - width;
		else
			x -= width * ratioX;
		//Y�� (��, ��)
		if (y - height * ratioY < 0)
			y = 0;
		else if (y + height * (1 - ratioY) > _backHeight)
			y = _backHeight - height;
		else
			y -= height * ratioY;

		_zoom = RectMake(x, y, width, height);
	}
}

void cameraManager::vibrateScreen(float standardX, float standardY, float magnitude, float interval)
{
	_count += TIMEMANAGER->getElapsedTime();
	if (_count >= interval) {
		updateScreen(standardX + RND->getFromFloatTo(-magnitude, magnitude),
			standardY + RND->getFromFloatTo(-magnitude, magnitude));
		_count = 0;
	}
}

void cameraManager::render(HDC frontDC, int destX, int destY, HDC backDC,
	float zoom)
{
	/********* �μ� ���� *********/ /*
	HDC frontDC: ���縦 ���� DC (������ �츮�� ���� ȭ��)
	int destX: �츮�� ���� ȭ�鿡�� ������� x��ǥ
	int destY: �츮�� ���� ȭ�鿡�� ������� y��ǥ
	HDC backDC: ������ �� DC (������ �츮�� �׸��� ȭ��)
	bool map: true�� ��ü�� ���, false�� �� ���
	bool mini: true�� �̴ϸ� ���, false�� �� ���
	*/

	if (zoom != 1.0) {
		StretchBlt(
			backDC,
			_screen.left,
			_screen.top,
			_frontWidth,
			_frontHeight,
			backDC,
			_zoom.left,
			_zoom.top,
			_zoom.right - _zoom.left,
			_zoom.bottom - _zoom.top,
			SRCCOPY);
	}

	//DC�������� ��Ӻ��縦 ����(ȭ�� ������ ����)
	BitBlt(
		frontDC,				//����޴� DC
		destX,					//����޴� ��ǥ(left)
		destY,					//����޴� ��ǥ(top)
		_frontWidth,			//����Ǵ� ����ũ��
		_frontHeight,			//����Ǵ� ����ũ��
		backDC,					//����Ǵ� DC
		_screen.left, _screen.top,	//����Ǵ� ������ǥ(left, top)
		SRCCOPY);				//�״�� �����ؿ���(���)

}