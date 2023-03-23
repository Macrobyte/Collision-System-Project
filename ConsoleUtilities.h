#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <conio.h>



namespace CUtils
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

}
	
	

