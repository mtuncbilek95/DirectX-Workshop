#include "Window/Window.h"

int main(int argc, char* argv[])
{
    Window* MainWindow = new Window(800,600);
    MainWindow->WindowLoop();
    delete MainWindow;
}
