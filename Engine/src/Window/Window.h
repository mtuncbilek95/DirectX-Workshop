#pragma once

#include <Core/CoreAPI.h>
#include <Graphics/Renderer.h>

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
    
    HINSTANCE handleInstance;
    HWND windowHandle;
    Engine::Renderer* DirectXGraphics;
    static LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM wParam,LPARAM lParam);
    
    bool closeRequest;

};
