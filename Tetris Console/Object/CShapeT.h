#pragma once
#include "CShape.h"
class CShapeT :
	public CShape
{
public:
	CShapeT();
	CShapeT(const CShapeT& t);
	~CShapeT();


public:
	virtual bool Init();
	virtual void Rotation(bool left);
	virtual CShapeT* Clone();
};

