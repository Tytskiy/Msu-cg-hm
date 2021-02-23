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
    clearGame();
}

void Game::clearGame() {
    delete render;
    delete player;
    delete level;
}

void Game::init() {
    currLevel = 0;
    loadLevel(currLevel);
}

void Game::restart() const {
    clearGame();
    loadLevel(currLevel);
}

void Game::newLevel() {
    clearGame();
    currLevel += 1;
    loadLevel(currLevel);
}


void Game::loadLevel(int numLevel) const {
    level = new Level(levelPath[numLevel], {40, 8});
    render = new class Render(background, sizeOfWindow);
    Point posOfGame = {(sizeOfWindow.width - level->getSize().width) / 2,
                       (sizeOfWindow.height - level->getSize().height) / 2};
    render->addLayer(level->getStaticObjects(), posOfGame);
    auto tmp = Point{level->getPlayerPosition().x + posOfGame.x, level->getPlayerPosition().y + posOfGame.y};
    player = new Player("../resources/doomguy.png", tmp, {32, 32});
}

void Game::update(float dt) {
}

void Game::processInput(float dt) {
    if (state == GAME_ACTIVE) {
        if (inputState.keys[GLFW_KEY_W] and player->getPosition().y +
                                            player->getSize().height < sizeOfWindow.height - PADDING)
            player->move(MovementDir::DOWN, dt);
        else if (inputState.keys[GLFW_KEY_S] and player->getPosition().y > PADDING)
            player->move(MovementDir::UP, dt);
        if (inputState.keys[GLFW_KEY_A] and player->getPosition().x > PADDING)
            player->move(MovementDir::LEFT, dt);
        else if (inputState.keys[GLFW_KEY_D] and
                 player->getPosition().x + player->getSize().width < sizeOfWindow.width - PADDING)
            player->move(MovementDir::RIGHT, dt);
    }
}

void Game::rendering() {
    render->drawStatic();
    render->drawObject(*player);
    auto w = render->getSizeOfRender().width;
    auto h = render->getSizeOfRender().height;

    //чтобы рисовалось сверху-вниз
    glRasterPos2f(-1, 1);
    glPixelZoom(1, -1);
    glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_BYTE, render->getDynamicImage()->getImage());
}