#pragma once

#include "Core/CoreAPI.h"
#include "Graphics/Graphics.h"

class Window
{
public:
    Window(unsigned width, unsigned height);
    Window(const Window&) = delete;
    Window& operator =(const Window&) = delete;
    ~Window();

    void WindowLoop();

private:
    void ProcessMessages();
    void FrameLoop();
    
    HINSTANCE handleInstance;
    HWND windowHandle;
    Graphics* DirectXGraphics;
    static LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM wParam,LPARAM lParam);
    
    bool closeRequest;

    float test = 0;
};
