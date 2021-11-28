#include "stdafx.h"
#include "object.h"
#include "player.h"

object::object()
{
}

object::~object()
{
}

HRESULT object::init()
{
	objectImageBundle();

	setObjectBox();
	setObjectDoor();
	setObjectFire();
	setObjectPulley();
	setObjectStone();
	setObjectAwl();
	setObjectLadder();

	

	return S_OK;
}

void object::release()
{
}

void object::update()
{
	//Box
	for (int i = 0; i < 3; i++)
	{
		_objectBox[0].rc = RectMake(_objectBox[0].x, _objectBox[0].y, 168, 84);
		_objectBox[1].rc = RectMake(_objectBox[1].x, _objectBox[1].y, 192, 48);
		_objectBox[2].rc = RectMake(_objectBox[2].x, _objectBox[2].y, 96, 144);
	}

	//Door
	for (int i = 0; i < 3; i++)
	{
		_objectDoor[0].rc = RectMake(_objectDoor[0].x, _objectDoor[0].y, 48, 144);
		_objectDoor[1].rc = RectMake(_objectDoor[1].x, _objectDoor[1].y, 48, 144);
		_objectDoor[2].rc = RectMake(_objectDoor[2].x, _objectDoor[2].y, 48, 144);
		//_objectDoor[2].rc = RectMake(_objectDoor[2].x, _objectDoor[2].y, 102, 144);
	}

	//fire
	for (int  i = 0; i < 4; i++)
	{
		_objectFire[0].rc = RectMake(_objectFire[0].x, _objectFire[0].y, 324, 93);	//1
		_objectFire[1].rc = RectMake(_objectFire[1].x, _objectFire[1].y, 864, 96);	//3
		_objectFire[2].rc = RectMake(_objectFire[2].x, _objectFire[2].y, 864, 96);	//3
		_objectFire[3].rc = RectMake(_objectFire[3].x, _objectFire[3].y, 864, 96);	//3
	}

	////pulley_upd
	//for (int i = 0; i < MAXPULLEY; i++)		//MAXPULLEY 5
	//{
	//	_objectPulley[0].rc = RectMake(_objectPulley[0].x, _objectPulley[0].y, 96, 48);
	//	_objectPulley[1].rc = RectMake(_objectPulley[1].x, _objectPulley[1].y, 96, 48);
	//	_objectPulley[2].rc = RectMake(_objectPulley[2].x, _objectPulley[2].y, 96, 48);
	//	_objectPulley[3].rc = RectMake(_objectPulley[3].x, _objectPulley[3].y, 96, 48);
	//	_objectPulley[4].rc = RectMake(_objectPulley[4].x, _objectPulley[4].y, 96, 48);
	//}


	//stone
	for (int i = 0; i < 2; i++)
	{
		_objectStone[0].rc = RectMake(_objectStone[0].x, _objectStone[0].y, 96, 96);
		_objectStone[1].rc = RectMake(_objectStone[1].x, _objectStone[1].y, 96, 96);
	}

	//awl
	for (int i = 0; i < MAXAWL; i++)	//MAXAWL 12
	{
		_objectAwl[0].rc = RectMake(_objectAwl[0].x, _objectAwl[0].y, 48, 96);
		_objectAwl[1].rc = RectMake(_objectAwl[1].x, _objectAwl[1].y, 48, 96);
		_objectAwl[2].rc = RectMake(_objectAwl[2].x, _objectAwl[2].y, 48, 96);
		_objectAwl[3].rc = RectMake(_objectAwl[3].x, _objectAwl[3].y, 48, 96);
		_objectAwl[4].rc = RectMake(_objectAwl[4].x, _objectAwl[4].y, 48, 96);
		_objectAwl[5].rc = RectMake(_objectAwl[5].x, _objectAwl[5].y, 48, 96);
		_objectAwl[6].rc = RectMake(_objectAwl[6].x, _objectAwl[6].y, 48, 96);
		_objectAwl[7].rc = RectMake(_objectAwl[7].x, _objectAwl[7].y, 48, 96);
		_objectAwl[8].rc = RectMake(_objectAwl[8].x, _objectAwl[8].y, 48, 96);
		_objectAwl[9].rc = RectMake(_objectAwl[9].x, _objectAwl[9].y, 48, 96);
		_objectAwl[10].rc = RectMake(_objectAwl[10].x, _objectAwl[10].y, 48, 96);
		_objectAwl[11].rc = RectMake(_objectAwl[11].x, _objectAwl[11].y, 48, 96);
	}


	//ladder
	for (int i = 0; i < MAXLADDER; i++)	//MAXLADDER 8		//좌에서 우 순서
	{
		_objectLadder[0].rc = RectMake(_objectLadder[0].x, _objectLadder[0].y, 98, 96);
		_objectLadder[1].rc = RectMake(_objectLadder[1].x, _objectLadder[1].y, 98, 145);
		_objectLadder[2].rc = RectMake(_objectLadder[2].x, _objectLadder[2].y, 98, 288);
		_objectLadder[3].rc = RectMake(_objectLadder[3].x, _objectLadder[3].y, 98, 192);
		_objectLadder[4].rc = RectMake(_objectLadder[4].x, _objectLadder[4].y, 98, 145);
		_objectLadder[5].rc = RectMake(_objectLadder[5].x, _objectLadder[5].y, 98, 140);
		_objectLadder[6].rc = RectMake(_objectLadder[6].x, _objectLadder[6].y, 98, 336);
		_objectLadder[7].rc = RectMake(_objectLadder[7].x, _objectLadder[7].y, 98, 241);
	}

	//rope
}

void object::render()
{
	//Box
	for (int i = 0; i < 3; i++)
	{
		Rectangle(getMemDC(), _objectBox[0].rc);
		_objectBox[0].img->render(getMemDC(), _objectBox[0].x, _objectBox[0].y);

		Rectangle(getMemDC(), _objectBox[1].rc);
		_objectBox[1].img->render(getMemDC(), _objectBox[1].x, _objectBox[1].y);

		Rectangle(getMemDC(), _objectBox[2].rc);
		_objectBox[2].img->render(getMemDC(), _objectBox[2].x, _objectBox[2].y);
	}

	//Door
	for (int i = 0; i < 4; i++)
	{
		Rectangle(getMemDC(), _objectDoor[0].rc);	//LtoR	2시
		_objectDoor[0].img->render(getMemDC(), _objectDoor[0].x, _objectDoor[0].y);

		Rectangle(getMemDC(), _objectDoor[1].rc);	//RtoL	6시 중간
		_objectDoor[1].img->render(getMemDC(), _objectDoor[1].x, _objectDoor[1].y);

		Rectangle(getMemDC(), _objectDoor[2].rc);	//RtoL	5시
		_objectDoor[2].img->render(getMemDC(), _objectDoor[2].x, _objectDoor[2].y);

		//상호작용하면 그때 [0], [1], [2]를 [3]으로 바꿔주자
		//Rectangle(getMemDC(), _objectDoor[3].rc);
		//_objectDoor[3].img->render(getMemDC(), _objectDoor[3].x, _objectDoor[3].y);
	}

	//fire
	for (int i = 0; i < 4; i++)
	{
		Rectangle(getMemDC(), _objectFire[0].rc);	//Fire1
		_objectFire[0].img->render(getMemDC(), _objectFire[0].x, _objectFire[0].y);

		Rectangle(getMemDC(), _objectFire[1].rc);	//Fire3
		_objectFire[1].img->render(getMemDC(), _objectFire[1].x, _objectFire[1].y);

		Rectangle(getMemDC(), _objectFire[2].rc);	//Fire3
		_objectFire[2].img->render(getMemDC(), _objectFire[2].x, _objectFire[2].y);

		Rectangle(getMemDC(), _objectFire[3].rc);	//Fire3
		_objectFire[3].img->render(getMemDC(), _objectFire[3].x, _objectFire[3].y);
	}

	////pulley
	//for (int i = 0; i < MAXPULLEY; i++)		//MAXPULLEY 5
	//{
	//	Rectangle(getMemDC(), _objectPulley[0].rc);
	//	_objectPulley[0].img->render(getMemDC(), _objectPulley[0].x, _objectPulley[0].y);		//12시

	//	Rectangle(getMemDC(), _objectPulley[1].rc);
	//	_objectPulley[1].img->render(getMemDC(), _objectPulley[1].x, _objectPulley[1].y);		//drrL

	//	Rectangle(getMemDC(), _objectPulley[2].rc);
	//	_objectPulley[2].img->render(getMemDC(), _objectPulley[2].x, _objectPulley[2].y);		//drrR

	//	Rectangle(getMemDC(), _objectPulley[3].rc);
	//	_objectPulley[3].img->render(getMemDC(), _objectPulley[3].x, _objectPulley[3].y);		//3시

	//	Rectangle(getMemDC(), _objectPulley[4].rc);
	//	_objectPulley[4].img->render(getMemDC(), _objectPulley[4].x, _objectPulley[4].y);		//5시

	//}

	//stone
	for (int i = 0; i < 2; i++)
	{
		Rectangle(getMemDC(), _objectStone[0].rc);
		_objectStone[0].img->render(getMemDC(), _objectStone[0].x, _objectStone[0].y);
		
		Rectangle(getMemDC(), _objectStone[1].rc);
		_objectStone[1].img->render(getMemDC(), _objectStone[1].x, _objectStone[1].y);

	}

	//awl	//투명렉트니까 나중에 주석
	for (int i = 0; i < MAXAWL; i++)
	{	
		//img->render 필요없지
		Rectangle(getMemDC(), _objectAwl[0].rc);
		Rectangle(getMemDC(), _objectAwl[1].rc);
		Rectangle(getMemDC(), _objectAwl[2].rc);
		Rectangle(getMemDC(), _objectAwl[3].rc);
		Rectangle(getMemDC(), _objectAwl[4].rc);
		Rectangle(getMemDC(), _objectAwl[5].rc);
		Rectangle(getMemDC(), _objectAwl[6].rc);
		Rectangle(getMemDC(), _objectAwl[7].rc);
		Rectangle(getMemDC(), _objectAwl[8].rc);
		Rectangle(getMemDC(), _objectAwl[9].rc);
		Rectangle(getMemDC(), _objectAwl[10].rc);
		Rectangle(getMemDC(), _objectAwl[11].rc);
	}

	//ladder	//투명렉트니까 나중에 주석
	for (int i = 0; i < MAXLADDER; i++)		//MAXLADDER 8
	{
		//img->render 필요없지
		Rectangle(getMemDC(), _objectLadder[0].rc);
		Rectangle(getMemDC(), _objectLadder[1].rc);
		Rectangle(getMemDC(), _objectLadder[2].rc);
		Rectangle(getMemDC(), _objectLadder[3].rc);
		Rectangle(getMemDC(), _objectLadder[4].rc);
		Rectangle(getMemDC(), _objectLadder[5].rc);
		Rectangle(getMemDC(), _objectLadder[6].rc);
		Rectangle(getMemDC(), _objectLadder[7].rc);
	}

	//rope		//투명렉트니까 나중에 주석
}

void object::objectImageBundle()
{
	IMAGEMANAGER->addImage("objectBox1_4x2", "IMAGE/objectBOX4x2.bmp", 168, 84, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("objectBox2_4x1", "IMAGE/objectBOX4x1.bmp", 192, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("objectBox3_2x3", "IMAGE/objectBOX2x3.bmp", 96, 144, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("objectDoor1_LtoR", "IMAGE/objectDoorLtoR.bmp", 48, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("objectDoor2_Open", "IMAGE/objectDoorOpen.bmp", 102, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("objectDoor3_RtoL", "IMAGE/objectDoorRtoL.bmp", 48, 144, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Fire1", "IMAGE/objectFire1Frame.bmp", 324, 93, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Fire3", "IMAGE/objectFire3Frame.bmp", 864, 96, 1, 6, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("objectPulley", "IMAGE/objectPulley.bmp", 96, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("objectMovingStone", "IMAGE/objectMovingStone.bmp", 96, 96, true, RGB(255, 0, 255));
	//===================================================================================================


}

void object::setObjectBox()
{
	for (int i = 0; i < 3; i++)
	{
		_objectBox[0].img = IMAGEMANAGER->findImage("objectBox1_4x2");
		_objectBox[0].x = 921;
		_objectBox[0].y = 1159;

		_objectBox[1].img = IMAGEMANAGER->findImage("objectBox2_4x1");
		_objectBox[1].x = 2497;
		_objectBox[1].y = 430;

		_objectBox[2].img = IMAGEMANAGER->findImage("objectBox3_2x3");
		_objectBox[2].x = 2548;
		_objectBox[2].y = 1917;
	}
}

void object::setObjectDoor()
{

	for (int i = 0; i < 4; i++)
	{
		_objectDoor[0].img = IMAGEMANAGER->findImage("objectDoor1_LtoR");		//2시
		_objectDoor[0].x = 2976;
		_objectDoor[0].y = 669;

		_objectDoor[1].img = IMAGEMANAGER->findImage("objectDoor3_RtoL");		//6시 중간
		_objectDoor[1].x = 1967;
		_objectDoor[1].y = 1389;

		_objectDoor[2].img = IMAGEMANAGER->findImage("objectDoor3_RtoL");		//5시
		_objectDoor[2].x = 2928;
		_objectDoor[2].y = 1916;

		//3번째는 열린거
	}

}

void object::setObjectFire()
{
	for (int i = 0; i < 4; i++)
	{
		_objectFire[0].img = IMAGEMANAGER->findImage("Fire1");		
		_objectFire[0].x = 2782;
		_objectFire[0].y = 142;

		_objectFire[1].img = IMAGEMANAGER->findImage("Fire3");
		_objectFire[1].x = 2638;
		_objectFire[1].y = 1347;

		_objectFire[2].img = IMAGEMANAGER->findImage("Fire3");
		_objectFire[2].x = 2783;
		_objectFire[2].y = 1581;

		_objectFire[3].img = IMAGEMANAGER->findImage("Fire3");
		_objectFire[3].x = 2638;
		_objectFire[3].y = 1826;
	}
}

void object::setObjectPulley()
{
	for (int i = 0; i < MAXPULLEY; i++)
	{

		//_objectPulley[0].img = IMAGEMANAGER->findImage("objectPulley");		//12시
		//_objectPulley[0].x = 960;
		//_objectPulley[0].y = 236;

		//_objectPulley[1].img = IMAGEMANAGER->findImage("objectPulley");		//drrL
		//_objectPulley[1].x = 2016;
		//_objectPulley[1].y = 946;

		//_objectPulley[2].img = IMAGEMANAGER->findImage("objectPulley");		//drrR
		//_objectPulley[2].x = 2305;
		//_objectPulley[2].y = 946;

		//_objectPulley[3].img = IMAGEMANAGER->findImage("objectPulley");		//2시
		//_objectPulley[3].x = 3026;
		//_objectPulley[3].y = 813;

		//_objectPulley[4].img = IMAGEMANAGER->findImage("objectPulley");		//5시
		//_objectPulley[4].x = 2448;
		//_objectPulley[4].y = 2110;
	}
}

void object::setObjectStone()
{
	for (int i = 0; i < 2; i++)
	{
		_objectStone[0].img = IMAGEMANAGER->findImage("objectMovingStone");
		_objectStone[0].x = 1104;
		_objectStone[0].y = 1245;

		_objectStone[1].img = IMAGEMANAGER->findImage("objectMovingStone");
		_objectStone[1].x = 1775;
		_objectStone[1].y = 1005;
	}
}

void object::setObjectAwl()
{
	for (int i = 0; i < MAXAWL; i++)
	{
		_objectAwl[0].x = 1201;
		_objectAwl[0].y = 1629;

		_objectAwl[1].x = 1249;
		_objectAwl[1].y = 1629;

		_objectAwl[2].x = 1632;
		_objectAwl[2].y = 1629;

		_objectAwl[3].x = 1680;
		_objectAwl[3].y = 1677;

		_objectAwl[4].x = 1728;
		_objectAwl[4].y = 1725;

		_objectAwl[5].x = 1776;
		_objectAwl[5].y = 1773;

		_objectAwl[6].x = 1824;
		_objectAwl[6].y = 1821;

		_objectAwl[7].x = 1872;
		_objectAwl[7].y = 1917;

		_objectAwl[8].x = 1920;
		_objectAwl[8].y = 1917;

		_objectAwl[9].x = 1968;
		_objectAwl[9].y = 1917;

		_objectAwl[10].x = 2016;
		_objectAwl[10].y = 1917;

		_objectAwl[11].x = 2064;
		_objectAwl[11].y = 1917;
	}
}

void object::setObjectLadder()
{
	for (int i = 0; i < MAXLADDER; i++)		//MAXLADDER 8
	{
		_objectLadder[0].x = 816;
		_objectLadder[0].y = 669;

		_objectLadder[1].x = 1200;
		_objectLadder[1].y = 236;

		_objectLadder[2].x = 1295;
		_objectLadder[2].y = 380;

		_objectLadder[3].x = 1535;
		_objectLadder[3].y = 908;

		_objectLadder[4].x = 1679;
		_objectLadder[4].y = 236;

		_objectLadder[5].x = 2638;
		_objectLadder[5].y = 1100;

		_objectLadder[6].x = 2736;
		_objectLadder[6].y = 477;

		_objectLadder[7].x = 3022;
		_objectLadder[7].y = 236;
	}
}


void object::changeBOX()
{
}

void object::changeDoor()
{
}

void object::movePulley()
{
}

void object::moveStone()
{
}

void object::objectPlayerCollision()
{
	
}

