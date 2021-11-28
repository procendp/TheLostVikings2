#pragma once
#include "gameNode.h"
#include <vector>		//�����̳� ����

struct tagBullet
{
	image* bulletImage;		//�Ѿ� �̹���
	RECT rc;				//�Ѿ� ��Ʈ
	float x, y;				//�Ѿ� ��ǥ(�ǽð�)
	float angle;			//�Ѿ� ����
	float radius;			//�Ѿ� ������
	float speed;			//�Ѿ� ���ǵ�
	float fireX, fireY;		//�Ѿ� �߻�� ó�� ��ǥ(�߻�� ��ǥ)
	bool isFire;			//�߻��?
	int count;				//�Ѿ� ������ī��Ʈ��
};

class missile : public gameNode
{
private:
	vector <tagBullet>				_vBullet;
	vector <tagBullet>::iterator	_viBullet;

	float _range;	//��Ÿ� ��(?)

public:
	missile() {};
	~missile() {};

	HRESULT init(int bulletMax, float range);
	
	void release();
	void update();
	void render();

	//�Ѿ� �߻��Լ� (������ ��ǥ)
	void fire(float x, float y);
	//�Ѿ� �������ݽô�
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
