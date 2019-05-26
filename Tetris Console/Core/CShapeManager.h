#pragma once

#include "../Game.h"

class CShapeManager
{
	DECLARE_SINGLE(CShapeManager);

private:
	unordered_map<SHAPE_TYPE, class CShape*> m_mapShape;

	class CShape* m_pCurShape;
	class CShape* m_pNextShape;

	class CShape* FindShape(SHAPE_TYPE eType);

public:
	POSITION GetPos() const;
	bool Init();
	void Update();
	void Render();
	void MoveDown();

	void SetShape();

	void Rotate(bool left);

	class CShape* CreateShape(SHAPE_TYPE eType);
	class CShape* CreateShape();

	void NextShape();
	void NextShapeRender();
};

