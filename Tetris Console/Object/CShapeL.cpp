#include "CShapeL.h"

CShapeL::CShapeL()
{
}

CShapeL::CShapeL(const CShapeL & l) :
	CShape(l)
{
}


CShapeL::~CShapeL()
{
}

bool CShapeL::Init()
{
	m_eShape = ST_L;

	m_tShape[1][1] = '0';
	m_tShape[1][2] = '0';
	m_tShape[1][3] = '0';
	m_tShape[2][1] = '0';

	return true;
}

void CShapeL::Rotation(bool left)
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

		if (IsRotation(1, 1) &&
			IsRotation(1, 2) &&
			IsRotation(1, 3) &&
			IsRotation(2, 1))
		{
			memset(m_tShape, '1', 16);


			m_tShape[1][1] = '0';
			m_tShape[1][2] = '0';
			m_tShape[1][3] = '0';
			m_tShape[2][1] = '0';

			bRotation = true;
		}



		break;

	case 90:



		if (IsRotation(0, 2) &&
			IsRotation(1, 2) &&
			IsRotation(2, 2) &&
			IsRotation(2, 3))
		{
			memset(m_tShape, '1', 16);


			m_tShape[0][2] = '0';
			m_tShape[1][2] = '0';
			m_tShape[2][2] = '0';
			m_tShape[2][3] = '0';

			bRotation = true;
		}
		

		break;

	case 180:

	

		if (IsRotation(0, 3) &&
			IsRotation(1, 1) &&
			IsRotation(1, 2) &&
			IsRotation(1, 3))
		{
			memset(m_tShape, '1', 16);


			m_tShape[0][3] = '0';
			m_tShape[1][1] = '0';
			m_tShape[1][2] = '0';
			m_tShape[1][3] = '0';

			bRotation = true;
		}


		break;

	case 270:

		if (IsRotation(0, 1) &&
			IsRotation(0, 2) &&
			IsRotation(1, 2) &&
			IsRotation(2, 2))
		{
			memset(m_tShape, '1', 16);


			m_tShape[0][1] = '0';
			m_tShape[0][2] = '0';
			m_tShape[1][2] = '0';
			m_tShape[2][2] = '0';

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

CShapeL * CShapeL::Clone()
{
	return new CShapeL(*this);
}


