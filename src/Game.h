#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <GLFW/glfw3.h>

#include "Render.h"
#include "GameObject.h"
#include "Level.h"

static constexpr Pixel background = {200, 200, 200, 255};

enum GameState {
    GAME_ACTIVE, GAME_MENU, GAME_WIN
};

struct InputState {
    bool keys[1024]{};
    GLfloat lastX = 0, lastY = 0;
    bool firstMouse = true;
    bool captureMouse = true;
    bool capturedMouseJustNow = false;
};

class Game {
public:
    Game(int width, int height);

    ~Game();

    void clearGame();

    void restart();

    void newLevel();

    void loadLevel(int numLevel);

    static Directions
    staticCollision(const GameObject &gm, const bool *collisionMap, const Size &sizeOfMap, int len = 3);

    Directions dynamicCollision(const GameObject &gm);

    void init();

    void processInput(float dt);

    void update(float dt);

    void rendering() const;

    GameState state;
    InputState inputState;
    Size sizeOfWindow;
    int currLevel = 0;

    //std::list<GameObject *> *dynamicObjects;
    bool *collisionMap = nullptr;
    Render *render = nullptr;
    Player *player = nullptr;
    Level *level = nullptr;
    Point posOfLevel;
};

#endif