#include <GLFW/glfw3.h>

#include "Window.h"


int main(void)
{
    NWindow::Window window = NWindow::Window();
    window.run(window.win);
    delete(window.win);
}