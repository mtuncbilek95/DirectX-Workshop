#include "Window.h"

Window::Window(unsigned width, unsigned height) : handleInstance(GetModuleHandle(nullptr))
{
    const wchar_t* className = L"Window Class";

    WNDCLASSEX windowClass{};
    windowClass.cbSize = sizeof(windowClass);
    windowClass.lpszClassName = className;
    windowClass.lpszMenuName = nullptr;
    windowClass.hInstance = handleInstance;
    windowClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.lpfnWndProc = WindowProc;

    RegisterClassEx(&windowClass);

    DWORD windowStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

    RECT windowSize;
    windowSize.left = 250;
    windowSize.top = 250;
    windowSize.right = windowSize.left + width;
    windowSize.bottom = windowSize.top + height;

    AdjustWindowRect(&windowSize, windowStyle, false);

    windowHandle = CreateWindowEx(0, className, L"DX11 App", windowStyle, windowSize.left, windowSize.top, windowSize.right - windowSize.left,
                                  windowSize.bottom - windowSize.top, nullptr, nullptr, handleInstance, this);

    ShowWindow(windowHandle, SW_SHOW);

    DirectXGraphics = new Engine::Renderer();
}

Window::~Window()
{
    const wchar_t* className = L"Window Class";
    UnregisterClass(className, handleInstance);
    DestroyWindow(windowHandle);
}

void Window::WindowLoop()
{
    DirectXGraphics->Initialize(windowHandle);
    
    while (!closeRequest)
    {
        ProcessMessages();
        DirectXGraphics->RenderFrame();
    }
}

void Window::ProcessMessages()
{
    MSG msg{};

    while (PeekMessage(&msg, windowHandle, 0, 0,PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK Window::WindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            Window* WindowPtr = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
            SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)WindowPtr);
            break;
        }
    case WM_CLOSE:
        ((Window*)(GetWindowLongPtr(handle, GWLP_USERDATA)))->closeRequest = true;
        break;
    }

    return DefWindowProc(handle, message, wParam, lParam);
}
