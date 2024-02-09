#ifndef SNAKE_GAME_GAME_HPP
#define SNAKE_GAME_GAME_HPP

#include "Window.hpp"
#include "World.hpp"
#include "Snake.hpp"

class Game
{
public:
  Game();

  ~Game();

  void HandleInput();

  void Update();

  void Render();

  Window *GetWindow();

  void RestartClock();

private:
  Window m_window;

  World m_world;
  Snake m_snake;

  sf::Clock m_clock;
  sf::Time m_elapsed;
};

#endif // SNAKE_GAME_GAME_HPP
