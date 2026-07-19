#include <main.hpp>

int main(int argc, char** argv){
    //settings
    std::string title = "Sorting Visualizer";
    int WINDOW_WIDTH = 1320;
    int WINDOW_HEIGHT = 720;

    Visualizer v;
    v.title = title;
    v.windowWidth = WINDOW_WIDTH;
    v.windowHeight = WINDOW_HEIGHT;
    v.font_path = "cozette.ttf";

    v.init();
    v.clearScreen();

    //array to sort
    std::vector<int> arr;

    //sorting algorithms
    //list of algs, display names, recommended input size, recommended tick rate
    void (*algs[])(Visualizer&, std::vector<int>&) = {
        selection_sort, //0
        double_selection_sort, 
        insertion_sort, 
        binary_insertion_sort, 
        bubble_sort, //4
        cocktail_shaker_sort, 
        quick_sort, 
        merge_sort, 
        heap_sort, //8
        comb_sort, 
        shell_sort,
        radix_sort_LSD_base4, 
        radix_sort_MSD_base4, 
        bogo_sort, 
        stalin_sort, 
    };
    char* alg_label[] = {
        "Selection Sort", //0
        "Double Selection Sort", 
        "Insertion Sort", 
        "Binary Insertion Sort", 
        "Bubble Sort", //4
        "Cocktail Shaker Sort", 
        "Quicksort", 
        "Merge Sort", 
        "Heapsort", //8
        "Comb Sort", 
        "Shell Sort",
        "Radix Sort(LSD) base 4", 
        "Radix Sort(MSD) base 4", 
        "Bogosort", 
        "Stalin Sort", 
    };
    int resosize = WINDOW_WIDTH-10;
    int algs_inputsize[] = {
        resosize/4, //0
        resosize/4, 
        resosize/4, 
        resosize/4, 
        resosize/4, //4
        resosize/4, 
        resosize, 
        resosize, 
        resosize, //8
        resosize, 
        resosize, 
        resosize, 
        resosize, 
        6, 
        resosize, 
    };
    int algs_tickrate[] = {
        0, //0
        0, 
        0, 
        0, 
        0, //4
        0, 
        0, 
        0, 
        0, //8
        0, 
        0, 
        0, 
        0, 
        0, 
        0, 
    };
    int numAlgsImplemented = sizeof(algs)/sizeof(algs[0]);

    int algs_inputsize_fixed = resosize;
    int algs_tickrate_fixed = 0;

    bool use_recommended_inputsize = true;
    bool use_recommended_tickrate = true;
    bool oneshot = false;
    bool loop = true;

    arr = generateShuffledArray(use_recommended_inputsize ? algs_inputsize[0] : algs_inputsize_fixed);
    do{
        for(int i=11;i<numAlgsImplemented;i++){
            //set tick rate
            v.tickrate = use_recommended_tickrate ? algs_tickrate[i] : algs_tickrate_fixed; //0 is very fast

            //shuffle array
            v.label = "Shuffling";
            shuffle_array_anim(v, arr, use_recommended_inputsize ? algs_inputsize[i] : algs_inputsize_fixed);

            //sort array
            run_sort_anim(v, arr, algs[i], alg_label[i], oneshot);
            std::cout << "Sort " << i << " finished!\n";
        }
    }while(loop);


    bool running = true;
    while(running){
        running = v.handleEvents();
        v.sleep(16);
    }

    v.quit();

	return 0;
}

std::vector<int> generateRandomArray(int length, int minValue, int maxValue){
    std::mt19937 rng(std::random_device{}());

    std::uniform_int_distribution<int> dist(minValue, maxValue);

    std::vector<int> values(length);

    for(int& value : values) {
        value = dist(rng);
    }
    return values;
}

std::vector<int> generateShuffledArray(int length){
    std::vector<int> values(length);
    for(int i=0;i<length;i++){
        values[i] = i+1;
    }

    static std::mt19937 rng(std::random_device{}());

    std::shuffle(values.begin(), values.end(), rng);

    return values;
}

std::vector<int> shuffleArray(std::vector<int>& arr){
    std::vector<int> values(arr.size());
    for(int i=0;i<arr.size();i++) {
        values[i] = arr[i];
    }

    static std::mt19937 rng(std::random_device{}());

    std::shuffle(values.begin(), values.end(), rng);

    return values;
}


void run_sort_anim(Visualizer& v, std::vector<int>& arr, void (*alg)(Visualizer&, std::vector<int>&), char* alg_label, bool oneshot){
    v.label = alg_label;
    v.clearScreen();
    v.displayArray(arr);
    v.activeSleep(2000);
    v.setAudioEnabled(true);

    //run sort
    alg(v, arr);

    v.setAudioEnabled(false);

    v.displayArray(arr);
    v.activeSleep(200);

    v.sorted_animation_ms = 1000;
    v.setAudioEnabled(true);
    v.sortedAnimation(arr);
    v.setAudioEnabled(false);

    v.displayArray(arr);
    v.activeSleep(100);

    v.sorted_animation_ms = 200;
    v.setAudioEnabled(true);
    v.sortedAnimation(arr);
    v.setAudioEnabled(false);

    //hang if oneshot
    while(oneshot){
        v.activeSleep(2000);
    }
    v.activeSleep(1000);
    v.displayArray(arr);
}

void shuffle_array_anim(Visualizer& v, std::vector<int>& arr, int size){
    //temporarily set to 4
    int tmp = v.displayIndicesMaxCount;
    v.displayIndicesMaxCount = 4;
    //make new shuffled array
    std::vector<int> new_arr;
    new_arr.reserve(size);
    new_arr = generateShuffledArray(size);
    arr.resize(size);

    v.setAudioEnabled(true);
    //copy to original array, with no sleep
    int tmptickrate = v.tickrate;
    v.tickrate = 0;
    for(int i=0;i<size;i++){
        arr[i] = new_arr[i];
        v.displayArrayS(arr, i, v.write_color);
        v.sleep((int)((float)(v.shuffle_animation_ms)/size + 0.5));
    }
    v.tickrate = tmptickrate;
    v.setAudioEnabled(false);
    v.displayArray(arr);
    v.displayIndicesMaxCount = tmp;
}



