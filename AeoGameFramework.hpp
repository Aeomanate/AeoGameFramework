//
// Created by Aeomanate on 30.09.2021.
//

#ifndef AEOGAMELIB_AEOGAMEFRAMEWORK_HPP
#define AEOGAMELIB_AEOGAMEFRAMEWORK_HPP

#include <chrono>
#include <memory>

#if defined(FRAMEWORK_PROJECT)
    #define API __declspec(dllexport)
#else
    #define API __declspec(dllimport)
#endif


struct ALSize {
    int w, h;
};

class ALSpriteImpl;
class API ALSprite {
  public:
    explicit ALSprite(const char* path = nullptr);
    ALSprite(ALSprite&& other) noexcept;
    ALSprite(ALSprite const&) = delete;
    
    ~ALSprite();
    void Load(const char* path);
    
    void Draw(int x, int y);
    ALSprite FlipHorizontal();
    ALSize GetSizeWH();
  
  private:
    explicit ALSprite(ALSpriteImpl*);
    ALSpriteImpl* sprite_impl = nullptr;
};

using Clock = std::chrono::steady_clock;
using TimeMs = long long int;

// Get the number of milliseconds since library initialization.
API TimeMs getTickCount();

class API Timer {
  public:
    explicit Timer(TimeMs interval = 0);
    
    [[nodiscard]] bool IsStarted() const;
    [[nodiscard]] bool IsExpired() const;
    bool IfExpiredThenStart();
    
    void SetInterval(TimeMs new_interval);
    void Start();
    void Stop();
    
    [[nodiscard]] TimeMs Interval() const;
    [[nodiscard]] TimeMs StartTime() const;
    [[nodiscard]] TimeMs Elapsed() const;
  
  private:
    TimeMs last_check = 0;
    TimeMs interval;
};

enum class ALKey {
    RIGHT,
    LEFT,
    DOWN,
    UP,
    NONE
};

enum class ALMouseButton {
    LEFT,
    MIDDLE,
    RIGHT,
    NONE
};

class API AeoGameFramework {
  public:
    AeoGameFramework(
        ALSize scene_size,
        ALSize screen_size,
        const char* title,
        bool is_fullscreen
    );
    
    // return : true - ok, false - failed, application will exit
    virtual bool Init() = 0;
    
    virtual void Close() = 0;
    
    // return value: if true will exit the application
    virtual bool Tick() = 0;
    
    // param: xrel, yrel: The vector of motion in the X/Y direction
    // param: x, y : coordinate, relative to window
    virtual void OnMouseMove(int x, int y, int xrelative, int yrelative) = 0;
    
    virtual void OnMouseButtonPressed(ALMouseButton button) = 0;
    
    virtual void OnMouseButtonReleased(ALMouseButton button) = 0;
    
    virtual void OnKeyPressed(ALKey k) = 0;
    
    virtual void OnKeyReleased(ALKey k) = 0;
    
    virtual ~AeoGameFramework() = default;
};

API void drawTestBackground();

API ALSize getSceneSize();

API int run(AeoGameFramework*);


#endif // AEOGAMELIB_AEOGAMEFRAMEWORK_HPP
