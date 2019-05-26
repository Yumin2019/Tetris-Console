#include "CShape.h"
#include "../Core/CCore.h"
#include "../Core/CInput.h"
#include "../Core/CStageManager.h"


CShape::CShape()
{
	memset(m_tShape, '1', 16);
	m_tPos = POSITION(7, 0);

	m_iRotation = 0;

}

CShape::CShape(const CShape & shape)
{
	m_tPos = shape.m_tPos;
	memcpy(m_tShape, shape.m_tShape, 16);

	m_iRotation = 0;

	m_eShape = shape.m_eShape;


}


CShape::~CShape()
{
}



bool CShape::Init()
{
	return false;
}

void CShape::Rotation(bool left)
{
}

bool CShape::IsRotation(int row, int col)
{
	// 해당 위치가 비었는지 검사하는 함수

	POSITION tArrPos = POSITION(1, 2);

	POSITION tOffset = POSITION(row, col) - tArrPos; // rc

	tOffset.x += m_tPos.y; // y
	tOffset.y += m_tPos.x; // x

	if (GET_SINGLE(CStageManager)->IsBlock(tOffset.y, tOffset.x))
	{
		return false;
	}

	return true;
}

SHAPE_TYPE CShape::GetShape() const
{
	return m_eShape;
}

POSITION CShape::GetPos() const
{
	return m_tPos;
}

void CShape::MoveRight()
{
	POSITION tArrPos = POSITION(1, 2); // r c

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_tShape[i][j] != '0')
				continue;


			POSITION tOffset = POSITION(i, j) - tArrPos; // rc

			tOffset.x += m_tPos.y; // y
			tOffset.y += m_tPos.x; // x

			if (GET_SINGLE(CStageManager)->IsBlock(tOffset.y + 1, tOffset.x))
			{
				return;
			}


		}
	}

	++m_tPos.x;
}

void CShape::MoveLeft()
{
	POSITION tArrPos = POSITION(1, 2); // r c

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_tShape[i][j] != '0')
				continue;


			POSITION tOffset = POSITION(i, j) - tArrPos; // rc

			tOffset.x += m_tPos.y; // y
			tOffset.y += m_tPos.x; // x

			if (GET_SINGLE(CStageManager)->IsBlock(tOffset.y - 1, tOffset.x)) // 왼쪽이 블럭이다.
			{
				return;
			}


		}
	}


	--m_tPos.x;
}

bool CShape::MoveDown()
{

	// 1. 바닥에 닿은 경우
	// 2. 다른 블럭의 위에 있게된 경우.
	

	POSITION tArrPos = POSITION(1, 2); // r c

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_tShape[i][j] != '0')
				continue;


				// 모든 블럭을 비교하여 바로 아래에 블럭이 있는지 계산.


			POSITION tOffset = POSITION(i, j) - tArrPos; // rc

			tOffset.x += m_tPos.y; // y
			tOffset.y += m_tPos.x; // x

			if (GET_SINGLE(CStageManager)->IsBlock(tOffset.y, tOffset.x + 1))
			{
				// 아래가 블럭이다.
				return true;
			}
			else if (tOffset.x + 1 >= STAGE_HEIGHT)
			{
				return true; // 바닥
			}


		}
	}





	++m_tPos.y;

	// 이동한 자리가 바닥과 닿았다면...
	// 너비를 고려하여...

	// 일단.

	return false;
}


void CShape::Update()
{

	if (KEYDOWN("MoveLeft"))
	{
		MoveLeft();
	}

	else if (KEYDOWN("MoveRight"))
	{
		MoveRight();
	}


	else if (KEYDOWN("RotationLeft"))
	{
		Rotation(true);

	}

	else if (KEYDOWN("RotationRight"))
	{
		Rotation(false);

	}


	Render();
}

void CShape::Render()
{
	/*
	출력을 StageManager에서 담당하고, stage에 직접적으로 값을 두는 것이 어떨까 ? 
	
	아니면, 출력을 하다가 바닥과 부딛힌 경우에 스테이지에 넣어버리는 것도 좋음.
	*/



	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{

			int x = m_tPos.x + j;
			int y = m_tPos.y - (1 - i);

			if (x < 0 || y < 0)
				continue;
		

			GET_SINGLE(CCore)->gotoxy(x - 2, y);

			if (m_tShape[i][j] == '0')
				printf("■");
		/*	else 
				printf("  ");*/
		}
	}
	
}

void CShape::NextShapeRender()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{


			int x = STAGE_WIDTH + 2 + j;
			int y = STAGE_HEIGHT - 5 + i;

			GET_SINGLE(CCore)->gotoxy(x, y);

			if (m_tShape[i][j] != '0')
				printf("  ");
			else
				printf("■");
		}
	}


}

bool CShape::IsBlock(int row, int col)
{

	if (row < 0 || row >= 4 || col < 0 || col >= 4)
		return false;

	if (m_tShape[row][col] == '0')
		return true;

	return false;
}

