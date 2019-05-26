#pragma once
#include "CShape.h"
class CShapeS :
	public CShape
{
public:
	CShapeS();
	CShapeS(const CShapeS& s);
	~CShapeS();


public:
	virtual bool Init();
	virtual void Rotation(bool left);
	virtual CShapeS* Clone();
};

