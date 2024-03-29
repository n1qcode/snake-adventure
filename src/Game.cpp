#include "Game.hpp"

using namespace std;

Game::Game()
    : m_window("Snake Adventure", sf::Vector2u(800, 600)),
      m_snake(m_world.GetBlockSize()),
      m_world(sf::Vector2u(800, 600)) {}

Game::~Game() {}

void Game::HandleInput() {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
     m_snake.GetDirection() != Direction::Down) {
    m_snake.SetDirection(Direction::Up);
  } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
            m_snake.GetDirection() != Direction::Up) {
    m_snake.SetDirection(Direction::Down);
  } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            m_snake.GetDirection() != Direction::Right) {
    m_snake.SetDirection(Direction::Left);
  } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            m_snake.GetDirection() != Direction::Left) {
    m_snake.SetDirection(Direction::Right);
  }
}

void Game::Update() {
  m_window.Update();

  float timeStep = 1.0f / m_snake.GetSpeed();

  if(m_elapsed.asSeconds() >= timeStep) {
    m_snake.Tick();
    m_world.Update(m_snake);
    m_elapsed -= sf::seconds(timeStep);
    if(m_snake.HasLost()) {
      m_snake.Reset();
    }
  }
}

void Game::Render() {
  m_window.BeginDraw();

  m_world.Render(*m_window.GetRenderWindow());
  m_snake.Render(*m_window.GetRenderWindow());

  m_window.EndDraw();
}

Window *Game::GetWindow() {
  return &m_window;
}

void Game::RestartClock() {
  m_elapsed += m_clock.restart();
}