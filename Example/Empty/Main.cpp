#include <iostream>
#include <cstdlib>

#include <vector>
#include <memory>
#include <Windows.h>

#include "ToyEngine/Engine/Engine.h"


using namespace std;


int main()
{
    ToyEngine::Engine::Instance().StartUp();
    
    while (true)
    {
        ToyEngine::Engine::Instance().Step(0.1f);

        Sleep(100); // 0.1 second
    }

    system("pause");
    return 0;
}