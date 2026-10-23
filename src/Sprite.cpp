// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 30.09.2021.
//

#include "AeoGameFramework.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include "AlSpriteImpl.hpp"

FRSprite::FRSprite(char const* path) {
    if(not path) return;
    Load(path);
}

FRSprite::FRSprite(FRSprite&& other) noexcept
: sprite_impl(other.sprite_impl)
{
    other.sprite_impl = nullptr;
}

FRSprite::~FRSprite() {
    delete sprite_impl;
}

void FRSprite::Load(char const* path) {
    assert(path != nullptr && "Path to sprite is nullptr");
    sprite_impl = new ALSpriteImpl(path);
}

FRSprite::FRSprite(ALSpriteImpl* prev_sprite)
: sprite_impl(prev_sprite)
{}

void FRSprite::Draw(int x, int y) {
    sprite_impl->Draw(x, y);
}

FRSprite FRSprite::FlipHorizontal() {
    return FRSprite(sprite_impl->FlipHorizontal());
}

FRSize FRSprite::GetSizeWH() {
    return sprite_impl->GetSizeWH();
}

