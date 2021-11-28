#pragma once
#include "gameNode.h"
#include <vector>		//컨테이너 쓰자

struct tagBullet
{
	image* bulletImage;		//총알 이미지
	RECT rc;				//총알 렉트
	float x, y;				//총알 좌표(실시간)
	float angle;			//총알 각도
	float radius;			//총알 반지름
	float speed;			//총알 스피드
	float fireX, fireY;		//총알 발사시 처음 좌표(발사된 좌표)
	bool isFire;			//발사됨?
	int count;				//총알 프레임카운트용
};

class missile : public gameNode
{
private:
	vector <tagBullet>				_vBullet;
	vector <tagBullet>::iterator	_viBullet;

	float _range;	//사거리 용(?)

public:
	missile() {};
	~missile() {};

	HRESULT init(int bulletMax, float range);
	
	void release();
	void update();
	void render();

	//총알 발사함수 (생성될 좌표)
	void fire(float x, float y);
	//총알 움직여줍시다
	void move();
};

class hyunMoo : public gameNode
{
private:
	vector <tagBullet>				_vBullet;
	vector <tagBullet>::iterator	_viBullet;

	float _range;
	int _bulletMax;

public:
	hyunMoo() {};
	~hyunMoo() {};

	HRESULT init(int bulletMax, float range);

	void release();
	void update();
	void render();

	void fire(float x, float y);
	
	void move();

};
