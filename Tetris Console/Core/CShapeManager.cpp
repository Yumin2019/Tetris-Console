#include "CShapeManager.h"
#include "CCore.h"
#include "CStageManager.h"

// Shape
#include "../Object/CRectangle.h"
#include "../Object/CShapeI.h"
#include "../Object/CShapeL.h"
#include "../Object/CShapeT.h"
#include "../Object/CShapeZ.h"
#include "../Object/CShapeJ.h"
#include "../Object/CShapeS.h"

DEFINITION_SINGLE(CShapeManager);

CShapeManager::CShapeManager() : 
	m_pCurShape(NULL),
	m_pNextShape(NULL)
{
}


CShapeManager::~CShapeManager()
{
	Safe_Delete_Map(m_mapShape);

	SAFE_DELETE(m_pCurShape);

	SAFE_DELETE(m_pNextShape);
}

CShape * CShapeManager::FindShape(SHAPE_TYPE eType)
{
	unordered_map<SHAPE_TYPE, CShape*>::iterator iter = m_mapShape.find(eType);

	if (iter == m_mapShape.end())
		return NULL;

	return iter->second;
}

POSITION CShapeManager::GetPos() const
{
	return m_pCurShape->GetPos();
}

bool CShapeManager::Init()
{
	CShape* pShape = new CRectangle;

	if (!pShape->Init())
	{
		SAFE_DELETE(pShape);
		return false;
	}

	m_mapShape.insert(make_pair(ST_RECTANGLE, pShape));


	pShape = new CShapeL;

	if (!pShape->Init())
	{
		SAFE_DELETE(pShape);
		return false;
	}

	m_mapShape.insert(make_pair(ST_L, pShape));


	pShape = new CShapeI;

	if (!pShape->Init())
	{
		SAFE_DELETE(pShape);
		return false;
	}

	m_mapShape.insert(make_pair(ST_I, pShape));


	pShape = new CShapeT;

	if (!pShape->Init())
	{
		SAFE_DELETE(pShape);
		return false;
	}

	m_mapShape.insert(make_pair(ST_T, pShape));


	pShape = new CShapeZ;

	if (!pShape->Init())
	{
		SAFE_DELETE(pShape);
		return false;
	}

	m_mapShape.insert(make_pair(ST_Z, pShape));


	pShape = new CShapeS;

	if (!pShape->Init())
	{
		SAFE_DELETE(pShape);
		return false;
	}

	m_mapShape.insert(make_pair(ST_S, pShape));


	pShape = new CShapeJ;

	if (!pShape->Init())
	{
		SAFE_DELETE(pShape);
		return false;
	}

	m_mapShape.insert(make_pair(ST_J, pShape));


	SetShape();

	return true;
}

void CShapeManager::Update()
{
	m_pCurShape->Update();
}

void CShapeManager::Render()
{
	m_pCurShape->Render();
}

void CShapeManager::MoveDown()
{
	if (m_pCurShape->MoveDown())
	{
		// 현재 블럭의 위치를 기준으로 block

		POSITION tPos = m_pCurShape->GetPos();

		POSITION tArrPos = POSITION(1, 2); // r c

		
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (m_pCurShape->IsBlock(i, j))
				{
					// 이곳이 블럭이면.. 해당 위치를 스테이지에서 block으로 만든다.

					// 배열 내부에서 pivot 좌측 아래로부터 상대적인 좌표를 구해서 이것 + pos

					POSITION tOffset = POSITION(i, j) - tArrPos; // rc

					tOffset.x += tPos.y; // y
					tOffset.y += tPos.x; // x

					GET_SINGLE(CStageManager)->StageBlock(tOffset.y, tOffset.x + 1);


					if (tOffset.x <= 0)
					{
						CCore::m_bGameLoop = false;
						return;
					}


				}
			}
		}


		
		// 모든 블럭을 맵에다가 찍는 과정을 거치고, 라인을 검사
		GET_SINGLE(CStageManager)->CheckLine();

		// 교체.

		NextShape();

		// 새로운 블럭 장착.

		NextShapeRender();
		
		CCore::m_bSpace = false;
		CCore::m_fMoveTime = 0.f;

	}
}

void CShapeManager::SetShape()
{
	// 도형 셋팅

	SAFE_DELETE(m_pCurShape);
	SAFE_DELETE(m_pNextShape);

	m_pCurShape = CreateShape();
	m_pNextShape = CreateShape();
}

void CShapeManager::Rotate(bool left)
{
	m_pCurShape->Rotation(left);

}


CShape * CShapeManager::CreateShape(SHAPE_TYPE eType)
{
	CShape* pShape = FindShape(eType)->Clone();

	return pShape;
}

CShape * CShapeManager::CreateShape()
{
	SHAPE_TYPE eType = (SHAPE_TYPE)(rand() % ST_END);

	return CreateShape(eType);
}

void CShapeManager::NextShape()
{
	SAFE_DELETE(m_pCurShape);

	m_pCurShape = m_pNextShape;

	m_pNextShape = CreateShape();
}

void CShapeManager::NextShapeRender()
{
	m_pNextShape->NextShapeRender();
}

