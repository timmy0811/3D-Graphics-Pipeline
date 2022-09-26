#include "core/Game.h"

using namespace projection;

int main()
{
    // Init Game Engine
    Game game;

    // Loop
    while (game.getWindowIsOpen())
    {
        // Update
        game.update();

        // Render Image
        game.render();
    }

    return 0;
}