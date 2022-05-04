#pragma once

// �� ��������� ���ӿ��� �������� ���Ǵ� ������� ��Ƶΰ�
// #include �ؼ� ����� �������� ���۵Ǿ���.
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>

#include "Vector2.h"

#define SAFE_DELETE(p) if(p)	{ delete p; p= nullptr; }
#define SAFE_DELETE_ARRAY(p) if(p)	{ delete[] p; p= nullptr; }

float RadianToDegree(float Radian);
float DegreeToRadian(float Degree);
