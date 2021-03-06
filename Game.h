#ifndef GAME_H
#define GAME_H

#include <vector>
#include "TextureManager.h"
#include "GeneralFunction.h"
#include "Map.h"
#include "Character.h"
#include "Goat.h"
#include "Dragon.h"
#include "EnemyManager.h"
#include "BonusManager.h"
#include "TextManager.h"

class Game {
private :
    SDL_Window* window;
    bool is_running;
    bool game_over;
    Uint64 time_start;
    int play_time;
    int high_score;
    bool pause_game;
    TextManager* pause_text = new TextManager("Press Space to continue game!", SDL_Color{255, 255, 255}, "font\\chary.ttf", 50, Vector2D(SCREEN_WIDTH/2 - 300, SCREEN_HEIGHT/2));

public :
    static SDL_Renderer* renderer;
    static SDL_Texture* background;
    static int score;
    static int check_point;
    static Map* map_game1;
    static Map* map_game2;
    static SDL_Event g_event;
    static Character* character;
    static Goat* goat;
    static Dragon* dragon;
    static EnemyManager* enemy_list;
    static BonusManager* bonus_list;

    static TextManager* show_score;
    static TextManager* show_time;
    static TextManager* show_hp;
    static TextureManager* heart;

    bool get_is_running() const {return is_running;}
    bool get_game_over() const {return game_over;}
    void set_is_running(const bool& running) {is_running = running;}
    void set_game_over(const bool& over) {game_over = over;}


    void game_init();
    int make_menu();
    void make_high_score();
    void make_info_game();
    int make_play_again();
    void enemy_list_manager();
    void setup_game();
    void handle_event();
    void character_collision();
    void destroy_enemy();
    void take_bonus();
    void reset_game();
    void update_game();
    void render_game();
    void clean_game();
};

#endif // GAME_H

