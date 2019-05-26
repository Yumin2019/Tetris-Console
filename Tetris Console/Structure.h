#pragma once


typedef struct _tagPosition
{
	int x, y;

	_tagPosition() :
		x(0),
		y(0)
	{}

	_tagPosition(int _x, int _y) :
		x(_x),
		y(_y)
	{}

	void operator=(const _tagPosition& tPos)
	{
		x = tPos.x;
		y = tPos.y;
	}

	_tagPosition operator+(const _tagPosition& tPos)
	{
		_tagPosition m_tPos;

		m_tPos.x = x + tPos.x;
		m_tPos.y = y + tPos.y;

		return m_tPos;
	}

	void operator+=(const _tagPosition& tPos)
	{
		x += tPos.x;
		y += tPos.y;
	}

	_tagPosition operator-(const _tagPosition& tPos)
	{
		_tagPosition m_tPos;

		m_tPos.x = x - tPos.x;
		m_tPos.y = y - tPos.y;

		return m_tPos;
	}

	void operator-=(const _tagPosition& tPos)
	{
		x -= tPos.x;
		y -= tPos.y;
	}
	
}POSITION, *PPOSITION;