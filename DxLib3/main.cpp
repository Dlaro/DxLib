#include "DxLib.h"
#include <math.h>
#include <time.h>
#include <array>
using namespace std;
const char TITLE[] = "01_Step1";
const int WinWidth = 800;
const int WinHeight = 600;
const double PI = 3.14159265358979323846;
struct qu
{	
	int	x, y, velx, vely;
	int size;
	int deadtime;
};

int* inputx,*inputy;
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{

	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetGraphMode(WinWidth, WinHeight, 32);
	SetWindowSizeExtendRate(1.0);

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	inputx = new int(400);
	inputy = new int(300);
	srand((unsigned int)time(NULL));
	qu qus[400]{ 400,300,0,0,5,60 };
	int pri = LoadGraph("particle.jpg");
	qu qu_1{ 0,0,1,1,60 };
	for (qu* q = begin(qus); q != end(qus); ++q) {
		int i = rand();
		q->x = *inputx;
		q->y = *inputy;
		q->velx = sin(i % 200 / 100.0 * PI) * 10.0;
		q->vely = cos(i % 200 / 100.0 * PI) * 10.0;
		q->deadtime = rand() % 120 + 60;

		q->size = rand() % 10 *10+50;
	}


	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		GetMousePoint(inputx, inputy);
		for (qu* q = begin(qus); q != end(qus); ++q) { 
			q->x += q->velx;
			q->y += q->vely;
			q->deadtime--;
			if ((q->deadtime) <= 0) {

				int i = rand();
				
				
				q->velx = sin(i % 20 / 10.0 * PI) * 10.0;
				q->vely = cos(i % 20 / 10.0 * PI) * 10.0;
				q->deadtime = rand() % 120 + 60;
				q->x = *inputx - q->size / 2;
				q->y = *inputy - q->size / 2;
				q->size = rand() % 10 * 10+80;
			}
			DrawExtendGraph(q->x, q->y, q->size + q->x, q->size + q->y, pri, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_MULA, 255);
			DrawCircle(q->size / 2 + q->x, q->size / 2 + q->y, q->size / 2, GetColor(0, 0, 255), 1);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			
		
		}
		
		
		

		ScreenFlip();
		Sleep(10);
	}

	DxLib_End();
	return 0;
}
