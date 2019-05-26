#pragma once

#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}

#define DECLARE_SINGLE(Type) \
private: \
static Type* m_pInst; \
public: \
static Type* GetInst() \
{\
if(!m_pInst) m_pInst = new Type; \
return m_pInst;\
}\
static void DestroyInst()\
{\
SAFE_DELETE(m_pInst); \
}\
Type();\
~Type();

#define GET_SINGLE(Type) Type::GetInst()
#define DESTROY_SINGLE(Type) Type::DestroyInst()
#define DEFINITION_SINGLE(Type) Type* Type::m_pInst = NULL

#define STAGE_WIDTH 15
#define STAGE_HEIGHT 20


#define KEYDOWN(Key) CInput::GetInst()->KeyDown(Key)
#define KEYPRESS(Key) CInput::GetInst()->KeyPress(Key)
#define KEYUP(Key) CInput::GetInst()->KeyUp(Key)



template<typename T>
void Safe_Delete_VecList(T& p)
{
	T::iterator iter;
	T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	p.clear();
}


template<typename T>
void Safe_Delete_Map(T& p)
{
	T::iterator iter;
	T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	p.clear();
}


