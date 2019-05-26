#include "CShapeT.h"



CShapeT::CShapeT()
{
}

CShapeT::CShapeT(const CShapeT & t) :
	CShape(t)
{
}


CShapeT::~CShapeT()
{
}

bool CShapeT::Init()
{
	m_eShape = ST_T;

	m_tShape[2][0] = '0';
	m_tShape[2][1] = '0';
	m_tShape[2][2] = '0';
	m_tShape[3][1] = '0';

	return true;
}

void CShapeT::Rotation(bool left)
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

		if (IsRotation(2, 0) &&
			IsRotation(2, 1) &&
			IsRotation(2, 2) &&
			IsRotation(3, 1))
		{
			memset(m_tShape, '1', 16);

			m_tShape[2][0] = '0';
			m_tShape[2][1] = '0';
			m_tShape[2][2] = '0';
			m_tShape[3][1] = '0';

			bRotation = true;
		}



		break;

	case 90:



		if (IsRotation(1, 1) &&
			IsRotation(2, 1) &&
			IsRotation(3, 1) &&
			IsRotation(2, 2))
		{
			memset(m_tShape, '1', 16);

			m_tShape[1][1] = '0';
			m_tShape[2][1] = '0';
			m_tShape[3][1] = '0';
			m_tShape[2][2] = '0';

			bRotation = true;
		}


		break;

	case 180:



		if (IsRotation(1, 1) &&
			IsRotation(2, 0) &&
			IsRotation(2, 1) &&
			IsRotation(2, 2))
		{
			memset(m_tShape, '1', 16);

			m_tShape[1][1] = '0';
			m_tShape[2][0] = '0';
			m_tShape[2][1] = '0';
			m_tShape[2][2] = '0';

			bRotation = true;
		}


		break;

	case 270:

		if (IsRotation(1, 1) &&
			IsRotation(2, 0) &&
			IsRotation(2, 1) &&
			IsRotation(3, 1))
		{
			memset(m_tShape, '1', 16);


			m_tShape[1][1] = '0';
			m_tShape[2][0] = '0';
			m_tShape[2][1] = '0';
			m_tShape[3][1] = '0';

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

CShapeT * CShapeT::Clone()
{
	return new CShapeT(*this);
}


