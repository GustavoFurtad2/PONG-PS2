/*
# _____        ____   ___
#   |     \/   ____| |___|
#   |     |   |   \  |   |
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licensed under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#pragma once

#include <tyra>

namespace Tyra {

class Pong: public Game {
 public:
  Pong(Engine* engine);
  ~Pong();

  void init();

  void loop();

 private:
  void loadTexture();
  void loadSprite();
  void Controls();
  void resetBall();

  Engine* engine;

  Sprite rect1;
  Sprite rect2;
  Sprite ball;

  float PlayerWidth = 16.0F;
  float PlayerHeight = 98.0F;

  float Player1Y;
  float Player2Y;
  float Player1_Speed = 5;
  float Player2_Speed = 5;

  float BallX;
  float BallY;

  float BallWidth  = 8.0F;
  float BallHeight = 8.0F;

  float BallSpeed =  5;
  float BallSpeedX = 5;
  float BallSpeedY = 5;

  bool HoldingUp = false;
  bool HoldingDown = false;

  bool HoldingTriangle = false;
  bool HoldingCross = false;
 };

}
