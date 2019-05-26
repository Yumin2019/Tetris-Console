#include "CStageManager.h"
#include "CCore.h"



DEFINITION_SINGLE(CStageManager);

CStageManager::CStageManager()
{
}


CStageManager::~CStageManager()
{
}

bool CStageManager::Init()
{
	for (int i = 0; i < STAGE_HEIGHT; ++i)
	{
		memset(m_tStage[i], '1', STAGE_WIDTH);
	}

	return true;
}

void CStageManager::Render()
{
	for (int i = 0; i < STAGE_HEIGHT; ++i)
	{
		for (int j = 0; j < STAGE_WIDTH; ++j)
		{
			if (m_tStage[i][j] == '0')
			{
				GET_SINGLE(CCore)->gotoxy(j, i);

				printf("□");
			}
		}
	}
}

void CStageManager::Update()
{
}

void CStageManager::StageBlock(int x, int y)
{
	if (x >= STAGE_WIDTH || y >= STAGE_HEIGHT + 1 || x < 0 || y < 0)
		return;

	m_tStage[y-1][x] = '0';



}

void CStageManager::CheckLine()
{

	int cnt = 0;

	for (int i = 0; i < STAGE_HEIGHT; ++i)
	{

		bool bBlockLine = true;

		for (int j = 0; j < STAGE_WIDTH; ++j)
		{
			if (m_tStage[i][j] == '1')
			{
				bBlockLine = false;

				break;
			}

		}

		if (bBlockLine)
		{
			// 블럭라인. 
			++cnt;

			// 라인 정리.
			memset(m_tStage[i], '1', STAGE_WIDTH);

			// i 행부터 시작하여, 1 까지.  아래로 한 칸씩 옮긴다.
			//  1 ~ i까지.

			for (int j = i; j >= 1; --j)
			{
				memcpy(m_tStage[j], m_tStage[j - 1], STAGE_WIDTH);
			}

			memset(m_tStage[0], '1', STAGE_WIDTH);

		}

		if (cnt != 0)
		{
			// 블럭 라인에 따른 점수.

			GET_SINGLE(CCore)->AddScore(20 * cnt);
		}
	}
}

bool CStageManager::IsBlock(int x, int y)
{
	if (x >= STAGE_WIDTH || y >= STAGE_HEIGHT || x < 0 || y < 0)
		return true;

	else if (m_tStage[y][x] == '0')
		return true;

	return false;

}


