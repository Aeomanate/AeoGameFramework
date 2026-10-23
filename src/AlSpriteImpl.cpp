// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 04.10.2021.
//

#include "AlSpriteImpl.hpp"
#include "Internal.hpp"

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

ALSpriteImpl* ALSpriteImpl::FlipHorizontal() {
    ALSpriteImpl* copy = new ALSpriteImpl(*this);
    copy->sprite.setScale(-1, 1);
    copy->sprite.setOrigin((float)copy->GetSizeWH().w, 0);
    return copy;
}

ALSize ALSpriteImpl::GetSizeWH() {
    auto [x, y] = texture->getSize();
    return { (int)x, (int)y };
}
