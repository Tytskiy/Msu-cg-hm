#include <iostream>
#include <list>
#include "Game.h"

static std::string levelPath[2] = {"../levels/level_1", "../levels/level_2"};

Game::Game(int width, int height) : state(GAME_LOAD), sizeOfWindow({width, height}), currLevel(0) {
}

Game::~Game() {
    clearGame();
}

void Game::clearGame() {
    delete render;
    delete player;
    delete level;
    delete[] collisionMap;
}

void Game::init() {
    currLevel = 0;
    loadLevel(currLevel);
}

void Game::restart() {
    clearGame();
    std::cout << "RESTART" << std::endl;
    loadLevel(currLevel);
}

void Game::newLevel() {
    currLevel += 1;
    if (currLevel < 2) {
        clearGame();
        std::cout << "NEW" << std::endl;
        loadLevel(currLevel);
    } else {
        std::cout << "WIN" << std::endl;
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void Game::loadLevel(int numLevel) {
    level = new Level(levelPath[numLevel], {40, 40});
    render = new Render(background, sizeOfWindow);

    posOfLevel = {(sizeOfWindow.width - level->getSize().width) / 2,
                  (sizeOfWindow.height - level->getSize().height) / 2};
    level->setLevelPosition(posOfLevel);
    render->addLayer(level->getStaticObjects(), posOfLevel);

    auto tmp = Point{level->getPlayerPosition().x + posOfLevel.x, level->getPlayerPosition().y + posOfLevel.y};
    player = new Player(tmp, {24, 24}, 130);

    collisionMap = new bool[sizeOfWindow.width * sizeOfWindow.height]{false};
    fillMatrix(collisionMap, sizeOfWindow.width, level->getCollisionMap(), level->getSize().width,
               level->getSize().height, posOfLevel.x, posOfLevel.y);

    for (auto &i:level->getDO()) {
        i->setPosition(i->getPosition() + posOfLevel);
    }
}

Directions Game::staticCollision(const GameObject &gm, const bool *collisionMap, const Size &sizeOfMap, int len) {
    auto gmPos = gm.getPosition();
    auto gmSize = gm.getSize();
    int TopLeft = sizeOfMap.width * gmPos.y + gmPos.x + len;
    int TopRight = sizeOfMap.width * gmPos.y + gmPos.x + gmSize.width - len;
    int BottomLeft = sizeOfMap.width * (gmPos.y + gmSize.height - len) + gmPos.x + len;
    int BottomRight = sizeOfMap.width * (gmPos.y + gmSize.height - len) + gmPos.x + gmSize.width - len;
    auto tmp = Directions{};
    if (collisionMap[TopLeft - len] or collisionMap[BottomLeft - len])
        tmp.left = false;
    if (collisionMap[TopRight + len] or collisionMap[BottomRight + len])
        tmp.right = false;
    if (collisionMap[TopLeft - len * sizeOfMap.width] or collisionMap[TopRight - len * sizeOfMap.width])
        tmp.top = false;
    if (collisionMap[BottomLeft + len * sizeOfMap.width] or collisionMap[BottomRight + len * sizeOfMap.width])
        tmp.bottom = false;
    return tmp;
}


Directions Game::dynamicCollision(const GameObject &gm) {
    Directions dir{};
    for (auto &c:level->getDO()) {
        Directions tmp{};
        GameObject::doCollision(gm, *c, tmp, 4);
        if (c->getIsStatic()) {
            dir.left &= tmp.left;
            dir.right &= tmp.right;
            dir.top &= tmp.top;
            dir.bottom &= tmp.bottom;
        }
    }
    return dir;
}


void Game::update(float dt) {
    globalTime += dt;
    if (state != GAME_ACTIVE) return;

    for (auto iter = level->getDO().begin(); iter != level->getDO().end(); iter++) {
        (*iter)->triggered(*this);
        if ((*iter)->isDeleted()) {
            iter = level->getDO().erase(iter);
        }
    }
    for (auto &c:level->getDO()) {
        c->animation(*this);
    }
    player->animation(*this);
}


void Game::processInput(float dt) {
    if (state != GAME_ACTIVE) return;

    auto staticDir = staticCollision(*player, collisionMap, sizeOfWindow, 4);
    auto dynamicDir = dynamicCollision(*player);

    if (inputState.keys[GLFW_KEY_W] and staticDir.top and dynamicDir.top)
        player->move(MovementDir::UP, dt);
    else if (inputState.keys[GLFW_KEY_S] and staticDir.bottom and dynamicDir.bottom)
        player->move(MovementDir::DOWN, dt);
    if (inputState.keys[GLFW_KEY_A] and staticDir.left and dynamicDir.left)
        player->move(MovementDir::LEFT, dt);
    else if (inputState.keys[GLFW_KEY_D] and staticDir.right and dynamicDir.right)
        player->move(MovementDir::RIGHT, dt);

}

void Game::rendering(float dt) {
    float loadSpeed = 1;
    static float time = 0;

    render->drawStatic();

    for (auto &c:level->getDO()) {
        render->drawObject(*c);
    }
    render->drawObject(*player);

    if (state == GAME_LOAD) {
        if (time <= loadSpeed) {
            render->dimming(time / loadSpeed);
            time += dt;
        } else {
            time = 0;
            state = GAME_ACTIVE;
        }
    }
    if (state == GAME_NEW_LEVEL || state == GAME_LOSE || state == GAME_WIN) {

        if (time <= loadSpeed) {
            if (state == GAME_LOSE) {
                render->blur((time / loadSpeed) * 9);
            } else {
                render->dimming(1 - (time / loadSpeed));
            }
            time += dt;
        } else {
            time = 0;
            if (state == GAME_LOSE) {
                restart();
            } else {
                newLevel();
            }
            state = GAME_LOAD;
            if (state == GAME_LOSE) {
                render->blur(5);
            } else {
                render->dimming(0);
            }
        }
    }
    if (state == GAME_NEW_LEVEL) {
        auto tmp = Sprite("../resources/level_up.png");
        Point pos = {(sizeOfWindow.width - tmp.getSize().width) / 2, (sizeOfWindow.height - tmp.getSize().height) / 2};
        render->drawSprite(tmp, pos);
    } else if (state == GAME_LOSE) {
        auto tmp = Sprite("../resources/you_lose.png");
        Point pos = {(sizeOfWindow.width - tmp.getSize().width) / 2, (sizeOfWindow.height - tmp.getSize().height) / 2};
        render->drawSprite(tmp, pos);
    } else if (state == GAME_WIN) {
        auto tmp = Sprite("../resources/end_game.png");
        Point pos = {(sizeOfWindow.width - tmp.getSize().width) / 2, (sizeOfWindow.height - tmp.getSize().height) / 2};
        render->drawSprite(tmp, pos);
    }
    auto w = render->getSizeOfRender().width;
    auto h = render->getSizeOfRender().height;

    glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_BYTE, render->getDynamicImage()->getImage());
}
