#include "CInput.h"

DEFINITION_SINGLE(CInput);

CInput::CInput() :
	m_pKey(NULL)
{
}


CInput::~CInput()
{
	Safe_Delete_Map(m_mapKey);
}

bool CInput::Init()
{
	// ÁÂ¿ì ÀÌµ¿

	AddKey(VK_LEFT, "MoveLeft");
	AddKey(VK_RIGHT, "MoveRight");

	// ½ºÇÇµå
	AddKey(VK_UP, "SpeedUp");
	AddKey(VK_DOWN, "SpeedDown");
	
	// È¸Àü
	AddKey('Z', "RotationLeft");
	AddKey('X', "RotationRight");

	// ¹Ù´Ú¿¡ ²È±â
	AddKey(VK_SPACE, "Space");

	// Escape
	AddKey(VK_ESCAPE, "ESC");

	// Pause
	AddKey('P', "Pause");

	return true;
}

void CInput::Update()
{
	unordered_map<string, PKEYINFO>::iterator iter;
	unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
	{
		int cnt = 0;
		int iSize = iter->second->vecKey.size();

		for (int i = 0; i < iSize; ++i)
		{
			if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000)
				++cnt;
		}

		if (cnt == iSize)
		{
			if (!iter->second->m_bDown && !iter->second->m_bPress)
			{
				iter->second->m_bDown = true;
			}
			else if (iter->second->m_bDown && !iter->second->m_bPress)
			{
				iter->second->m_bDown = false;
				iter->second->m_bPress = true;
			}
		}

		else
		{
			if (iter->second->m_bDown || iter->second->m_bPress)
			{
				iter->second->m_bDown = false;
				iter->second->m_bPress = false;
				iter->second->m_bUp = true;
			}

			else if (iter->second->m_bUp)
				iter->second->m_bUp = false;
		}
	}

}

PKEYINFO CInput::FindKey(const string & strTag)
{
	unordered_map<string, PKEYINFO>::iterator iter = m_mapKey.find(strTag);

	if (iter == m_mapKey.end())
		return NULL;

	return iter->second;
}

bool CInput::KeyDown(const string & strTag)
{
	PKEYINFO pKey = FindKey(strTag);

	return pKey->m_bDown;
}

bool CInput::KeyPress(const string & strTag)
{

	PKEYINFO pKey = FindKey(strTag);

	return pKey->m_bPress;
}

bool CInput::KeyUp(const string & strTag)
{

	PKEYINFO pKey = FindKey(strTag);

	return pKey->m_bUp;
}
