#pragma once
#include "CShape.h"
class CShapeL :
	public CShape
{
public:
	CShapeL();
	~CShapeL();
	CShapeL(const CShapeL& l);



public:
	virtual bool Init();
	virtual void Rotation(bool left);
	virtual CShapeL* Clone();
};

