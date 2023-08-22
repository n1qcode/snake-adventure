#include <SFML/Graphics.hpp>

#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

void trySFML() {
  const int WEIGHT = 500;
  const int HEIGHT = 500;

  sf::RenderWindow window(sf::VideoMode(WEIGHT, HEIGHT), "Game Of Luck");
//  window.setVerticalSyncEnabled(true);
//  window.setFramerateLimit(60);
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }
}

const int WIDTH = 40;
const int HEIGHT = 20;
const int MAX_SNAKE_SIZE = 100;
const int SLEEP_TIME_INTERVAL = 10;
const int SLEEP_TIME_LIMITATION = 80;

const string SCORE_MESSAGE = "SCORE: ";
const string LOSE_MESSAGE = "Game Over! You LOSE!";
const string EXIT_MESSAGE = "You are out of the game!";
const string WIN_MESSAGE = "Congratulation! You FINISHED this game!";

const char TAIL = '*';
const char BOARD_H = '-';
const char BOARD_V = '|';
const char FRUIT = '#';
const char SNAKE = '0';
const char SPACE = ' ';

bool gameOver;
bool gameEnd;
bool gameExit;

int sleepTime = 260;
int snakeX, snakeY, fruitX, fruitY, score;
int tailX[MAX_SNAKE_SIZE], tailY[MAX_SNAKE_SIZE];
int tailSize;

enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Sleep() {
  this_thread::sleep_for(chrono::milliseconds(sleepTime));
}

void fruitGenerator() {
  fruitX = rand() % WIDTH;
  fruitY = rand() % HEIGHT;
}

void Setup() {
  gameOver = false;
  dir = STOP;
  snakeX = WIDTH / 2;
  snakeY = HEIGHT / 2;
  score = 0;

  fruitGenerator();
}

void Draw() {
  system("clear");

  for (int i = 0; i <= WIDTH; i++)
    cout << BOARD_H;
  cout << endl;

  for (int i = 1; i <= HEIGHT; i++) {
    for (int j = 1; j <= WIDTH; j++) {
      if (j == 1 || j == WIDTH)
        cout << BOARD_V;
      if (i == snakeY && j == snakeX)
        cout << SNAKE;
      else if (i == fruitY && j == fruitX)
        cout << FRUIT;
      else {
        bool print = false;

        for (int k = 0; k < tailSize; k++) {
          if (tailX[k] == j && tailY[k] == i) {
            print = true;
            cout << TAIL;
          }
        }

        if (!print)
          cout << SPACE;
      }
    }
    cout << endl;
  }

  for (int i = 0; i <= WIDTH; i++)
    cout << BOARD_H;

  cout << endl;
  cout << SCORE_MESSAGE << score << endl;

  Sleep();
}

void Input() {
  if (_kbhit()) {
    char key = _getche();
    switch (key) {
      case 'a':
        if (dir != RIGHT)
          dir = LEFT;
        break;
      case 'd':
        if (dir != LEFT)
          dir = RIGHT;
        break;
      case 'w':
        if (dir != DOWN)
          dir = UP;
        break;
      case 's':
        if (dir != UP)
          dir = DOWN;
        break;
      case 'x':
        gameExit = true;
        system("clear");
        break;
      default:
        break;
    }
  }
}

void Logic() {
  if (tailSize == MAX_SNAKE_SIZE) {
    gameEnd = true;
    system("clear");
  }

  int prevX = tailX[0];
  int prevY = tailY[0];
  int prev2X, prev2Y;
  tailX[0] = snakeX;
  tailY[0] = snakeY;

  for (int i = 1; i < tailSize; i++) {
    prev2X = tailX[i];
    prev2Y = tailY[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }

  switch (dir) {
    case LEFT:
      snakeX--;
      break;
    case RIGHT:
      snakeX++;
      break;
    case UP:
      snakeY--;
      break;
    case DOWN:
      snakeY++;
      break;
    case STOP:
      break;
  }

  if (snakeX == WIDTH - 1)
    snakeX = 2;
  else if (snakeX == 0)
    snakeX = WIDTH - 1;
  else if (snakeY == HEIGHT + 1)
    snakeY = 1;
  else if (snakeY == 0)
    snakeY = HEIGHT + 1;

  if (snakeX == fruitX && snakeY == fruitY) {
    score += 10;
    tailSize++;
    fruitGenerator();
    if (sleepTime != SLEEP_TIME_LIMITATION)
      sleepTime -= SLEEP_TIME_INTERVAL;
  }

  for (int i = 1; i < tailSize; ++i) {
    if (tailX[i] == snakeX && tailY[i] == snakeY) {
      gameOver = true;
      system("clear");
    }
  }
}

int main() {
  trySFML();
  Setup();

  while (!gameOver && !gameEnd && !gameExit) {
    Draw();
    Input();
    Logic();
  }

  if (gameOver)
    cout << LOSE_MESSAGE << endl;
  if (gameEnd)
    cout << WIN_MESSAGE << endl;
  if (gameExit)
    cout << EXIT_MESSAGE << endl;
  cout << SCORE_MESSAGE << score << endl;

  return 0;
}
