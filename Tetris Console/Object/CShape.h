#pragma once

#include "../Game.h"

class CShape
{
public:
	CShape();
	CShape(const CShape& shape);
	virtual ~CShape();

protected:
	POSITION m_tPos;
	char m_tShape[4][4];
	SHAPE_TYPE m_eShape;

	int m_iRotation;

public:

	virtual bool Init() = 0;
	virtual void Rotation(bool left) = 0;
	virtual CShape* Clone() = 0;

	bool IsRotation(int row, int col);


	SHAPE_TYPE GetShape() const;

	POSITION GetPos() const;

	void MoveRight(); 
	void MoveLeft();
	bool MoveDown();
	void Update();
	void Render();
	void NextShapeRender();
	bool IsBlock(int row, int col);


};

