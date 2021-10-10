#include <iostream>
#include "AeoGameFramework.hpp"


class MyGame: public AeoGameFramework {
  public:
    MyGame(
        ALSize scene_size,
        ALSize screen_size,
        char const* title,
        bool fullscreen
    )
    : AeoGameFramework(scene_size, screen_size, title, fullscreen)
    {}
    
    // return : true - ok, false - failed, application will exit
    bool Init() override {
        std::cout << "Init()\n";
        return true;
    }
    
    void Close() override {
        std::cout << "Close()\n";
    }
    
    // return value: if true will exit the application
    bool Tick() override {
        drawTestBackground();
        return false;
    }
    
    // param: xrel, yrel: The vector of motion in the X/Y direction
    // param: x, y : coordinate, relative to window
    void OnMouseMove(int x, int y, int xrelative, int yrelative) override {
        std::cout << "XY(" << x << ", " << y << "), ";
        std::cout << "V(" << xrelative << ", " << yrelative << ")\n";
    }
    
    void OnMouseButtonPressed(ALMouseButton button) override {
        std::cout << "Button pressed: " << (int)button << "\n";
    }
    
    void OnMouseButtonReleased(ALMouseButton button) override {
        std::cout << "Button released: " << (int)button << "\n";
    }
    
    void OnKeyPressed(ALKey k) override {
        std::cout << "Key pressed: " << (int)k << "\n";
    }
    
    void OnKeyReleased(ALKey k) override {
        std::cout << "Key released: " << (int)k << "\n";
    }
};

int main() {
    return run(new MyGame({320, 240}, {800, 600}, "Test title", false));
}