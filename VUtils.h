#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <conio.h>
#include <random>


namespace VUtils
{
	const enum TextColors
	{
		BLACK = 0,
		DARK_BLUE = 1,
		DARK_GREEN = 2,
		DARK_CYAN = 3,
		DARK_RED = 4,
		DARK_MAGENTA = 5,
		DARK_YELLOW = 6,
		DARK_WHITE = 7,
		GRAY = 8,
		BLUE = 9,
		GREEN = 10,
		CYAN = 11,
		RED = 12,
		MAGENTA = 13,
		YELLOW = 14,
		WHITE = 15
	};

	const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	static void Log()
    {
        std::cout << std::endl;
    }

    /// <summary>
    /// Prints a message to the console
	/// You can add anything you want to print like this: Log("String", int, float)
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <param name="value"></param>
    /// <param name="...args"></param>
    template<typename T, typename... Args>
	static void Log(const T& value, const Args&... args)
    {
        std::ostringstream ss;
        ss << value;
        std::cout << ss.str();
        Log(args...);
    }

	/// <summary>
	/// Prints a message to the console that is red by default.
	/// Only the first argument will be red the rest will be the normal console color.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="value"></param>
	/// <param name="...args"></param>
	template<typename T, typename... Args>
	static void LogError(const T& value, const Args&... args)
	{
		std::ostringstream ss;
		ss << "\033[1;31m" << value << "\033[0m"; 
		std::cerr << ss.str(); 
		Log(args...);
	}

	/// <summary>
	/// Prints a message to the console that is green by default.
	/// Only the first argument will be green the rest will be the normal console color.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="value"></param>
	/// <param name="...args"></param>
	template<typename T, typename... Args>
	static void LogWarning(const T& value, const Args&... args)
	{
		std::ostringstream ss;
		ss << "\033[1;33m" << value << "\033[0m";
		std::cerr << ss.str();
		Log(args...);
	}



	/// <summary>
	/// Prints a message to the console with a desired color.
	/// You can use the ConsoleColors enum.
	/// </summary>
	/// <param name="message"></param>
	/// <param name="color"></param>
	static void LogColor(std::string message, int color)
	{
		SetConsoleTextAttribute(hOut, color);
		std::cout << message << std::endl;
		SetConsoleTextAttribute(hOut, WHITE);
	}

	/// <summary>
	/// Sets the output color of the console text.
	/// </summary>
	/// <param name="color"></param>
	static void SetColor(int color)
	{
		SetConsoleTextAttribute(hOut, color);
	}

	/// <summary>
	/// Clears the console screen.
	/// </summary>
	static void ClearConsole()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(hOut, &info);
		DWORD d = info.srWindow.Bottom * info.srWindow.Right;
		COORD coord = { 0,0 };
		FillConsoleOutputCharacter(hOut, ' ', d, coord, &d);
	}

	/// <summary>
	/// Sets the cursor at the chosen x and y position
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	static void SetCursor(short x, short y)
	{
		COORD coord = { x , y };
		SetConsoleCursorPosition(hOut, coord);
	}

	/// <summary>
	/// Returns a random number between the min and max values.
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	static int GetRandomNumber(int min, int max)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(min, max);
		return dist(mt);
	}

	/// <summary>
	///  If the value is less than the minimum, it is set to the minimum. 
	///  If the value is greater than the maximum, it is set to the maximum. 
	///  If the value is within the range, it is returned as is.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="value"></param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	template <typename T>
	T clamp(T value, T min, T max) 
	{
		return value < min ? min : (value > max ? max : value);
	}

	

}
	
	

