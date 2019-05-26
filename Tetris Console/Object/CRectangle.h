#pragma once
#include "CShape.h"
class CRectangle :
	public CShape
{
public:
	CRectangle();
	CRectangle(const CRectangle& rect);
	~CRectangle();


public:
	virtual bool Init();
	virtual void Rotation(bool left);
	virtual CRectangle* Clone();

};

