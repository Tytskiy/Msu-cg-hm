#include <iostream>

#include "config.h"
#include "Game.h"

static std::string levelPath[2] = {"../levels/level_1", "../levels/level_1"};
Render *render;
Player *player;
Level *level;

Game::Game(int width, int height) : state(GAME_ACTIVE), sizeOfWindow({width, height}), currLevel(0) {
}

Game::~Game() {
    ClearGame();
}

void Game::ClearGame() {
    delete render;
    delete player;
    delete level;
}

void Game::Init() {
    currLevel = 0;
    LoadLevel(currLevel);
}

void Game::Restart() const {
    ClearGame();
    LoadLevel(currLevel);
}

void Game::newLevel() {
    ClearGame();
    currLevel += 1;
    LoadLevel(currLevel);
}


void Game::LoadLevel(int numLevel) const {
    level = new Level(levelPath[numLevel], {40, 8});
    render = new class Render(background, sizeOfWindow);
    Point posOfGame = {(sizeOfWindow.width - level->GetSize().width) / 2,
                       (sizeOfWindow.height - level->GetSize().height) / 2};
    render->AddLayer(level->GetStaticObjects(), posOfGame);
    player = new Player("../resources/doomguy.png", {0, 0}, {32, 32});
}

void Game::Update(float dt) {
}

void Game::ProcessInput(float dt) {
    if (state == GAME_ACTIVE) {
        if (inputState.keys[GLFW_KEY_W] and player->GetPosition().y +
                                            player->GetSize().height < sizeOfWindow.height - PADDING)
            player->Move(MovementDir::UP, dt);
        else if (inputState.keys[GLFW_KEY_S] and player->GetPosition().y > PADDING)
            player->Move(MovementDir::DOWN, dt);
        if (inputState.keys[GLFW_KEY_A] and player->GetPosition().x > PADDING)
            player->Move(MovementDir::LEFT, dt);
        else if (inputState.keys[GLFW_KEY_D] and
                 player->GetPosition().x + player->GetSize().width < sizeOfWindow.width - PADDING)
            player->Move(MovementDir::RIGHT, dt);
    }
}

void Game::Render() {
    render->DrawStatic();
    render->DrawObject(*player);
    auto w = render->GetSizeOfRender().width;
    auto h = render->GetSizeOfRender().height;
    glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_BYTE, render->GetDynamicImage()->GetImage());
}