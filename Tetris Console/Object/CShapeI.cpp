#include "CShapeI.h"



CShapeI::CShapeI()
{
}

CShapeI::CShapeI(const CShapeI & I) :
	CShape(I)
{
}


CShapeI::~CShapeI()
{
}

bool CShapeI::Init()
{
	m_eShape = ST_I;


	m_tShape[0][2] = '0';
	m_tShape[1][2] = '0';
	m_tShape[2][2] = '0';
	m_tShape[3][2] = '0';

	return true;
}

void CShapeI::Rotation(bool left)
{
	if (left)
		m_iRotation += 90;
	else
		m_iRotation -= 90;

	if (m_iRotation == 360)
		m_iRotation = 0;
	else if (m_iRotation == -90)
		m_iRotation = 270;

	bool bRotation = false;

	switch (m_iRotation)
	{
	case 0:
	case 180:
		if (IsRotation(0, 2) &&
			IsRotation(1, 2) &&
			IsRotation(2, 2) &&
			IsRotation(3, 2))
		{
			memset(m_tShape, '1', 16);


			m_tShape[0][2] = '0';
			m_tShape[1][2] = '0';
			m_tShape[2][2] = '0';
			m_tShape[3][2] = '0';

			bRotation = true;
		}



		break;

	

	case 90:
	case 270:

		if (IsRotation(1, 0) &&
			IsRotation(1, 1) &&
			IsRotation(1, 2) &&
			IsRotation(1, 3))
		{
			memset(m_tShape, '1', 16);


			m_tShape[1][0] = '0';
			m_tShape[1][1] = '0';
			m_tShape[1][2] = '0';
			m_tShape[1][3] = '0';

			bRotation = true;
		}





		break;
	}


	if (!bRotation)
	{
		if (left)
			m_iRotation -= 90;
		else
			m_iRotation += 90;
	}

}

CShapeI * CShapeI::Clone()
{
	return new CShapeI(*this);
}
