#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

using namespace std;

class Display {
public:
    // Color constants
    static const int BLACK = 0;
    static const int BLUE = 1;
    static const int GREEN = 2;
    static const int CYAN = 3;
    static const int RED = 4;
    static const int MAGENTA = 5;
    static const int YELLOW = 6;
    static const int WHITE = 7;
    static const int GRAY = 8;
    static const int LIGHT_BLUE = 9;
    static const int LIGHT_GREEN = 10;
    static const int LIGHT_CYAN = 11;
    static const int LIGHT_RED = 12;
    static const int LIGHT_MAGENTA = 13;
    static const int LIGHT_YELLOW = 14;
    static const int BRIGHT_WHITE = 15;

    static void setColor(int textColor, int bgColor = BLACK) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
    }

    static void resetColor() {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    }

    static void clearScreen() {
        system("cls");
    }

    static void printHeader(const string& title) {
        setColor(BRIGHT_WHITE, BLUE);
        cout << "\n " << title << " \n";
        resetColor();
        cout << "\n";
    }

    static void printMenuOption(int option, const string& text) {
        setColor(LIGHT_CYAN);
        cout << " [" << option << "] ";
        resetColor();
        cout << text << "\n";
    }

    static void printError(const string& message) {
        setColor(LIGHT_RED);
        cout << " [ERROR] " << message << "\n";
        resetColor();
        Beep(500, 200); // Sound alert
    }

    static void printSuccess(const string& message) {
        setColor(LIGHT_GREEN);
        cout << " [SUCCESS] " << message << "\n";
        resetColor();
    }

    static void printLine() {
        setColor(GRAY);
        cout << "========================================\n";
        resetColor();
    }

    static void printSystemLog(const string& message) {
        setColor(YELLOW);
        cout << " [SYSTEM] " << message << "\n";
        resetColor();
        Sleep(300); // Simulate processing time
    }

    static void loadingAnimation(const string& message) {
        setColor(LIGHT_MAGENTA);
        cout << " " << message;
        for (int i = 0; i < 3; i++) {
            cout << ".";
            Sleep(300);
        }
        cout << "\n";
        resetColor();
    }

    static void printAsciiArt() {
        setColor(LIGHT_CYAN);
        cout << R"(
   ___              _   ___      _ _                 
  | __|__  ___   __| | |   \ ___| (_)_ _____ _ _ _  
  | _/ _ \/ _ \ / _` | | |) / -_) | \ V / -_) '_| | 
  |_|\___/\___/ \__,_| |___/\___|_|_|\_/\___|_| |_| 
                                                    
        )" << "\n";
        resetColor();
    }
};

#endif
