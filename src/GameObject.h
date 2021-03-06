#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include <vector>
#include <string>
#include "config.h"
#include "primitive.h"
#include "Sprite.h"

class Game;

class GameObject {
public:
    explicit GameObject(const Sprite &spr, const Point &pos = {0, 0},
                        const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 0, bool trig = false,
                        bool isCollision = true);

    explicit GameObject(const std::string &path, const Point &pos = {0, 0},
                        const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 0, bool trig = false,
                        bool isCollision = true);

    explicit GameObject(const std::vector<std::string> &paths, const Point &pos = {0, 0},
                        const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 0, bool trig = false,
                        bool isCollision = true, float speedAnim = 0.2);

    GameObject(const GameObject &gm);

    static bool doCollision(const GameObject &one, const GameObject &two, int shift = 0);

    static bool doCollision(const GameObject &one, const GameObject &two, Directions &dir, int shift = 0);

    virtual bool triggered(Game &game);

    virtual void animation(Game &game);

    bool getTriggered() const;

    void setTriggered(bool trig);

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
    bool isCollision;
    bool isAnimation;
    bool deleted = false;
    float speedAnim = 0.2;
    int numSprites = 1;
    float time = 0;
    int currSprite = 0;
};

class Player : public GameObject {
public:
    explicit Player(const Point &pos = {0, 0}, const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 150,
                    bool trig = false, bool isCollision = false);

    void move(MovementDir dir, float dt);

    void animation(Game &game);

    int keys = 0;
    int health = 3;
    float time = 0;
    float wait = 1.5;
    bool isPain = false;
};

class DestructObject : public GameObject {
public:
    explicit DestructObject(const Point &pos = {0, 0}, const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 0,
                            bool trig = false, bool isCollision = true);


    bool triggered(Game &game) override;

    //void animation(Game &game) override;
};

class Portal : public GameObject {
public:
    explicit Portal(const Point &pos = {0, 0}, const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 0,
                    bool trig = false, bool isCollision = false);


    bool triggered(Game &game) override;

    //void animation(Game &game) override;

private:
    bool isOpen = true;
};

class Trap : public GameObject {
public:
    explicit Trap(const Point &pos = {0, 0}, const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 0,
                  bool trig = false, bool isCollision = false);

    bool triggered(Game &game) override;
    // void animation(Game &game) override;
};


class Door : public GameObject {
public:
    explicit Door(const Point &pos = {0, 0}, const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 0, bool trig = false,
                  bool isCollision = true);

    bool triggered(Game &game) override;

    void animation(Game &game) override;
};

class Spikes : public GameObject {
public:
    explicit Spikes(const Point &pos = {0, 0}, const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 0,
                    bool trig = false,
                    bool isCollision = true);

    bool triggered(Game &game) override;

    void animation(Game &game) override;
};

class Key : public GameObject {
public:
    explicit Key(const Point &pos = {0, 0}, const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 0,
                 bool trig = false,
                 bool isCollision = false);

    bool triggered(Game &game) override;

    void animation(Game &game) override;
};

#endif