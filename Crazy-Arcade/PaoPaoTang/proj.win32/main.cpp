#include "main.h"
#include "GameLogic.h"
#include "CCEGLView.h"
#include "BaseDef.h"
USING_NS_CC;

// uncomment below line, open debug console
// #define USE_WIN32_CONSOLE

/****º¸≈Ãº‡øÿ≤‚ ‘*****/
void MY_LPFN_ACCELEROMETER_KEYHOOK(UINT message, WPARAM wParam, LPARAM lParam)
{
	EControlType eCtrlType = ECT_NUM;
	EPressState ePrsState = EPS_NONE;

	switch (message)
	{
	case WM_KEYDOWN:
	case WM_KEYUP:
	{
		if (WM_KEYDOWN == message)
			ePrsState = EPS_DOWN;
		else
			ePrsState = EPS_UP;
		switch (wParam)
		{
		case 'w':
		case 'W':
			eCtrlType = ECT_UP; break;
		case 's':
		case 'S':
			eCtrlType = ECT_DOWN; break;
		case 'a':
		case 'A':
			eCtrlType = ECT_LEFT; break;
		case 'd':
		case 'D':
			eCtrlType = ECT_RIGHT; break;
		case VK_SPACE:
			eCtrlType = ECT_PRESS; break;
		case VK_UP:
			eCtrlType = ECT_UP2; break;
		case VK_DOWN:
			eCtrlType = ECT_DOWN2; break;
		case VK_LEFT:
			eCtrlType = ECT_LEFT2; break;
		case VK_RIGHT:
			eCtrlType = ECT_RIGHT2; break;
		case VK_RETURN:
			eCtrlType = ECT_PRESS2; break;
			
		}
		break;
	}
	}




	((GameLogic&)CCApplication::sharedApplication()).handleInput(eCtrlType, ePrsState);
}
/****º¸≈Ãº‡øÿ≤‚ ‘*****/
int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
    GameLogic app;
    CCEGLView& eglView = CCEGLView::sharedOpenGLView();
    eglView.setViewName("Hello World");
    eglView.setFrameSize(FRAME_WIDTH, FRAME_HEIGHT);
    // set the design resolution screen size, if you want to use Design Resoulution scaled to current screen, please uncomment next line.
    // eglView.setDesignResolutionSize(480, 320);
	eglView.setAccelerometerKeyHook(MY_LPFN_ACCELEROMETER_KEYHOOK);
    int ret = CCApplication::sharedApplication().run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
