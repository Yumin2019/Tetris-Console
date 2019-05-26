#pragma once

#include "../Game.h"

class CCore
{
	DECLARE_SINGLE(CCore);

public: 
	static bool m_bSpace;
	static float m_fMoveTime;
	static bool m_bGameLoop;

private:
	HANDLE m_hHandle;
	int m_iScore;

private:
	void Input();
	void Logic();
	void StageRender();
	void NextShapeRender();
	void InitRender();

public:
	bool Init();
	void Run();
	void AddScore(int i);

	void gotoxy(int x, int y);

};

