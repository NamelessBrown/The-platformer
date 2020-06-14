// SFML_template.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine/Engine.h"

int main()
{
    Engine::GetInstance()->Init(1280, 720, "The Platformer", false);
    Engine::GetInstance()->Run();
    Engine::GetInstance()->Quit();
}
