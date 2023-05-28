#include"GUI.h"

int main()
{
    GUI Renderer;
    int status = Renderer.display();
    Renderer.endGame(status);
}
