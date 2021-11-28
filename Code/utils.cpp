#include "stdafx.h"
#include "utils.h"

namespace SUNFL_UTIL
{
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return sqrtf(x * x + y * y);
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		//�ڽ����� ��ġ���� ������      �̺κ��� �ڽ���
		float angle = acosf(x / distance);

		//��ſ� Y�� ������ ������
		if (y2 > y1)
		{
			angle = PI2 - angle;
			if (angle >= PI2) angle -= PI2;
		}
		
		return angle;
	}
}