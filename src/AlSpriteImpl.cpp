// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 04.10.2021.
//

#include "AlSpriteImpl.hpp"
#include "Internal.hpp"
#include <cmath>

ALSpriteImpl::ALSpriteImpl(char const* path) {
    texture = std::make_shared<sf::Texture>();
    texture->loadFromFile(path);
    sprite.setTexture(*texture);
}

ALSpriteImpl::ALSpriteImpl(sf::Texture const& in_texture) {
    texture = std::make_shared<sf::Texture>(in_texture);
    sprite.setTexture(*texture);
}

void ALSpriteImpl::Draw(int x, int y) {
    framework_data->render_texture.draw(sprite, sf::Transform().translate((float)x, (float)y));
}

void ALSpriteImpl::SetSize(int width, int height) {
    auto [x, y] = texture->getSize();
    if (x == 0 || y == 0) return;
    float sx = (float)width / (float)x;
    float sy = (float)height / (float)y;
    if (sprite.getScale().x < 0.f) {
        sprite.setScale(-sx, sy);
    } else {
        sprite.setScale(sx, sy);
    }
}

ALSpriteImpl* ALSpriteImpl::FlipHorizontal() {
    ALSpriteImpl* copy = new ALSpriteImpl(*this);
    sf::Vector2f curScale = copy->sprite.getScale();
    copy->sprite.setScale(-curScale.x, curScale.y);
    if (copy->sprite.getScale().x < 0.f) {
        copy->sprite.setOrigin((float)texture->getSize().x, 0.f);
    } else {
        copy->sprite.setOrigin(0.f, 0.f);
    }
    return copy;
}

FRSize ALSpriteImpl::GetSizeWH() {
    auto [x, y] = texture->getSize();
    sf::Vector2f scale = sprite.getScale();
    return { static_cast<int>(std::round(x * std::abs(scale.x))), static_cast<int>(std::round(y * std::abs(scale.y))) };
}
