//
// Created by Aeomanate on 30.09.2021.
//

#ifndef AEOGAMELIB_AEOGAMEFRAMEWORK_HPP
#define AEOGAMELIB_AEOGAMEFRAMEWORK_HPP

#include <chrono>
#include <memory>

#if defined(AEO_STATIC) || !defined(_WIN32)
    #define API
#elif defined(FRAMEWORK_PROJECT)
    #define API __declspec(dllexport)
#else
    #define API __declspec(dllimport)
#endif


struct FRSize {
    int w, h;
};

class ALSpriteImpl;
class API FRSprite {
  public:
    explicit FRSprite(const char* path = nullptr);
    FRSprite(FRSprite&& other) noexcept;
    FRSprite(FRSprite const&) = delete;
    
    ~FRSprite();
    void Load(const char* path);
    
    void Draw(int x, int y);
    void SetSize(int width, int height);
    FRSprite FlipHorizontal();
    FRSize GetSizeWH();
  
  private:
    explicit FRSprite(ALSpriteImpl*);
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

enum class FRKey {
    RIGHT,
    LEFT,
    DOWN,
    UP,
    NONE
};

enum class FRMouseButton {
    LEFT,
    MIDDLE,
    RIGHT,
    NONE
};

class API AeoGameFramework {
  public:
    AeoGameFramework(
        FRSize scene_size,
        FRSize screen_size,
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
    
    virtual void OnMouseButtonPressed(FRMouseButton button) = 0;
    
    virtual void OnMouseButtonReleased(FRMouseButton button) = 0;
    
    virtual void OnKeyPressed(FRKey k) = 0;
    
    virtual void OnKeyReleased(FRKey k) = 0;
    
    virtual ~AeoGameFramework() = default;
};

API void drawTestBackground();

API FRSize getSceneSize();

API int run(AeoGameFramework*);


#endif // AEOGAMELIB_AEOGAMEFRAMEWORK_HPP
