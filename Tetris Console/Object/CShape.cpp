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
	// �ش� ��ġ�� ������� �˻��ϴ� �Լ�

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

			if (GET_SINGLE(CStageManager)->IsBlock(tOffset.y - 1, tOffset.x)) // ������ ���̴�.
			{
				return;
			}


		}
	}


	--m_tPos.x;
}

bool CShape::MoveDown()
{

	// 1. �ٴڿ� ���� ���
	// 2. �ٸ� ���� ���� �ְԵ� ���.
	

	POSITION tArrPos = POSITION(1, 2); // r c

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_tShape[i][j] != '0')
				continue;


				// ��� ���� ���Ͽ� �ٷ� �Ʒ��� ���� �ִ��� ���.


			POSITION tOffset = POSITION(i, j) - tArrPos; // rc

			tOffset.x += m_tPos.y; // y
			tOffset.y += m_tPos.x; // x

			if (GET_SINGLE(CStageManager)->IsBlock(tOffset.y, tOffset.x + 1))
			{
				// �Ʒ��� ���̴�.
				return true;
			}
			else if (tOffset.x + 1 >= STAGE_HEIGHT)
			{
				return true; // �ٴ�
			}


		}
	}





	++m_tPos.y;

	// �̵��� �ڸ��� �ٴڰ� ��Ҵٸ�...
	// �ʺ� ����Ͽ�...

	// �ϴ�.

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
	����� StageManager���� ����ϰ�, stage�� ���������� ���� �δ� ���� ��� ? 
	
	�ƴϸ�, ����� �ϴٰ� �ٴڰ� �ε��� ��쿡 ���������� �־������ �͵� ����.
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
				printf("��");
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
				printf("��");
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

