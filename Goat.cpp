#include "Goat.h"
#include "GeneralFunction.h"

Goat::Goat(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel) : Enemy(filePath, position, numFrame, speed, vel) {
    is_attacking = false;
    is_appear = false;
    num_attack = 0;
    time_wait = 3000;
    time_appear = 10000;
    time_start = SDL_GetTicks64();
}

Goat::~Goat() {
    clear_up();
}

void Goat::init_weapon(const int& x_pos) {
    Weapon* fire = new Weapon("image\\fire_sprite.png", Vector2D(x_pos, 0), 10, 80, Vector2D(0, 5), 10);
    weapon.push_back(fire);
}

void Goat::remove_weapon(const int& index) {
    if ( index < weapon.size() && weapon.size() > 0 ) {
        weapon.erase(weapon.begin() + index);
    }
}

void Goat::check_weapon() {
    for ( int i = 0; i < weapon.size(); ) {
        if ( weapon[i]->get_ypos() + weapon[i]->get_destRect().w >= GROUND_HEIGHT ) weapon[i]->set_is_move(false);
        if ( !weapon[i]->get_is_move() ) remove_weapon(i);
        else ++i;
    }
}

void Goat::attack(const int& x_pos) {
    if ( destRect.x >= SCREEN_WIDTH/2 - 100 && !is_attacking && num_attack < NUM_ATTACK ) {
        is_attacking = true;
        time_start = SDL_GetTicks64();
    }

    if ( num_attack == NUM_ATTACK ) {
        is_attacking = false;
    }

    if ( is_attacking ) {
        destRect.x = SCREEN_WIDTH/2 - 100;
        if ( SDL_GetTicks64() - time_start >= time_wait ) {
            if ( file_path != "image\\goat_attack.png" ) set_file_path("image\\goat_attack.png", 14);
            else if ( frame >= num_frame - 1 ) {
                play_sound_effect("music\\fire_ball.wav");
                init_weapon(x_pos);
                ++num_attack;
                set_file_path("image\\goat.png", 4);
                time_start = SDL_GetTicks64();
            }
        }
    }
}

void Goat::appear() {
    if ( destRect.x >= SCREEN_WIDTH + destRect.w ) {
        destRect.x = -destRect.w;
        is_appear = false;
        num_attack = 0;
        time_start = SDL_GetTicks64();
    }
    if ( SDL_GetTicks64() - time_start >= time_appear && !is_appear ) {
        is_appear = true;
    }
    if ( !is_appear && destRect.x >= -destRect.w ) {
        destRect.x = -destRect.w;
    }
}


void Goat::update() {
    Enemy::update();
    appear();
    check_weapon();
    for ( int i = 0; i < weapon.size(); ++i ) {
        weapon[i]->update();
    }
}

void Goat::draw() {
    Enemy::draw();
    for ( int i = 0; i < weapon.size(); ++i ) {
        weapon[i]->draw();
    }
}

void Goat::clear_up() {
    weapon.clear();
}
