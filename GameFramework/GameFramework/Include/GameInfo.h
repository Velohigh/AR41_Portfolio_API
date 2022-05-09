#pragma once

// 이 헤더파일은 게임에서 공통으로 사용되는 내용들을 담아두고
// #include 해서 사용할 목적으로 제작되었다.
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <typeinfo>
#include <string>
// 전역함수던 멤버함수건 상관없이 함수포인터를 등록해놓고
// 콜해주는 기능을 제공해준다.
#include <functional>	

#include "Vector2.h"
#include "SharedPtr.h"

#define SAFE_DELETE(p) if(p)	{ delete p; p= nullptr; }
#define SAFE_DELETE_ARRAY(p) if(p)	{ delete[] p; p= nullptr; }
#define SAFE_RELEASE(p) if(p)	{ p->Release(); p = nullptr; } // RC를 감소시키는용

float RadianToDegree(float Radian);
float DegreeToRadian(float Degree);
