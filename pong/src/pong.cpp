
/*
# _____        ____   ___
#   |     \/   ____| |___|
#   |     |   |   \  |   |
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licensed under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include <tyra>
#include "pong.hpp"

namespace Tyra {

    /** Lets save pointer to engine class */
    Pong::Pong(Engine* t_engine) : engine(t_engine) {}

    Pong::~Pong() {
        engine->renderer.getTextureRepository().freeBySprite(rect1);
        engine->renderer.getTextureRepository().freeBySprite(rect2);
        engine->renderer.getTextureRepository().freeBySprite(ball);
    }

    void Pong::init() {

      loadSprite();
      loadTexture();

      Player1Y = 512.0F / 2.0F - PlayerHeight / 2.0F;
      Player2Y = 512.0F / 2.0F - PlayerHeight / 2.0F;

      BallX = 512.0F / 2.0 - BallWidth / 2.0F;
      BallY = 224.0F / 2.0 - BallHeight / 2.0F;

    }

    void Pong::loop() {
      auto& renderer = engine->renderer;

      renderer.beginFrame();

      if (engine->pad.getPressed().Cross) {
          HoldingCross = true;
      } else {
          HoldingCross = false;
      }

      if (engine->pad.getPressed().Triangle) {
          HoldingTriangle = true;
      } else {
          HoldingTriangle = false;
      }

      if (engine->pad.getPressed().DpadUp) {
          HoldingUp = true;
      } else {
          HoldingUp = false;
      }

      if (engine->pad.getPressed().DpadDown) {
          HoldingDown = true;
      } else {
          HoldingDown = false;
      }

      if (HoldingUp == true) {
        if (Player1Y >= 0.0F) {
          Player1Y -= Player1_Speed;
        }
      }
      if (HoldingDown == true) {
        if (Player1Y + PlayerHeight <= 448.0F) {
          Player1Y += Player1_Speed;
        }
      }

      if (HoldingTriangle == true) {
        if (Player2Y >= 0.0F) {
          Player2Y -= Player2_Speed;
        }
      }
      if (HoldingCross == true) {
        if (Player2Y + PlayerHeight <= 448.0F) {
          Player2Y += Player2_Speed;
        }
      }

      BallX += BallSpeedX;
      BallY += BallSpeedY;

      if (BallX + BallWidth >= 448.0F + 48.0F && BallX <= 512.0F && BallY >= Player2Y && BallY <= Player2Y + PlayerHeight) {

        BallSpeed += 0.1F;
        BallSpeedX = -BallSpeed;
        BallSpeedY = -BallSpeed;
        Player1_Speed = BallSpeed;
        Player2_Speed = BallSpeed;

      }
      else if (BallX >= 0 && BallX <= PlayerWidth && BallY >= Player1Y && BallY <= Player1Y + PlayerHeight) {

        BallSpeed += 0.1F;
        BallSpeedX = BallSpeed;
        BallSpeedY = BallSpeed;
        Player1_Speed = BallSpeed;
        Player2_Speed = BallSpeed;

      }
      else if (BallX < 0) {
        BallX = 512.0F / 2.0 - BallWidth / 2.0F;
        BallY = 224.0F / 2.0 - BallHeight / 2.0F;
      }
      else if (BallX > 512.0F) {
        BallX = 512.0F / 2.0 - BallWidth / 2.0F;
        BallY = 224.0F / 2.0 - BallHeight / 2.0F;
      }

      if (BallY + BallHeight / 2 >= 448.0F) {
        BallSpeedY = -BallSpeedY;
      }
      else if (BallY <= 0.0F) {
        BallSpeedY = -BallSpeedY;
      }

      rect1.position = Vec2(0.0F, Player1Y);
      rect2.position = Vec2(512.0F, Player2Y);
      ball.position  = Vec2(BallX, BallY);

      renderer.renderer2D.render(rect1);
      renderer.renderer2D.render(rect2);
      renderer.renderer2D.render(ball);

      renderer.endFrame();
    }

    void Pong::loadSprite() {

      const auto& screenSettings = engine->renderer.core.getSettings();

      rect1.mode = SpriteMode::MODE_STRETCH;
      rect2.mode = SpriteMode::MODE_STRETCH;
      ball.mode  = SpriteMode::MODE_STRETCH;

      rect1.size = Vec2(PlayerWidth, PlayerHeight);
      rect1.position = Vec2(-PlayerWidth, Player1Y);

      rect2.size = Vec2(-PlayerWidth, PlayerHeight);
      rect2.position = Vec2(448.0F + PlayerWidth, Player2Y);

      ball.size = Vec2(BallWidth, BallHeight);
      ball.position = Vec2(512.0F / 2.0F - BallWidth / 2.0F, 448 / 2.0F - BallWidth / 2.0F);
   }

   void Pong::loadTexture() {

      auto& renderer = engine->renderer;

      auto& textureRepository = renderer.getTextureRepository();

      auto rect1path = FileUtils::fromCwd("rect1.png");
      auto* rect1_texture = textureRepository.add(rect1path);

      auto rect2path = FileUtils::fromCwd("rect2.png");
      auto* rect2_texture = textureRepository.add(rect2path);

      auto ballpath = FileUtils::fromCwd("ball.png");
      auto* ball_texture = textureRepository.add(ballpath);

      rect1_texture->addLink(rect1.id);
      rect2_texture->addLink(rect2.id);
      ball_texture->addLink(ball.id);
    }

}
