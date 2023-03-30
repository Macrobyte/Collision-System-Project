#include "Time.h"
#include <thread>
#include "VUtils.h"

float Time::_targetFrameTime = 0;
std::chrono::high_resolution_clock::time_point Time::_lastFrameTime = std::chrono::high_resolution_clock::now();
int Time::_frameCount = 0;
int Time::_fps = 0;
std::chrono::high_resolution_clock::time_point Time::_lastFPSTime = std::chrono::high_resolution_clock::now();

void Time::Initialize(float targetFrameTime)
{
	VUtils::LogWarning("Initializing Timer...");
	
	_targetFrameTime = targetFrameTime;
	_lastFrameTime = std::chrono::high_resolution_clock::now();
	
	VUtils::LogColor("Timer initialized.", VUtils::GREEN);
}

float Time::DeltaTime()
{
	auto currentFrameTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> elapsed = currentFrameTime - _lastFrameTime;
	_lastFrameTime = currentFrameTime;
	return elapsed.count();
}

void Time::Sleep()
{
	auto targetTime = _lastFrameTime + std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(_targetFrameTime));
	std::this_thread::sleep_until(targetTime);	
}

int Time::GetFPS()
{
	auto currentFrameTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> elapsed = currentFrameTime - _lastFPSTime;
	_frameCount++;
	if (elapsed.count() >= 1.0f)
	{
		_fps = static_cast<float>(_frameCount) / (float)elapsed.count();
		_frameCount = 0;
		_lastFPSTime = currentFrameTime;
	}
	
	return _fps;
}

