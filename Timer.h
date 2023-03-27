#pragma once
#include <chrono>

class Timer
{
public:
    static void Initialize(float targetFrameTime);
    static float GetElapsedTime();
    static void Sleep();
	static int GetFPS();

private:
    static float _targetFrameTime;
    static std::chrono::high_resolution_clock::time_point _lastFrameTime;
    static int _frameCount;
	static int _fps;
	static std::chrono::high_resolution_clock::time_point _lastFPSTime;
};

