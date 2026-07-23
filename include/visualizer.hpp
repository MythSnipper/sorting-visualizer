#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>

struct ColorRGB{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    ColorRGB(uint8_t r, uint8_t g, uint8_t b);
    ColorRGB(int hex);
};

struct Oscillator {
    double frequency = 0.0;
    double phase = 0.0;
    double volume = 0.05; //0.0 - 1.0
    bool enabled = false;
};


class Visualizer{
    public:
        ColorRGB bg_color = {0x202020};
        std::string title;
        int windowWidth, windowHeight;
        int tickrate = 100; //how many ticks per second
        int sorted_animation_ms = 1000; //sorted animation display for
        int shuffle_animation_ms = 2000; //shuffle animation display for

        //paddings
        int text_padding = 50; //padding for displaying the text at the top
        int padding = 2; //padding from the window frame overall

        //Text
        //path to font
        char* font_path = NULL;
        //font
        TTF_Font* font = NULL;
        //current displaying text
        std::string label;

        ColorRGB bar_color = {0xFFFFFF};
        ColorRGB read_color = {0xFFA500};
        ColorRGB write_color = {0xFF0000};
        ColorRGB sorted_color = {0x00FF00};

        int colormode = 0;
        //1 is special colors of june
        //2 is same as 1 but non static coloring

        //store indices with either read or write, 0 read 1 write
        std::vector<std::pair<int, bool>> displayIndices;
        //if above vector has displayIndicesMaxCount elements, display one frame
        int displayIndicesMaxCount = 1;


        void init();
        bool handleEvents();
        void clearScreen();
        void drawRect(int x, int y, int width, int height, ColorRGB color, bool fill);
        void drawText(std::string& text, int x, int y, ColorRGB color);
        void update();
        void quit();
        void sleep(int ms);
        void activeSleep(int ms);

        void displayArray(std::vector<int>& arr);
        void displayArrayS(std::vector<int>& arr, int index, ColorRGB hcolor);
        void displayArrayD(std::vector<int>& arr, int index, int index2, ColorRGB hcolor);

        void displayArray_sortedLim(std::vector<int>& arr, int index, ColorRGB hcolor);
        void sortedAnimation(std::vector<int>& arr);


        void setFrequency(double frequency);
        void setAudioEnabled(bool enabled);
        double valueToFrequency(int value, int minValue, int maxValue);
        

    private:
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        SDL_AudioDeviceID audioDevice = 0;
        Oscillator oscillator;

        static void audioCallback(void* userdata, uint8_t* stream, int len);
};




