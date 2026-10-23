//
// Created by Aeomanate on 04.10.2021.
//

#ifndef AEOGAMEFRAMEWORK_ALSPRITEIMPL_HPP
#define AEOGAMEFRAMEWORK_ALSPRITEIMPL_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "AeoGameFramework.hpp"

class ALSpriteImpl {
  public:
    explicit ALSpriteImpl(const char* path);
    
    explicit ALSpriteImpl(sf::Texture const& in_texture);
    
    void Draw(int x, int y);
    
    ALSpriteImpl* FlipHorizontal();
    
    ALSize GetSizeWH();
  
  private:
    ALSpriteImpl(ALSpriteImpl const& other) = default;
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
};



#endif // AEOGAMEFRAMEWORK_ALSPRITEIMPL_HPP
