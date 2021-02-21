#include "Game.h"
#include "Level.h"


Level *levels;
Render *render;
Player *player;

Game::Game(int width, int height) : state(GAME_ACTIVE), width(width), height(height) {}

Game::~Game() {
    delete render;
    delete player;
}

void Game::Init() const {
    levels = new Level[2];
    levels[0] = Level("../resources/wall_24.png", {40, 40}, {0, 0});
    render = new class Render(levels[0]);
    player = new Player("../resources/doomguy.png", {32, 32}, {64, 64});
}

void Game::Close() {
    this->~Game();
}

void Game::Update(float dt) {}

void Game::ProcessInput(float dt) {
    if (state == GAME_ACTIVE) {
        if (inputState.keys[GLFW_KEY_W])
            player->Move(MovementDir::UP, dt);
        else if (inputState.keys[GLFW_KEY_S])
            player->Move(MovementDir::DOWN, dt);
        if (inputState.keys[GLFW_KEY_A])
            player->Move(MovementDir::LEFT, dt);
        else if (inputState.keys[GLFW_KEY_D])
            player->Move(MovementDir::RIGHT, dt);
    }
}

void Game::Render() const {
    player->Draw(*render);
    glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, render->DynamicImage()->GetImage());
}