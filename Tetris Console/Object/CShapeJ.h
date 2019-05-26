#pragma once
#include "CShape.h"
class CShapeJ :
	public CShape
{
public:
	CShapeJ();
	CShapeJ(const CShapeJ& j);
	~CShapeJ();


public:
	virtual bool Init();
	virtual void Rotation(bool left);
	virtual CShapeJ* Clone();
};

