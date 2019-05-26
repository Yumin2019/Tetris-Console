#pragma once

#include "../Game.h"

class CTimer
{
	DECLARE_SINGLE(CTimer);

private:
	LARGE_INTEGER m_tTime;
	LARGE_INTEGER m_tSecond;

	float m_fDeltaTime;

public:
	float GetDeltaTime() const;
	bool Init();
	void Update();
};

