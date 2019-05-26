#pragma once

#include "../Game.h"

class CStageManager
{
	DECLARE_SINGLE(CStageManager);

private:
	char m_tStage[STAGE_HEIGHT][STAGE_WIDTH];

public:
	bool Init();
	void Render();
	void Update();
	void StageBlock(int x, int y);
	void CheckLine();
	bool IsBlock(int x, int y);

};

