#pragma once

// �� ��������� ���ӿ��� �������� ���Ǵ� ������� ��Ƶΰ�
// #include �ؼ� ����� �������� ���۵Ǿ���.
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>

#define SAFE_DELETE(p) if(p)	{delete p; p= nullptr;}
#define SAFE_DELETE_ARRAY(p)	if(p)	{delete[] p; p= nullptr;}
