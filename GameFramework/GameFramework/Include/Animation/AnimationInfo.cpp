
#include "AnimationInfo.h"
#include "../Resource/Animation/AnimationSequence.h"

CAnimationInfo::CAnimationInfo()	:
	m_Frame(0),
	m_Time(0.f),
	m_FrameTime(0.f),
	m_PlayTime(1.f),
	m_PlayScale(1.f),
	m_Loop(false),
	m_Reverse(false)
{
}

CAnimationInfo::~CAnimationInfo()
{
}
