
#include "GameEngine.h"

using namespace sf;

int main()
{
    
    std::unique_ptr <GameEngine> myGame = std::make_unique<GameEngine>();
        
    myGame->run();


    return 0;
}