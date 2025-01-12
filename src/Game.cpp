#include "Game.hpp"
#include "States/PauseState.hpp"
#include "States/MainMenuState.hpp"
#include "States/WinState.hpp"
#include "States/LostState.hpp"
#include "States/OptionState.hpp"
#include <sstream>

Game::Game() : mainWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close), currentState(nullptr)
{

    this->mainWindow.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - mainWindow.getSize().x / 2,
                                              sf::VideoMode::getDesktopMode().height / 2 - mainWindow.getSize().y / 2));
    this->mainWindow.requestFocus();

    for (size_t i = 0; i < NUMBER_OF_STATES; i++)
        statesList[i] = nullptr;
}

void Game::init()
{
    if (!font.loadFromFile(FONT_DIRECTORY + std::string("Xerox Sans Serif Narrow Bold.ttf")))
    {
        std::cout << "Bad font" << std::endl;
        exit(1);
    }
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);

    statesList[MAINMENU] = new MainMenuState();
    statesList[PAUSE] = new PauseState();
    statesList[WIN] = new WinState();
    statesList[LOST] = new LostState();
    statesList[OPTIONS] = new OptionsState();
    currentState = statesList[MAINMENU];
    run();
}

void Game::run()
{
    while (mainWindow.isOpen())
    {
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
            currentState = currentState->eventHandler(mainWindow, statesList, event);
        }
        currentState = currentState->update(mainWindow, statesList);

        mainWindow.clear();
        currentState->render(mainWindow);

        mainWindow.display();
    }
}