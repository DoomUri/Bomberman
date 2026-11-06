#include "Minion.h"

#define ENEMY_SIZE 16.f
#define ENEMY_MOVING_SPEED 0.5f
#define GRAVITY 0.05f        

#define STOP_MOVING_TIME 2000.f


// FUNCIONES DE OBJETO
void Minion::init(const glm::vec2& pos, const glm::ivec2& tileMapDispl, ShaderProgram& shaderProgram) {
    position = pos;
    tileDispl = tileMapDispl;
    inBossState = MinionState::INACTIVE;
    spritesheet.loadFromFile("images/Minion.png", TEXTURE_PIXEL_FORMAT_RGBA);
    spritesheet.setWrapS(GL_CLAMP_TO_EDGE);
    spritesheet.setWrapT(GL_CLAMP_TO_EDGE);
    spritesheet.setMinFilter(GL_NEAREST);
    spritesheet.setMagFilter(GL_NEAREST);
    sprite = Sprite::createSprite(glm::ivec2(ENEMY_SIZE, ENEMY_SIZE), glm::vec2(0.25f, 0.5f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(2);

    // Caminar
    sprite->setAnimationSpeed(0, 6);
    sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
    sprite->addKeyframe(0, glm::vec2(0.25f, 0.f));

    // Muerte
    sprite->setAnimationSpeed(1, 8);
    sprite->addKeyframe(1, glm::vec2(0.5, 0.f));

    sprite->changeAnimation(0);
    sprite->setPosition(glm::vec2(tileDispl.x + position.x, tileDispl.y + position.y));
}

// FUNCIONES DE JUEGO
void Minion::updateLogic(int deltaTime, TileMap* map, glm::vec2 player_pos) {

    int fallY = static_cast<int>(position.y);
    float old_Y = position.y;
    if (falling) {
        position.y += gravity;
        gravity += GRAVITY;
    }
    if (map->collisionMoveDown(glm::ivec2(position.x, position.y + ENEMY_MOVING_SPEED), glm::vec2(ENEMY_SIZE, ENEMY_SIZE), &fallY)) {
        position.y = old_Y;
        gravity = 0;
        falling = false;
    }
    else {
        falling = true;
    }
    if (movingRight) {
        position.x += ENEMY_MOVING_SPEED;
        if (map->collisionMoveRight(glm::ivec2(position), glm::vec2(ENEMY_SIZE, ENEMY_SIZE))) {
            position.x -= ENEMY_MOVING_SPEED;
            movingRight = false;
            pauseTimer = STOP_MOVING_TIME;
        }
    }
    else {
        position.x -= ENEMY_MOVING_SPEED;
        if (map->collisionMoveLeft(glm::ivec2(position), glm::vec2(ENEMY_SIZE, ENEMY_SIZE))) {
            position.x += ENEMY_MOVING_SPEED;
            movingRight = true;
            pauseTimer = STOP_MOVING_TIME;
        }
    }

    sprite->setFlipped(movingRight);
    sprite->setPosition(glm::vec2(tileDispl.x + position.x, tileDispl.y + position.y));
    sprite->update(deltaTime);
    if (state == EnemyState::DEAD) inBossState = MinionState::INACTIVE;
}

void Minion::render() {
    if (inBossState == MinionState::ACTIVE) {
        if (sprite && state != EnemyState::DEAD) {
            sprite->render();
        }
    }
}

void Minion::activate(glm::vec2 pos, bool direction) {
    position = pos;
    movingRight = direction;
    sprite->changeAnimation(0);
    state = EnemyState::ALIVE;
    inBossState = MinionState::ACTIVE;
}

void Minion::deactivate() {
    inBossState = MinionState::INACTIVE;
}

MinionState Minion::getState() { return inBossState; }