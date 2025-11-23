#include "core/Game.hpp"
#include "platform/PCPlatform.hpp"

using namespace Engine;

int main()
{
    PCPlatform platform;

    Game game(platform);
    game.Run();

    return 0;
}