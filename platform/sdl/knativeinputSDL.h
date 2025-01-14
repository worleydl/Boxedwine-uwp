#ifndef __KNATIVEWINDOW_SDL_H__
#define __KNATIVEWINDOW_SDL_H__

#include "knativeinput.h"

typedef enum
{
    LEFT_STICK_UP = 0,
    LEFT_STICK_DOWN,
    LEFT_STICK_LEFT,
    LEFT_STICK_RIGHT,
    LEFT_TRIGGER,
    RIGHT_TRIGGER,
    TYPE_COUNT
} AxisStateType;


class KNativeInputSDL : public KNativeInput {
public:
    KNativeInputSDL(U32 cx, U32 cy, int scaleX, int scaleY);

    void setScreenSize(U32 cx, U32 cy) override;
    U32 screenWidth() override;
    U32 screenHeight() override;

    bool waitForEvent(U32 ms) override; // if return is true, then event is available
    bool processEvents() override; // if return is false, then shutdown    
    void processCustomEvents(std::function<bool(bool isKeyDown, int key, bool isF11)> onKey, std::function<bool(bool isButtonDown, int button, int x, int y)> onMouseButton, std::function<bool(int x, int y)> onMouseMove) override;

    void runOnUiThread(std::function<void()> callback) override;
    bool mouseMove(int x, int y, bool relative) override;
    bool mouseWheel(int amount, int x, int y) override;
    bool mouseButton(U32 down, U32 button, int x, int y) override;
    bool key(U32 sdlScanCode, U32 key, U32 down) override;  // the key code is specific to the back end

    bool getVirtualMouseDelta(int* x, int* y) override;
    bool getMousePos(int* x, int* y, bool allowWarp = true) override;
    void setMousePos(int x, int y) override;
    void tickVirtualMouse() override;
    U32 getInputModifiers() override;

    int xToScreen(int x);
    int xFromScreen(int x);
    int yToScreen(int y);
    int yFromScreen(int y);

    bool checkMousePos(int& x, int& y, bool allowWarp);

    U32 scaleX = 100;
    U32 scaleXOffset = 0;
    U32 scaleY = 100;
    U32 scaleYOffset = 0;    
    int lastX = 0;
    int lastY = 0;
    float virtualMouseDX = 0.0;
    float virtualMouseDY = 0.0;
    float virtualMouseX = 320.0f;
    float virtualMouseY = 240.0f;

    U32 width = 0;
    U32 height = 0;

    // maybe patch libuwp to work with u32
    int fullWidth = 0;
    int fullHeight = 0;

    bool handlSdlEvent(SDL_Event* e);
    void refreshControllers();
};

typedef std::shared_ptr<KNativeInputSDL> KNativeInputSDLPtr;

#endif