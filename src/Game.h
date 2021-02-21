#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <GLFW/glfw3.h>

#include "Render.h"
#include "GameObject.h"
#include "Player.h"

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
    GameState state;
    InputState inputState;
    int width, height;

    Game(int width, int height);

    ~Game();

    void Close();

    void Init() const;

    void ProcessInput(float dt);

    void Update(float dt);

    void Render() const;
};

#endif