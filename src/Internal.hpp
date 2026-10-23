//
// Created by Aeomanate on 04.10.2021.
//

#ifndef AEOGAMEFRAMEWORK_INTERNAL_HPP
#define AEOGAMEFRAMEWORK_INTERNAL_HPP

#include <SFML/Graphics.hpp>
#include "AeoGameFramework.hpp"

struct FrameworkData {
    FrameworkData(
        ALSize scene_size,
        sf::VideoMode window_size,
        const char* window_name,
        bool is_fullscreen
    );
    
    sf::RenderTexture render_texture;
    sf::Sprite window_sprite;
    sf::RenderWindow window;
    std::chrono::time_point<Clock> init_moment;
};
extern std::unique_ptr<FrameworkData> framework_data;


#endif // AEOGAMEFRAMEWORK_INTERNAL_HPP
