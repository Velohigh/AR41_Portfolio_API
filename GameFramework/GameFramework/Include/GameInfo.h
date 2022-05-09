#pragma once

// �� ��������� ���ӿ��� �������� ���Ǵ� ������� ��Ƶΰ�
// #include �ؼ� ����� �������� ���۵Ǿ���.
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <typeinfo>
#include <string>
// �����Լ��� ����Լ��� ������� �Լ������͸� ����س���
// �����ִ� ����� �������ش�.
#include <functional>	

#include "Vector2.h"
#include "SharedPtr.h"

#define SAFE_DELETE(p) if(p)	{ delete p; p= nullptr; }
#define SAFE_DELETE_ARRAY(p) if(p)	{ delete[] p; p= nullptr; }
#define SAFE_RELEASE(p) if(p)	{ p->Release(); p = nullptr; } // RC�� ���ҽ�Ű�¿�

float RadianToDegree(float Radian);
float DegreeToRadian(float Degree);
