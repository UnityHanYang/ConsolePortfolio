#include "DxLib.h"
#include <time.h>

enum {
	DOWN_IDLE,
	DOWN_LWALK,
	DOWN_RWALK,
	IMG_TOTAL
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(false);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	int img[IMG_TOTAL];
	img[DOWN_IDLE] = LoadGraph("D_idle.png");
	img[DOWN_LWALK] = LoadGraph("D_lwalk.png");
	img[DOWN_RWALK] = LoadGraph("D_rwalk.png");

	int currentImg = DOWN_IDLE;
	int counter = 0;
	int x = 200, y = 200;
	int x1 = 0, y2 = 0;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			x -= 5;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))x += 5;
		if (CheckHitKey(KEY_INPUT_UP))y -= 3;
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			y += 2;
			counter++;
			if (counter % 28 == 0) {
				if (currentImg == DOWN_RWALK || currentImg == DOWN_IDLE) currentImg = DOWN_LWALK;
				else if (currentImg == DOWN_LWALK) currentImg = DOWN_RWALK;
			}
		}
		else
		{
			currentImg = DOWN_IDLE;
		}

		DrawRotaGraph(x, y, 0.3, 0, img[currentImg], 1);
	}

	DxLib_End();
	return 0;
}