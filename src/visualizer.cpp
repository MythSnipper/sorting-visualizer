#include <visualizer.hpp>

ColorRGB::ColorRGB(uint8_t r, uint8_t g, uint8_t b)
    : r(r), g(g), b(b)
{}

ColorRGB::ColorRGB(int hex){
    r = (hex >> 16) & 0xFF;
    g = (hex >> 8) & 0xFF;
    b = hex & 0xFF;
}

void Visualizer::init(){
    //Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
    } 
    //create window
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(!window){
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        exit(1);
    }
    //make renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer){
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        exit(1);
	}

    //clear screen
    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, 255);
    SDL_RenderClear(renderer);

    //audio init
    SDL_AudioSpec desired{};
    SDL_AudioSpec obtained{};

    desired.freq = 48000;
    desired.format = AUDIO_F32SYS;
    desired.channels = 1;
    desired.samples = 512;
    desired.callback = &Visualizer::audioCallback;
    desired.userdata = this; //pass this to userdata

    audioDevice = SDL_OpenAudioDevice(nullptr, 0, &desired, &obtained, 0);
    if(audioDevice == 0){
        std::cout << "Error opening audio device: " << SDL_GetError() << std::endl;
        exit(1);
    }
    else{
        oscillator.enabled = true;
        SDL_PauseAudioDevice(audioDevice, 0);
    }


}

bool Visualizer::handleEvents(){
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
		switch(e.type){
			case SDL_QUIT:
                return false;
                break;
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
				break;
			case SDL_MOUSEMOTION:
				break;
		}
	}
    //window resize
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    return true;
}

void Visualizer::clearScreen(){
    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, 255);
    SDL_RenderClear(renderer);
}

void Visualizer::drawRect(int x, int y, int width, int height, ColorRGB color, bool fill){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);

    SDL_Rect r = {x, y, width, height};
    ((fill) ? SDL_RenderFillRect : SDL_RenderDrawRect)(renderer, &r);
}

void Visualizer::update(){
    SDL_RenderPresent(renderer);
}

void Visualizer::quit(){
    SDL_PauseAudioDevice(audioDevice, 1);
    SDL_CloseAudioDevice(audioDevice);
    audioDevice = 0;

    //destroy renderer
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    //destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

void Visualizer::sleep(int ms){
    SDL_Delay(ms);
}

void Visualizer::activeSleep(int ms){
    if(ms <= 100){
        this->sleep(100);
        return;
    }
    int tms = 0;
    while(tms < ms){
        if(!this->handleEvents())exit(0);
        this->sleep(16);
        tms += 16;
    }
}




void Visualizer::displayArray(std::vector<int>& arr){
    this->displayArrayS(arr, -1, bar_color);
}

void Visualizer::displayArrayS(std::vector<int>& arr, int index, ColorRGB hcolor){
    this->displayArrayD(arr, index, -1, hcolor);
}

void Visualizer::displayArrayD(std::vector<int>& arr, int index, int index2, ColorRGB hcolor){
    if(!this->handleEvents())exit(0);
    this->clearScreen();

    if(arr.size() == 0)return;

    //find min and max values in arr
    int minValue = arr[0];
    for(int& num : arr){
        minValue = (num < minValue) ? num : minValue;
    }

    int maxValue = arr[0];
    for(int& num : arr){
        maxValue = (num > maxValue) ? num : maxValue;
    }

    if(maxValue == minValue)return;

    //calculate sound freq
    int soundIndex = -1;

    if(index >= 0 && index < arr.size()){
        soundIndex = index;
    }
    else if(index2 >= 0 && index2 < arr.size()){
        soundIndex = index2;
    }
    //set frequency
    if(soundIndex >= 0){
        double frequency = valueToFrequency(arr[soundIndex], minValue, maxValue);
        setFrequency(frequency);
    }

    //left right padding and up down padding, in px
    int chartWidth = this->windowWidth - 2 * padding;
    int chartHeight = this->windowHeight - 2 * padding - text_padding;

    //width of bar(fixed)
    int barWidth = chartWidth / arr.size();
    if(barWidth <= 0)return;

    //length of bar
    int barMinLength = 2;
    //calculate how many px to increase for every increase in array value
    float dpx = (float)chartHeight / (maxValue-minValue);

    //precalc values for color modes
    //1


    //2
    int t2_minValue = arr[0];
    int t2_maxValue = arr[0];
    for(int value : arr){
        if (value < t2_minValue) t2_minValue = value;
        if (value > t2_maxValue) t2_maxValue = value;
    }
    double t2_section = (double)(t2_maxValue - t2_minValue) / 5.0;

    for(int i=0;i<arr.size();i++){
        int num = arr[i];

        int barLength = barMinLength + ((num - minValue) * dpx);
        int x = padding + i * barWidth;
        int y = (chartHeight+padding) - barLength + text_padding;
        
        ColorRGB barcolor = bar_color;
        if(colormode == 1){
            int frac = arr.size()/5;
            if(i < frac){
                barcolor = ColorRGB{0x5BCFFB};
            }
            else if(i < frac*2){
                barcolor = ColorRGB{0xF5ABB9};
            }
            else if(i < frac*3){
                barcolor = ColorRGB{0xFFFFFF};
            }
            else if(i < frac*4){
                barcolor = ColorRGB{0xF5ABB9};
            }
            else{
                barcolor = ColorRGB{0x5BCFFB};
            }
        }
        else if(colormode == 2){
            double t2_rel = arr[i] - t2_minValue;

            if(t2_rel < t2_section){
                barcolor = ColorRGB{0x5BCFFB};
            }
            else if(t2_rel < t2_section*2){
                barcolor = ColorRGB{0xF5ABB9};
            }
            else if(t2_rel < t2_section*3){
                barcolor = ColorRGB{0xFFFFFF};
            }
            else if(t2_rel < t2_section*4){
                barcolor = ColorRGB{0xF5ABB9};
            }
            else{
                barcolor = ColorRGB{0x5BCFFB};
            }
        }

        barcolor = (i==index || i == index2) ? hcolor : barcolor;
        
        this->drawRect(x, y, barWidth, barLength, barcolor, true);
    }

    this->update();
    if(tickrate > 0){
        this->sleep(1000/tickrate);
    }
}




void Visualizer::displayArray_sortedLim(std::vector<int>& arr, int index, ColorRGB hcolor){
    if(!this->handleEvents())exit(0);
    this->clearScreen();

    if(arr.size() == 0)return;

    //find min and max values in arr
    int minValue = arr[0];
    for(int& num : arr){
        minValue = (num < minValue) ? num : minValue;
    }

    int maxValue = arr[0];
    for(int& num : arr){
        maxValue = (num > maxValue) ? num : maxValue;
    }

    if(maxValue == minValue)return;

    //calculate sound freq
    int soundIndex = index;

    //set frequency
    if(soundIndex >= 0){
        double frequency = valueToFrequency(arr[soundIndex], minValue, maxValue);
        setFrequency(frequency);
    }

    //left right padding and up down padding, in px
    int chartWidth = this->windowWidth - 2 * padding;
    int chartHeight = this->windowHeight - 2 * padding - text_padding;

    //width of bar(fixed)
    int barWidth = chartWidth / arr.size();
    if(barWidth <= 0)return;

    //length of bar
    int barMinLength = 2;
    //calculate how many px to increase for every increase in array value
    float dpx = (float)chartHeight / (maxValue-minValue);

    //precalc values for color modes
    //1


    //2
    int t2_minValue = arr[0];
    int t2_maxValue = arr[0];
    for(int value : arr){
        if (value < t2_minValue) t2_minValue = value;
        if (value > t2_maxValue) t2_maxValue = value;
    }
    double t2_section = (double)(t2_maxValue - t2_minValue) / 5.0;


    for(int i=0;i<arr.size();i++){
        int num = arr[i];

        int barLength = barMinLength + ((num - minValue) * dpx);
        int x = padding + i * barWidth;
        int y = (chartHeight+padding) - barLength + text_padding;

        ColorRGB barcolor = bar_color;
        if(colormode == 1){
            int frac = arr.size()/5;
            if(i < frac){
                barcolor = ColorRGB{0x5BCFFB};
            }
            else if(i < frac*2){
                barcolor = ColorRGB{0xF5ABB9};
            }
            else if(i < frac*3){
                barcolor = ColorRGB{0xFFFFFF};
            }
            else if(i < frac*4){
                barcolor = ColorRGB{0xF5ABB9};
            }
            else{
                barcolor = ColorRGB{0x5BCFFB};
            }
        }
        else if(colormode == 2){
            double t2_rel = arr[i] - t2_minValue;

            if(t2_rel < t2_section){
                barcolor = ColorRGB{0x5BCFFB};
            }
            else if(t2_rel < t2_section*2){
                barcolor = ColorRGB{0xF5ABB9};
            }
            else if(t2_rel < t2_section*3){
                barcolor = ColorRGB{0xFFFFFF};
            }
            else if(t2_rel < t2_section*4){
                barcolor = ColorRGB{0xF5ABB9};
            }
            else{
                barcolor = ColorRGB{0x5BCFFB};
            }
        }

        barcolor = (i==index) ? hcolor : barcolor;

        this->drawRect(x, y, barWidth, barLength, (i<=index) ? hcolor : barcolor, true);
    }

    this->update();
}

void Visualizer::sortedAnimation(std::vector<int>& arr){
    for(int i=0;i<arr.size();i++){
        displayArray_sortedLim(arr, i, sorted_color);
        this->sleep((int)(((float)sorted_animation_ms/arr.size()) + 0.5));
    }
}




void Visualizer::setFrequency(double frequency){
    if(audioDevice == 0){
        return;
    }
    SDL_LockAudioDevice(audioDevice);
    oscillator.frequency = frequency;
    SDL_UnlockAudioDevice(audioDevice);
}

void Visualizer::setAudioEnabled(bool enabled){
    if(audioDevice == 0){
        return;
    }
    SDL_LockAudioDevice(audioDevice);
    oscillator.enabled = enabled;

    if(!enabled){
        oscillator.phase = 0.0;
    }
    SDL_UnlockAudioDevice(audioDevice);
}

double Visualizer::valueToFrequency(int value, int minValue, int maxValue){
    double low = 120.0;
    double high = 1212.0;
    if(minValue == maxValue){
        return low;
    }
    double t = (double)(value - minValue) / (double)(maxValue - minValue);
    
    return low + t * (high - low);
}

void Visualizer::audioCallback(void* userdata, uint8_t* stream, int len){
    if(userdata == nullptr){
        return;
    }

    Visualizer* visualizer = (Visualizer*)userdata;

    Oscillator& osc = visualizer->oscillator;

    if(!osc.enabled){
        SDL_memset(stream, 0, len);
        return;
    }

    float* buffer = (float*)(stream);

    int samples = len / sizeof(float);
    double sampleRate = 48000.0;

    for(int i=0;i<samples;i++){
        buffer[i] = (float)(std::sin(osc.phase) * osc.volume);

        osc.phase += 2.0 * M_PI * osc.frequency / sampleRate;

        if(osc.phase > 2.0 * M_PI){
            osc.phase -= 2.0 * M_PI;
        }
    }
}




