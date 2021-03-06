#include "cstdlib"

#include "Game.h"
#include "GameObject.h"

GameObject::GameObject(const Sprite &spr, const Point &pos, const Size &size, int vel, bool trig, bool isCollision) :
        position(pos), size(size), velocity(vel), isTriggered(trig), isCollision(isCollision), isAnimation(false) {
    sprite = new Sprite(spr);
}

GameObject::GameObject(const std::string &path, const Point &pos, const Size &size, int vel, bool trig,
                       bool isCollision) :
        position(pos), size(size), velocity(vel), isTriggered(trig), isCollision(isCollision), isAnimation(false) {
    sprite = new Sprite(path);
}

GameObject::GameObject(const std::vector<std::string> &paths, const Point &pos, const Size &size,
                       int vel, bool trig,
                       bool isCollision, float speedAnim) : position(pos), size(size), velocity(vel), isTriggered(trig),
                                                            isCollision(isCollision), isAnimation(true),
                                                            speedAnim(speedAnim) {
    time = ((float) rand() / (float) RAND_MAX) / speedAnim;
    numSprites = paths.size();
    sprite = new Sprite[paths.size()];
    for (int i = 0; i < paths.size(); i++) {
        sprite[i] = Sprite(paths[i]);
    }
}

GameObject::GameObject(const GameObject &gm) : position(gm.position), size(gm.size), velocity(gm.velocity),
                                               isTriggered(gm.isTriggered), isCollision(gm.isCollision) {
    sprite = new Sprite(*gm.sprite);
}

bool GameObject::doCollision(const GameObject &one, const GameObject &two, int shift) {

    bool right = (one.getPosition().x + one.getSize().width - shift >= two.getPosition().x);
    bool left = (one.getPosition().x + shift <= two.getPosition().x + two.getSize().width);
    bool bottom = (one.getPosition().y + one.getSize().height - shift >= two.getPosition().y);
    bool top = (one.getPosition().y + shift <= two.getPosition().y + two.getSize().height);

    return left && right && bottom && top;
}

bool GameObject::doCollision(const GameObject &one, const GameObject &two, Directions &dir, int shift) {
    //Бог меня покарает за такой shit code
    bool right = (one.getPosition().x + one.getSize().width >= two.getPosition().x);
    bool left = (one.getPosition().x <= two.getPosition().x + two.getSize().width);
    bool bottom = (one.getPosition().y + one.getSize().height >= two.getPosition().y);
    bool top = (one.getPosition().y <= two.getPosition().y + two.getSize().height);

    if (left && right && bottom && top) {
        auto tmp = GameObject(one);

        tmp.setPosition(tmp.getPosition() + Point{-shift, 0});
        dir.left = !doCollision(tmp, two, shift);

        tmp.setPosition(tmp.getPosition() - Point{-shift, 0} + Point{shift, 0});
        dir.right = !doCollision(tmp, two, shift);

        tmp.setPosition(tmp.getPosition() - Point{shift, 0} + Point{0, -shift});
        dir.top = !doCollision(tmp, two, shift);

        tmp.setPosition(tmp.getPosition() - Point{0, -shift} + Point{0, shift});
        dir.bottom = !doCollision(tmp, two, shift);
    }
    return left && right && bottom && top;
}

bool GameObject::getTriggered() const {
    return isTriggered;
}

void GameObject::setTriggered(bool trig) {
    isTriggered = trig;
}

Sprite &GameObject::getSprite() const {
    return sprite[currSprite];
}

Size GameObject::getSize() const {
    return size;
}

Point GameObject::getPosition() const {
    return position;
}

void GameObject::setPosition(const Point &pos) {
    position = pos;
}

GameObject::~GameObject() {
    if (isAnimation) {
        delete[] sprite;
    } else {
        delete sprite;
    }
    sprite = nullptr;
}

void GameObject::setStatic(bool set) {
    isCollision = set;
}

bool GameObject::getIsStatic() const {
    return isCollision;
}

bool GameObject::triggered(Game &game) {
};

void GameObject::animation(Game &game) {
    if ((game.globalTime - time) < speedAnim || !isAnimation) return;
    currSprite = (currSprite + 1) % numSprites;
    time = game.globalTime;
}


bool GameObject::isDeleted() const {
    return deleted;
}


Player::Player(const Point &pos, const Size &size, int vel, bool trig, bool isCollision) :
        GameObject(std::vector<std::string>{"../resources/doomguy_stay.png", "../resources/doomguy_left.png",
                                            "../resources/doomguy_right.png", "../resources/doomguy_pain.png"}, pos,
                   size, vel, trig, isCollision) {

}

void Player::animation(Game &game) {
    if (isPain) {
        currSprite = 3;
        return;
    }
    if (game.inputState.keys[GLFW_KEY_A])
        currSprite = 1;
    else if (game.inputState.keys[GLFW_KEY_D])
        currSprite = 2;
    else
        currSprite = 0;
}


void Player::move(MovementDir dir, float dt) {
    switch (dir) {
        case MovementDir::UP:
            position.y -= dt * velocity;
            break;
        case MovementDir::DOWN:
            position.y += dt * velocity;
            break;
        case MovementDir::LEFT:
            position.x -= dt * velocity;
            break;
        case MovementDir::RIGHT:
            position.x += dt * velocity;
            break;
        default:
            break;
    }
}


DestructObject::DestructObject(const Point &pos, const Size &size, int vel, bool trig, bool isCollision)
        : GameObject(std::vector<std::string>{"../resources/dw_1.png", "../resources/dw_2.png", "../resources/dw_3.png",
                                              "../resources/dw_4.png", "../resources/dw_5.png",
                                              "../resources/dw_6.png"}, pos, size, vel, trig, isCollision, 0.8) {

}

//void DestructObject::animation(Game &game) {
//    if ((game.globalTime - time) < 0.3) return;
//    currSprite = (currSprite + 1) % 6;
//    time = game.globalTime;
//}

bool DestructObject::triggered(Game &game) {
    if (!doCollision(*game.player, *this)) return false;
    if (game.inputState.keys[GLFW_KEY_E]) {
        isTriggered = true;
        if (isAnimation) {
            delete[] sprite;
        } else {
            delete sprite;
        }
        sprite = nullptr;
        deleted = true;
    }
    return false;
}

Portal::Portal(const Point &pos, const Size &size, int vel, bool trig, bool isCollision)
        : GameObject(
        std::vector<std::string>{"../resources/portal_1.png", "../resources/portal_2.png",
                                 "../resources/portal_3.png", "../resources/portal_4.png", "../resources/portal_5.png"},
        pos, size, vel, trig,
        isCollision, 0.8) {

}

//void Portal::animation(Game &game) {
//    if ((game.globalTime - time) < speedAnim || !isAnimation) return;
//    currSprite = (currSprite + 1) % numSprites;
//    time = game.globalTime;
//}


bool Portal::triggered(Game &game) {
    if (!doCollision(*game.player, *this) || game.player->keys < 1) return false;
    isTriggered = true;
    if (game.currLevel == 1) {
        game.state = GAME_WIN;
    } else {
        game.state = GAME_NEW_LEVEL;
    }
    return true;
}


Trap::Trap(const Point &pos, const Size &size, int vel, bool trig, bool isCollision) :
        GameObject(std::vector<std::string>{"../resources/lava_1.png", "../resources/lava_2.png",
                                            "../resources/lava_3.png", "../resources/lava_4.png"}, pos, size, vel, trig,
                   isCollision, 0.5) {
    time = 0;
}

bool Trap::triggered(Game &game) {
    if (!doCollision(*game.player, *this)) return false;
    isTriggered = true;
    if (!game.player->isPain) {
        game.player->health--;
        game.player->time = game.globalTime;
        game.player->isPain = true;
    }
    if (game.player->health == 0) {
        game.state = GAME_LOSE;
    }
    return true;
}

Door::Door(const Point &pos, const Size &size, int vel, bool trig, bool isCollision) :
        GameObject(std::vector<std::string>{"../resources/door_1.png", "../resources/door_2.png"}, pos, size, vel,
                   trig, isCollision) {
}


bool Door::triggered(Game &game) {
    if (!doCollision(*game.player, *this) || (game.globalTime - time) < 0.5) return false;
    if (game.inputState.keys[GLFW_KEY_E]) {
        isTriggered = true;
        currSprite = (currSprite + 1) % 2;
        isCollision = !isCollision;
        time = game.globalTime;
    }
    return false;
}

void Door::animation(Game &game) {
    return;
}

Spikes::Spikes(const Point &pos, const Size &size, int vel, bool trig, bool isCollision) :
        GameObject(std::vector<std::string>{"../resources/peaks_1.png", "../resources/peaks_2.png",
                                            "../resources/peaks_3.png", "../resources/peaks_4.png"}, pos, size, vel,
                   trig, isCollision, 1) {
}

bool Spikes::triggered(Game &game) {
    if (!doCollision(*game.player, *this) || currSprite >= 2) return false;
    isTriggered = true;
    if (!game.player->isPain) {
        game.player->health--;
        game.player->time = game.globalTime;
        game.player->isPain = true;
    }
    if (game.player->health == 0) {
        game.state = GAME_LOSE;
    }
    return true;
}

void Spikes::animation(Game &game) {
    GameObject::animation(game);
    if (currSprite >= 2) {
        isCollision = false;
    }
}

Key::Key(const Point &pos, const Size &size, int vel, bool trig, bool isCollision) : GameObject(
        std::vector<std::string>{"../resources/key_1.png", "../resources/key_2.png",
                                 "../resources/key_3.png", "../resources/key_4.png"}, pos, size, vel,
        trig, isCollision, 0.3) {

}

bool Key::triggered(Game &game) {
    if (!doCollision(*game.player, *this)) return false;
    isTriggered = true;
    game.player->keys++;

    if (isAnimation) {
        delete[] sprite;
    } else {
        delete sprite;
    }
    sprite = nullptr;
    deleted = true;
    return false;
}

void Key::animation(Game &game) {
    GameObject::animation(game);
}
