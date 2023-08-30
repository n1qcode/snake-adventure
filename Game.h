//
// Created by n1qcode on 29.08.23.
//

#ifndef SNAKE_GAME_GAME_H
#define SNAKE_GAME_GAME_H

#include "Window.h"
#include "World.h"
#include "Snake.h"

class Game {
public:
  Game();

  ~Game();

  void Update();

  void Render();

  Window *GetWindow();

private:
  Window m_window;

  World m_world;
  Snake m_snake;

  sf::Clock m_clock;
  float m_elapsed;
};


#endif //SNAKE_GAME_GAME_H
