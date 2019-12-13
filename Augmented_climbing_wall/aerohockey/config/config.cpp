#include "config.hpp"

namespace Config
{
    // General
    float fps = 120.f;
    float screen_width = 800.f;
    float screen_height = 600.f;
    bool kinectControl = false;
    sf::Uint32 window_mode = sf::Style::None;

    // Game settings
    unsigned max_score = 5;
    float game_length = 180.f;
    float game_start_delay = 2.f;
    float result_demonstration_time = 5.f;

    // Colors
    sf::Color red = sf::Color(204, 0, 0);
    sf::Color green = sf::Color(0, 102, 0);
    sf::Color trace_color = sf::Color(243, 240, 240, 64);

    // Puck
    bool use_velocity_cap = true;
    float max_puck_velocity = 800.f;
    float initial_puck_velocity = 400.f;
    float puck_radius = screen_height / 20.f;
    int trace_capacity = 20;
    float trace_min_radius = 10.f;

    // Paddles
    extern float paddle_radius = screen_height / 20.f;

    // Collisions
    bool use_paddle_velocity = true;

    // Ready buttons
    sf::Vector2f left_ready_button_position = sf::Vector2f(screen_width / 4, screen_height / 2);
    sf::Vector2f left_ready_button_size = sf::Vector2f(screen_width / 10, screen_width / 10);
    sf::Vector2f right_ready_button_position = sf::Vector2f(screen_width * 3 / 4, screen_height / 2);
    sf::Vector2f right_ready_button_size = sf::Vector2f(screen_width / 10, screen_width / 10);

    // Scoreboard
    int font_size = 40;
    float timer_width = 120.f;
    float score_width = 60.f;
    float board_height = 60.f;

    // Resources
    std::string font_scoreboard_path = "/media/fonts/DIN.ttf";
    std::string sound_scored_path = "/media/sounds/scored.wav";
    std::string sound_hit_path = "/media/sounds/hit.wav";
    std::string sound_wall_path = "/media/sounds/wall.wav";
    std::string texture_background_path = "/media/textures/background.jpg";
    std::string texture_puck_path = "/media/textures/puck.png";
}