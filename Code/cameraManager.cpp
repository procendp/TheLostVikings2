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
	//backDC와 frontDC크기 설정
	_backWidth = width;
	_backHeight = height;
	_frontWidth = WINSIZEX;
	_frontHeight = WINSIZEY;
	//화면 Rect 생성
	_screen = RectMake(0, 0, WINSIZEX, WINSIZEY);	//우리가 플레이하는 화면 크기와 같은 크기의 렉트 생성
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
	//플레이어 기준으로 화면(_screen)갱신
	//playground.cpp의 update()에서 계속 갱신해주면 됨
	//인수로 기준이 되는 객체의 x, y좌표를 받음(현재는 player의 x, y)
	float x = standardX;
	float y = standardY;

	//X축 (좌, 우)
	if (x - _frontWidth * ratioX < 0)
		x = 0;
	else if (x + _frontWidth * (1 - ratioX) > _backWidth)
		x = _backWidth - _frontWidth;
	else
		x -= _frontWidth * ratioX;
	//Y축 (상, 하)
	if (y - _frontHeight * ratioY < 0)
		y = 0;
	else if (y + _frontHeight * (1 - ratioY) > _backHeight)
		y = _backHeight - _frontHeight;
	else
		y -= _frontHeight * ratioY;

	//갱신
	_screen = RectMake(x, y, _frontWidth, _frontHeight);

	if (zoom != 1.0) {
		x = standardX;
		y = standardY;
		float width = _frontWidth * zoom;
		float height = _frontHeight * zoom;

		//X축 (좌, 우)
		if (x - width * ratioX < 0)
			x = 0;
		else if (x + width * (1 - ratioX) > _backWidth)
			x = _backWidth - width;
		else
			x -= width * ratioX;
		//Y축 (상, 하)
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
	/********* 인수 설명 *********/ /*
	HDC frontDC: 복사를 받을 DC (실제로 우리가 보는 화면)
	int destX: 우리가 보는 화면에서 출력해줄 x좌표
	int destY: 우리가 보는 화면에서 출력해줄 y좌표
	HDC backDC: 복사해 올 DC (실제로 우리가 그리는 화면)
	bool map: true면 전체맵 출력, false면 안 출력
	bool mini: true면 미니맵 출력, false면 안 출력
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

	//DC영역간의 고속복사를 해줌(화면 깜빡임 방지)
	BitBlt(
		frontDC,				//복사받는 DC
		destX,					//복사받는 좌표(left)
		destY,					//복사받는 좌표(top)
		_frontWidth,			//복사되는 가로크기
		_frontHeight,			//복사되는 세로크기
		backDC,					//복사되는 DC
		_screen.left, _screen.top,	//복사되는 시작좌표(left, top)
		SRCCOPY);				//그대로 복사해오기(모드)

}