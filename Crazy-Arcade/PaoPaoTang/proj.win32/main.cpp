#include "main.h"
#include "GameLogic.h"
#include "CCEGLView.h"
#include "BaseDef.h"
USING_NS_CC;

// uncomment below line, open debug console
// #define USE_WIN32_CONSOLE

void MY_LPFN_ACCELEROMETER_KEYHOOK( UINT message,WPARAM wParam, LPARAM lParam )
{
	GameLogic::sharedGameLogic().handleInput(ECT_NONE,EPS_NONE);
}
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
