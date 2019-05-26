#pragma once

#include "../Game.h"

typedef struct _tagInput
{
	string m_strTag;
	bool m_bDown;
	bool m_bPress;
	bool m_bUp;
	vector<DWORD> vecKey;

	_tagInput() :
		m_bDown(false),
		m_bPress(false),
		m_bUp(false)
	{}


}KEYINFO, *PKEYINFO;

class CInput
{
	DECLARE_SINGLE(CInput);

private:
	PKEYINFO m_pKey;
	unordered_map<string, PKEYINFO> m_mapKey;


public:
	bool Init();
	void Update();


	PKEYINFO FindKey(const string& strTag);
	bool KeyDown(const string& strTag);
	bool KeyPress(const string& strTag);
	bool KeyUp(const string& strTag);


private:
	template<typename T>
	bool AddKey(const T& data)
	{
		const char* m_Type = typeid(T).name();

		if (strcmp(m_Type, "char") == 0 || strcmp(m_Type, "int") == 0)
		{
			m_pKey->vecKey.push_back((DWORD)data);
		}
		else
		{
			m_pKey->m_strTag = data;

			m_mapKey.insert(make_pair(m_pKey->m_strTag, m_pKey));
		}


		return true;
	}

	template<typename T, typename ... Types>
	bool AddKey(const T& data, const Types& ...arg)
	{
		if (!m_pKey)
			m_pKey = new KEYINFO;

		const char* m_Type = typeid(T).name();

		if (strcmp(m_Type, "char") == 0 || strcmp(m_Type, "int") == 0)
		{
			m_pKey->vecKey.push_back((DWORD)data);
		}
		else
		{
			m_pKey->m_strTag = data;
			
			m_mapKey.insert(make_pair(m_pKey->m_strTag, m_pKey));
		}


		AddKey(arg...);

		if (m_pKey)
			m_pKey = NULL;

		return true;
	}
};

