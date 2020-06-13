#include "InputHandler.h"
#include <iostream>

InputHandler* InputHandler::s_instance = nullptr;

InputHandler* InputHandler::GetInstance()
{
    if (s_instance == nullptr)
    {
        s_instance = new InputHandler();
    }

    return s_instance;
}

InputHandler::InputHandler()
{
    m_keyStates.resize(sf::Keyboard::KeyCount);
}

void InputHandler::SetEscapeSequence(sf::Keyboard::Key key)
{
    m_leaveKey = key;
}

InputHandler::~InputHandler()
{
    std::cout << "Input Handler gone...\n";
}

void InputHandler::EventHandler(sf::RenderWindow& window)
{
    while (window.pollEvent(m_event))
    {
        switch (m_event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            KeyDown(m_event.key.code);
            std::cout << "key: " << m_event.key.code << " pressed...\n";
            if (m_event.key.code == m_leaveKey)
            {
                window.close();
            }
            break;
        case sf::Event::KeyReleased:
            KeyUp(m_event.key.code);
            std::cout << "key: " << m_event.key.code << " released...\n";
            break;
        }
    }
}

bool InputHandler::GetKeyDown(sf::Keyboard::Key key)
{
    if (m_keyStates[key] == true)
        return true;

    return false;
}

void InputHandler::Quit()
{
    delete s_instance;
}

void InputHandler::KeyDown(sf::Keyboard::Key key)
{
    m_keyStates[key] = true;
}

void InputHandler::KeyUp(sf::Keyboard::Key key)
{
    m_keyStates[key] = false;
}
