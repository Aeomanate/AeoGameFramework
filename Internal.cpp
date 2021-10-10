// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 04.10.2021.
//

#include "Internal.hpp"

std::unique_ptr<FrameworkData> framework_data;

FrameworkData::FrameworkData(
    ALSize scene_size,
    sf::VideoMode window_size,
    char const* window_name,
    bool is_fullscreen
)
: window(
    window_size,
    window_name,
    is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default
  )
{
    render_texture.create((unsigned)scene_size.w, (unsigned)scene_size.h);
    window_sprite.setTexture(render_texture.getTexture());
    
    auto [sw, sh] = window.getSize();
    auto [rw, rh] = render_texture.getSize();
    sf::Vector2f scale_factor = { float(sw)/float(rw), float(sh)/float(rh) };
    window_sprite.setScale(scale_factor);
    
    init_moment = Clock::now();
}