#pragma once
#include "CShape.h"
class CShapeI :
	public CShape
{
public:
	CShapeI();
	CShapeI(const CShapeI& I);
	~CShapeI();


public:
	virtual bool Init();
	virtual void Rotation(bool left);
	virtual CShapeI* Clone();
};

