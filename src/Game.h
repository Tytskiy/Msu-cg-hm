#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <GLFW/glfw3.h>

#include "Render.h"
#include "GameObject.h"
#include "Player.h"
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

    static void clearGame();

    void restart() const;

    void newLevel();

    void loadLevel(int numLevel) const;

    void init();

    void processInput(float dt);

    void update(float dt);

    static void rendering();

    GameState state;
    InputState inputState;
    Size sizeOfWindow;
    int currLevel = 0;
};

#endif