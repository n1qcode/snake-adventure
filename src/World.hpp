#ifndef SNAKE_GAME_WORLD_HPP
#define SNAKE_GAME_WORLD_HPP

#include <SFML/Graphics.hpp>

#include "./Snake.hpp"

class World {
public:
  World(sf::Vector2u l_windSize);

  ~World();

  int GetBlockSize();

  void RespawnApple();

  void Update(Snake &l_player);

  void Render(sf::RenderWindow &l_window);

private:
  sf::Vector2u m_windowSize;
  sf::Vector2i m_item;
  int m_blockSize;

  sf::CircleShape m_appleShape;
  sf::RectangleShape m_bounds[4];
};

#endif  // SNAKE_GAME_WORLD_HPP
