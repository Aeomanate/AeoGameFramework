// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 30.09.2021.
//

#include <chrono>
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include "AeoGameFramework.hpp"
#include "AlSpriteImpl.hpp"
#include "Internal.hpp"

AeoGameFramework::AeoGameFramework(
    ALSize scene_size,
    ALSize screen_size,
    const char* title,
    bool is_fullscreen
) {
    framework_data = std::make_unique<FrameworkData>(
        scene_size,
        sf::VideoMode((unsigned)screen_size.w, (unsigned)screen_size.h),
        title,
        is_fullscreen
    );
}


void drawTestBackground() {
    static auto texture_generator = [] () -> sf::Texture const& {
        static sf::RenderTexture render_texture;
        auto [w, h] = getSceneSize();
        render_texture.create((unsigned)w, (unsigned)h);
        render_texture.clear();
        
        float size = 16;
        sf::RectangleShape rect({size, size});
        for(int x = 0; x < w; x += (int)size) {
            for(int y = 0; y < h; y += (int)size) {
                auto offset = sf::Transform().translate((float)x, (float)y);
                rect.setFillColor({
                    (uint8_t)(100 + (x ^ y) % 20 * (x * y) % 20),
                    (uint8_t)(180 + (y * x) % 20 * (y + x) % 20),
                    (uint8_t)(100 + (x ^ y) % 20 * (x - y) % 20)
                });
                render_texture.draw(rect, offset);
            }
        }
        render_texture.display();
        return render_texture.getTexture();
    };
    static ALSpriteImpl background(texture_generator());
    background.Draw(0, 0);
}

ALSize getSceneSize() {
    auto [x, y] = framework_data->render_texture.getSize();
    return {(int)x, (int)y};
}

void handleMoving(
    AeoGameFramework* user_framework,
    sf::Event::KeyEvent key,
    void (AeoGameFramework::*event)(ALKey)
) {
    switch(key.code) {
        case sf::Keyboard::Key::W: (user_framework->*event)(ALKey::UP);    break;
        case sf::Keyboard::Key::S: (user_framework->*event)(ALKey::DOWN);  break;
        case sf::Keyboard::Key::A: (user_framework->*event)(ALKey::LEFT);  break;
        case sf::Keyboard::Key::D: (user_framework->*event)(ALKey::RIGHT); break;
        default: break;
    }
}

void handleMousePress(
    AeoGameFramework* user_framework,
    sf::Event::MouseButtonEvent mouse,
    void (AeoGameFramework::*event)(ALMouseButton)
) {
    switch(mouse.button) {
        case sf::Mouse::Button::Left:
            (user_framework->*event)(ALMouseButton::LEFT);
            break;
        case sf::Mouse::Button::Right:
            (user_framework->*event)(ALMouseButton::RIGHT);
            break;
        case sf::Mouse::Button::Middle:
            (user_framework->*event)(ALMouseButton::MIDDLE);
            break;
        default:
            break;
    }
}
bool handleUserInput(AeoGameFramework* user_framework) {
    static sf::Vector2i prev_mose_pos = sf::Mouse::getPosition(framework_data->window);
    
    sf::Event e{};
    while(framework_data->window.pollEvent(e)) {
        switch(e.type) {
            case sf::Event::KeyPressed:
                handleMoving(user_framework, e.key, &AeoGameFramework::OnKeyPressed);
                break;
                
            case sf::Event::KeyReleased:
                if(e.key.code == sf::Keyboard::Key::Escape) {
                    return false;
                }
                
                handleMoving(user_framework, e.key, &AeoGameFramework::OnKeyReleased);
                break;
                
            case sf::Event::MouseButtonPressed:
                handleMousePress(user_framework, e.mouseButton, &AeoGameFramework::OnMouseButtonPressed);
                break;
            
            case sf::Event::MouseButtonReleased:
                handleMousePress(user_framework, e.mouseButton, &AeoGameFramework::OnMouseButtonReleased);
                break;
            
            case sf::Event::MouseMoved: {
                auto[x, y] = e.mouseMove;
                auto[px, py] = prev_mose_pos;
                user_framework->OnMouseMove(x, y, x - px, y - py);
                prev_mose_pos = { x, y };
                break;
            }
            
            case sf::Event::Closed:
                return false;
                
            default:
                break;
        }
    }
    
    return true;
}

int run(AeoGameFramework* user_framework) {
    bool is_work = true;
    
    user_framework->Init();
    Timer timer(1);
    while(is_work) {
        while(timer.IfExpiredThenStart());
        is_work = handleUserInput(user_framework);
        user_framework->Tick();
        framework_data->render_texture.display();
        framework_data->window.draw(framework_data->window_sprite);
        framework_data->window.display();
    }
    framework_data->window.close();
    return 0;
}
