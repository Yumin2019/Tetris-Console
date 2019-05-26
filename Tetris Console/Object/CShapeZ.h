#pragma once
#include "CShape.h"
class CShapeZ :
	public CShape
{
public:
	CShapeZ();
	CShapeZ(const CShapeZ& z);
	~CShapeZ();


public:
	virtual bool Init();
	virtual void Rotation(bool left);
	virtual CShapeZ* Clone();

};

