#include "CRectangle.h"



CRectangle::CRectangle()
{
}

CRectangle::CRectangle(const CRectangle & rect) :
	CShape(rect)
{
}


CRectangle::~CRectangle()
{
}

bool CRectangle::Init()
{
	m_eShape = ST_RECTANGLE;


	m_tShape[1][1] = '0';
	m_tShape[1][2] = '0';
	m_tShape[2][1] = '0';
	m_tShape[2][2] = '0';
	
	return true;
}

void CRectangle::Rotation(bool left)
{
}

CRectangle * CRectangle::Clone()
{
	return new CRectangle(*this);
}

