// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 30.09.2021.
//

#include "AeoGameFramework.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include "AlSpriteImpl.hpp"

ALSprite::ALSprite(char const* path) {
    if(not path) return;
    Load(path);
}

ALSprite::ALSprite(ALSprite&& other) noexcept
: sprite_impl(other.sprite_impl)
{
    other.sprite_impl = nullptr;
}

ALSprite::~ALSprite() {
    delete sprite_impl;
}

void ALSprite::Load(char const* path) {
    assert(path != nullptr && "Path to sprite is nullptr");
    sprite_impl = new ALSpriteImpl(path);
}

ALSprite::ALSprite(ALSpriteImpl* prev_sprite)
: sprite_impl(prev_sprite)
{}

void ALSprite::Draw(int x, int y) {
    sprite_impl->Draw(x, y);
}

ALSprite ALSprite::FlipHorizontal() {
    return ALSprite(sprite_impl->FlipHorizontal());
}

ALSize ALSprite::GetSizeWH() {
    return sprite_impl->GetSizeWH();
}

