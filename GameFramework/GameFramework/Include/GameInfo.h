#pragma once

// 이 헤더파일은 게임에서 공통으로 사용되는 내용들을 담아두고
// #include 해서 사용할 목적으로 제작되었다.
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
