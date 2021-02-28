#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "config.h"
#include "primitive.h"
#include "utils.h"
#include "Sprite.h"

class Game;

class GameObject {
public:
    explicit GameObject(const Sprite &spr, const Point &pos = {0, 0},
                        const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 0, bool trig = false,
                        bool isStatic = true);

    explicit GameObject(const std::string &path, const Point &pos = {0, 0},
                        const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 0, bool trig = false,
                        bool isStatic = true);

    GameObject(const GameObject &gm);

    static bool doCollision(const GameObject &one, const GameObject &two, int shift = 0);

    static bool doCollision(const GameObject &one, const GameObject &two, Directions &dir, int shift = 0);

    virtual bool triggered(Game &game);

    bool getTriggered() const;

    bool setTriggered(bool trig);

    Sprite &getSprite() const;

    Size getSize() const;

    Point getPosition() const;

    void setPosition(const Point &pos);

    ~GameObject();

    void setStatic(bool set);

    bool getIsStatic() const;

    bool isDeleted() const;

protected:
    Sprite *sprite = nullptr;
    Size size;
    Point position;
    int velocity;
    bool isTriggered;
    bool isStatic;
    bool deleted = false;
};

class Player : public GameObject {
public:
    explicit Player(const Sprite &spr, const Point &pos = {0, 0},
                    const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 200, bool trig = false, bool isStatic = false);

    explicit Player(const std::string &path, const Point &pos = {0, 0},
                    const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 200, bool trig = false, bool isStatic = false);

    void move(MovementDir dir, float dt);
};

class DestructObject : public GameObject {
public:
    explicit DestructObject(const Sprite &spr, const Point &pos = {0, 0},
                            const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 200, bool trig = false,
                            bool isStatic = false);

    explicit DestructObject(const std::string &path, const Point &pos = {0, 0},
                            const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 200, bool trig = false,
                            bool isStatic = false);

    bool triggered(Game &game) override;
};

class FinishObject : public GameObject {
public:
    explicit FinishObject(const Sprite &spr, const Point &pos = {0, 0},
                          const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 200, bool trig = false,
                          bool isStatic = false);

    explicit FinishObject(const std::string &path, const Point &pos = {0, 0},
                          const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 200, bool trig = false,
                          bool isStatic = false);

    bool triggered(Game &game) override;
};

class Trap : public GameObject {
public:
    explicit Trap(const Sprite &spr, const Point &pos = {0, 0},
                  const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 200, bool trig = false, bool isStatic = false);

    explicit Trap(const std::string &path, const Point &pos = {0, 0},
                  const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 200, bool trig = false, bool isStatic = false);

    bool triggered(Game &game) override;
};


#endif