#include "CCore.h"
#include "CTimer.h"
#include "CInput.h"
#include "CShapeManager.h"
#include "CStageManager.h"

DEFINITION_SINGLE(CCore);

bool CCore::m_bSpace; 
float CCore::m_fMoveTime;
bool CCore::m_bGameLoop = true;

CCore::CCore()
{
	srand((unsigned int)time(0));
}


CCore::~CCore()
{
	DESTROY_SINGLE(CInput);
	DESTROY_SINGLE(CTimer);
	DESTROY_SINGLE(CShapeManager);
	DESTROY_SINGLE(CStageManager);

}

void CCore::Input()
{
	
}

void CCore::Logic()
{

	

	// �׸���
	GET_SINGLE(CShapeManager)->Update();

	StageRender();

	NextShapeRender();

	GET_SINGLE(CShapeManager)->NextShapeRender();

	GET_SINGLE(CStageManager)->Render();

	gotoxy(17, 8);

	POSITION tPos = GET_SINGLE(CShapeManager)->GetPos();

	printf("x : %d  y : %d ", tPos.x, tPos.y);




}

void CCore::StageRender()
{

	for (int i = 0; i < STAGE_HEIGHT + 1; ++i)
	{

		for (int j = 0; j < STAGE_WIDTH + 2; ++j)
		{
			gotoxy(j - 1, i);

			if (i == 0 && (j == 0 || j == STAGE_WIDTH + 1) || i == STAGE_HEIGHT)
				printf("��");

			else if (j == 0 || j == STAGE_WIDTH + 1)
				printf("��");

		}



	}

}

void CCore::NextShapeRender()
{
	gotoxy(STAGE_WIDTH + 1, STAGE_HEIGHT);
	printf("��������");

	for (int i = 0; i < 6; ++i)
	{
		gotoxy(STAGE_WIDTH + 7, STAGE_HEIGHT - 6 + i);
		printf("��");
	}

	gotoxy(STAGE_WIDTH + 1, STAGE_HEIGHT  - 7);
	printf("��������");


}

void CCore::InitRender()
{

	GET_SINGLE(CShapeManager)->NextShapeRender();

	AddScore(0);

	gotoxy(25, 14);

	printf("�̵� �� ��");

	gotoxy(25, 16);

	printf("���� �ӵ� �� ��");

	gotoxy(25, 18);

	printf("ȸ�� Z X");

	gotoxy(25, 20);

	printf("������ SPACE / �Ͻ����� P / ���� ESC");
}

void CCore::AddScore(int i)
{
	m_iScore += i;

	gotoxy(17, 10);

	printf("Score : %d", m_iScore);
}

bool CCore::Init()
{
	system("title Tetris");

	// Handle
	m_hHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Shape
	if (!GET_SINGLE(CShapeManager)->Init())
		return false;

	// Timer
	if (!GET_SINGLE(CTimer)->Init())
		return false;

	// Input
	if (!GET_SINGLE(CInput)->Init())
		return false;

	// Stage
	if (!GET_SINGLE(CStageManager)->Init())
		return false;

	// Cursor
	CONSOLE_CURSOR_INFO ConsoleCursor;

	ConsoleCursor.bVisible = NULL;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(m_hHandle, &ConsoleCursor);

	InitRender();


	return true;
}

void CCore::Run()
{

	bool m_bPause = false;

	while (true)
	{

		m_iScore = 0;
		m_fMoveTime = 0.f;

		float fSpeed = 0.3f;
		float m_fDeltaTime = 0.f;
		float fClear = 0.f;

		while (m_bGameLoop)
		{
			GET_SINGLE(CInput)->Update();
			GET_SINGLE(CTimer)->Update();
			m_fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

			if (m_bPause)
			{
				m_bPause = false;
				m_fDeltaTime = 0.f;
			}

			m_fMoveTime += m_fDeltaTime;
			fClear += m_fDeltaTime;

			if (m_fMoveTime >= fSpeed)
			{
				m_fMoveTime -= fSpeed;

				GET_SINGLE(CShapeManager)->MoveDown();

			}


			if (fClear >= 0.11f)
			{

				fClear -= 0.11f;

				// �����

				for (int i = 0; i < STAGE_HEIGHT; ++i)
				{
					gotoxy(0, i);

					printf("                             ");

				}

				// Cur�� ��ġ�� �ٽ� �׷��� ( �� ���� ��ó�� ���̵��� �Ѵ�.)
				GET_SINGLE(CStageManager)->Render();
				GET_SINGLE(CShapeManager)->Render();

			}



			// ������.
			if (KEYDOWN("Space") && !m_bSpace)
			{
				m_fMoveTime = (19 - GET_SINGLE(CShapeManager)->GetPos().y) * fSpeed;

				m_bSpace = true;
			}

			if (KEYDOWN("SpeedDown"))
			{
				fSpeed += 0.1f;
			}

			if (KEYDOWN("SpeedUp"))
			{
				fSpeed -= 0.1f;

				if (fSpeed <= 0.f)
					fSpeed = 0.1f;
			}



			Logic();



			if (KEYDOWN("ESC"))
			{
				m_bGameLoop = false;
			}

			if (KEYDOWN("Pause"))
			{
				while (_kbhit())
					_getch();

				while (1)
				{
					if (_kbhit())
					{
						m_bPause = true;
						break;
					}
				}
			}

		}

		// ���� ���� or �ٽ� �ϱ�

		system("cls");

		gotoxy(0, 0);
		cout << "1. �ٽ��ϱ�";

		gotoxy(0, 1);
		cout << "2. ������ ";

		gotoxy(0, 2);


		int i = 0;


		while (_kbhit())
			_getch();

		while(i == 0)
		{
			cin >> i;

			if (cin.fail())
			{
				cin.ignore(1024, '\n');
				cin.clear();

				i = 0;
			}
			else if (i <= 0 || i > 2)
				i = 0;
		}


		if (i == 2)
			break;

		m_bGameLoop = true;
		
		GET_SINGLE(CShapeManager)->SetShape();
		GET_SINGLE(CStageManager)->Init();

		m_bPause = false;

		InitRender();

	}
	
	system("pause");


	/*
	
	���� ��Ȳ. L ��� ȸ���� ������ ����, �ٸ� ������ ȸ���� �����ϰ� dd
	�Ʒ��ʿ����� �¿� üũ�� �ϰ� �ִµ� �̰Ϳ� ���Ͽ� y���� ���� �����ϰ� �����ϸ� �� �� ����. dd

	����, ��ǥ ������ / ���� �հ����� ���� dd 

	�߰��ϸ� ���� �� : ��������.  pass 

	���ӿ���... �̷� �� dd
	
	*/
}

void CCore::gotoxy(int x, int y)
{

	COORD Pos = { (x + 1 + 5)* 2, y + 5};

	SetConsoleCursorPosition(m_hHandle, Pos);

}
