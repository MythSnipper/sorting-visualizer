#include <sorts.hpp>

#include <main.hpp>

//sorts
void selection_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;
    for(int i=0;i<n-1;i++){
        int min_I = i;
        //find index of smallest
        for(int j=i+1;j<n;j++){
            bool ifcond = arr[j] < arr[min_I];
            v.displayArrayD(arr, j, min_I, v.read_color);
            if(ifcond){
                min_I = j;
            }
        }

        //swap
        std::swap(arr[i], arr[min_I]);
        v.displayArrayD(arr, i, min_I, v.write_color);
    }
}

void double_selection_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;
    for(int i=0;i<n/2;i++){
        int min_I = i;
        int max_I = i;
        //find index of smallest and largest
        for(int j=i+1;j<=n-1-i;j++){
            bool if1cond = arr[j] < arr[min_I];
            v.displayArrayD(arr, j, min_I, v.read_color);
            if(if1cond){
                min_I = j;
            }

            bool if2cond = arr[j] > arr[max_I];
            v.displayArrayD(arr, j, max_I, v.read_color);
            if(if2cond){
                max_I = j;
            }
        }

        //swap
        std::swap(arr[i], arr[min_I]);
        v.displayArrayD(arr, i, min_I, v.write_color);

        max_I = (max_I == i) ? min_I : max_I;
        std::swap(arr[n-1-i], arr[max_I]);
        v.displayArrayD(arr, n-1-i, max_I, v.write_color);

    }
}

void insertion_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;
    for(int i=1;i<n;i++){
        int key = arr[i];
        v.displayArrayS(arr, i, v.read_color);
        int j = i-1;

        while(1){
            bool whilecond = (j >= 0 && arr[j] > key);
            v.displayArrayS(arr, j, v.read_color);
            if(!whilecond)break; //while loop condition

            arr[j+1] = arr[j];
            v.displayArrayS(arr, j, v.read_color);
            v.displayArrayS(arr, j+1, v.write_color);
            j--;
        }
        arr[j+1] = key;
        v.displayArrayS(arr, j+1, v.write_color);
    }
}

void binary_insertion_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;
    for(int i=1;i<n;i++){
        int key = arr[i];
        v.displayArrayS(arr, i, v.read_color);

        //sorted portion is 0 to i-1, binary search on that
        int min_I = 0;
        int max_I = i;
        while(min_I < max_I){
            int mid_I = min_I + ((max_I - min_I)/2);

            bool ifcond = arr[mid_I] <= key;
            v.displayArrayS(arr, mid_I, v.read_color);
            if(ifcond){
                min_I = mid_I + 1;
            }
            else{
                max_I = mid_I;
            }

            mid_I = min_I + ((max_I - min_I)/2);
        }

        //shift elements over by one
        for(int u=i;u>min_I;u--){
            arr[u] = arr[u-1];
            v.displayArrayS(arr, u, v.read_color);
            v.displayArrayS(arr, u-1, v.write_color);
        }
        //make mid_I+1 the key value
        arr[min_I] = key;
        v.displayArrayS(arr, min_I, v.write_color);
    }
}

void bubble_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;
    for(int i=0;i<n-1;i++){
        bool swapped = false;
        for(int j=0;j<n-i-1;j++){
            bool swapcond = arr[j] > arr[j+1];
            v.displayArrayD(arr, j, j+1, v.read_color);
            if(swapcond){
                //swap
                std::swap(arr[j], arr[j+1]);
                v.displayArrayD(arr, j, j+1, v.write_color);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
    }
}

void cocktail_shaker_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;

    int minptr = 0;
    int maxptr = n-1;

    while(minptr < maxptr){
        bool swapped = false;
        //shake from left to right
        for(int j=minptr;j<maxptr;j++){
            bool swapcond = arr[j] > arr[j+1];
            v.displayArrayD(arr, j, j+1, v.read_color);
            if(swapcond){
                //swap
                std::swap(arr[j], arr[j+1]);
                v.displayArrayD(arr, j, j+1, v.write_color);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
        maxptr--;

        swapped = false;
        //shake from right to left
        for(int j=maxptr;j>minptr;j--){
            bool swapcond = arr[j] < arr[j-1];
            v.displayArrayD(arr, j, j-1, v.read_color);
            if(swapcond){
                //swap
                std::swap(arr[j], arr[j-1]);
                v.displayArrayD(arr, j, j-1, v.write_color);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
        minptr++;
    }
}

void quick_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;
    quick_sort_helper(v, arr, 0, n-1);
}
void quick_sort_helper(Visualizer& v, std::vector<int>& arr, int start, int end){
    int n = arr.size();
    if(start < 0 || end < 0 || start >= n || end >= n || start >= end)return;

    //partition
    int pivot = arr[start];
    v.displayArrayS(arr, start, v.read_color);
    int leftptr = start+1;
    int rightptr = end;
    while(1){
        //leftptr moves right until it finds one bigger than the pivot
        
        while(1){
            bool whilecond1 = leftptr <= rightptr && arr[leftptr] <= pivot;
            v.displayArrayS(arr, leftptr, v.read_color);
            if(!whilecond1)break; //while condition
            leftptr++;
        }

        //rightptr moves left until it finds one smaller than the pivot
        while(1){
            bool whilecond2 = leftptr <= rightptr && arr[rightptr] >= pivot;
            v.displayArrayS(arr, rightptr, v.read_color);
            if(!whilecond2)break; //while condition
            rightptr--;
        }

        if(leftptr > rightptr)break;

        //if both conditions are satisfied, swap them
        std::swap(arr[leftptr], arr[rightptr]);
        v.displayArrayD(arr, leftptr, rightptr, v.write_color);

        //advance pointers
        leftptr++;
        rightptr--;
    }
    //swap pivot with leftptr-1
    std::swap(arr[start], arr[rightptr]);
    v.displayArrayD(arr, start, rightptr, v.write_color);

    //run quicksort on left and right
    quick_sort_helper(v, arr, start, rightptr-1);
    quick_sort_helper(v, arr, rightptr+1, end);
}

void merge_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;
    merge_sort_helper(v, arr, 0, n-1);
}
void merge_sort_helper(Visualizer& v, std::vector<int>& arr, int start, int end){
    //if list size is 1, do nothing
    int n = arr.size();
    if(start < 0 || end < 0 || start >= n || end >= n || start >= end)return;

    //split list in halves
    int mid = start + (end-start)/2;
    //sort list from start to mid
    merge_sort_helper(v, arr, start, mid);
    //sort list from mid+1 to end
    merge_sort_helper(v, arr, mid+1, end);

    //merge sorted halves
    int a = start; //goes from start to mid
    int b = mid+1; //goes from mid+1 to end

    std::vector<int> aux_arr;
    aux_arr.reserve(end-start+1);

    while(a <= mid && b <= end){
        bool ifcond1 = arr[a] <= arr[b];
        v.displayArrayD(arr, a, b, v.read_color);
        if(ifcond1){
            aux_arr.push_back(arr[a]);
            v.displayArrayS(arr, a, v.read_color);
            a++;
        }
        else{
            aux_arr.push_back(arr[b]);
            v.displayArrayS(arr, b, v.read_color);
            b++;
        }

    }
    //copy remaining
    while(a <= mid){
        aux_arr.push_back(arr[a]);
        v.displayArrayS(arr, a, v.read_color);
        a++;
    }
    while(b <= end){
        aux_arr.push_back(arr[b]);
        v.displayArrayS(arr, b, v.read_color);
        b++;
    }

    n = aux_arr.size();

    for(int i=0;i+1<n;i+=2){ //copy aux_arr to arr
        arr[start+i] = aux_arr[i];
        arr[start+i+1] = aux_arr[i+1];
        v.displayArrayD(arr, start+i, start+i+1, v.write_color);
    }
    if(n % 2 != 0){
        arr[start+n-1] = aux_arr[n-1];
        v.displayArrayS(arr, start+n-1, v.write_color);
    }
}

/*
Notes:
    array itself is a binary tree
    left child of node at index i: 2i+1
    right child of node at index i: 2i+2 
    max heap:
    value of parent > value of childrens

    First construct max heap(max element at index 0
    move the root value of max heap to the end of the array, making it complete
    the rest of the array is still the binary tree
    
    FIRST time constructing max heap
    treat array as btree, then find last non leaf node

    For n elements:
    last_non_leaf = n/2 - 1

    start at that index, perform sift down for elements in [last_non_leaf ..= 0]

    heap size means heap is in array from 0 to heapsize, as in (0 <= i < heapsize) and the next num to swap is arr[heapsize-1], starting heap size is n
*/
void heap_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;

    //build max heap by sift down from [n/2-1 ..= 0]
    for(int i=n/2-1;i>=0;i--){
        heap_sort_sift_down(v, arr, i, n);
    }

    for(int heapsize=n;heapsize>0;heapsize--){
        //swap maximum with end
        std::swap(arr[0], arr[heapsize-1]);
        v.displayArrayD(arr, 0, heapsize-1, v.write_color);

        //sift down from index 0 again, with one less heapsize
        heap_sort_sift_down(v, arr, 0, heapsize-1);
    }
    
}
void heap_sort_sift_down(Visualizer& v, std::vector<int>& arr, int index, int heapsize){
    int n = arr.size();
    if(heapsize <= 1 || heapsize > n || index < 0 || index >= heapsize)return;
    //indexes
    int leftchild_i;
    int rightchild_i;
    bool hasleft = heap_sort_get_left_child_i(v, arr, index, leftchild_i, heapsize);
    bool hasright = heap_sort_get_right_child_i(v, arr, index, rightchild_i, heapsize);

    //Find index of max child
    int maxchild_i;
    if(hasleft && hasright){
        //compare both
        maxchild_i = (arr[rightchild_i] > arr[leftchild_i]) ? rightchild_i : leftchild_i;
        v.displayArrayD(arr, rightchild_i, leftchild_i, v.read_color);
    }
    else if(hasleft || hasright){
        maxchild_i = hasleft ? leftchild_i : rightchild_i;
    }
    else{ //no children
        return;
    }
    //swap with maxchild if the current is smaller than the children
    bool ifcond = arr[index] < arr[maxchild_i];
    v.displayArrayD(arr, index, maxchild_i, v.read_color);
    if(ifcond){
        std::swap(arr[index], arr[maxchild_i]);
        v.displayArrayD(arr, index, maxchild_i, v.write_color);
        
        //continue the sift down
        heap_sort_sift_down(v, arr, maxchild_i, heapsize);
    }
}
bool heap_sort_get_left_child_i(Visualizer& v, std::vector<int>& arr, int index, int& ret, int heapsize){ //returns bool if child exists
    int n = arr.size();
    if(heapsize < 0 || heapsize > n || index < 0 || index >= heapsize)return false;
    int leftindex = 2 * index + 1;
    if(leftindex < heapsize){
        ret = leftindex;
        return true;
    }
    return false;
}
bool heap_sort_get_right_child_i(Visualizer& v, std::vector<int>& arr, int index, int& ret, int heapsize){ //returns bool if child exists
    int n = arr.size();
    if(heapsize < 0 || heapsize > n || index < 0 || index >= heapsize)return false;
    int rightindex = 2 * index + 2;
    if(rightindex < heapsize){
        ret = rightindex;
        return true;
    }
    return false;
}

void comb_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;

    int combsize = comb_sort_get_next_combsize(n);

    //comb until size is 1
    while(combsize != 1){
        //comb
        comb_sort_comb(v, arr, combsize);
        //get new size
        combsize = comb_sort_get_next_combsize(combsize);
    }
    bool sorted = false;
    //while not sorted comb with size 1 until it is sorted
    while(!sorted){
        //comb
        sorted = comb_sort_comb(v, arr, 1);
    }
}
int comb_sort_get_next_combsize(int combsize){ //returns the next comb size
    if(combsize <= 1)return 1;

    int newsize = (int)((float)combsize) / 1.3f;
    return (newsize == 0) ? 1 : newsize;
}
bool comb_sort_comb(Visualizer& v, std::vector<int>& arr, int combsize){ //returns true if no swaps made
    int n = arr.size();
    if(n < 2 || combsize <= 0 || combsize >= n)return true;

    bool sorted = true;

    //combs the array once
    for(int i=0;i<n-combsize;i++){
        //compare arr[i] and arr[i+combsize]
        bool ifcond = arr[i] > arr[i+combsize];
        v.displayArrayD(arr, i, i+combsize, v.read_color);
        if(ifcond){
            //swap
            std::swap(arr[i], arr[i+combsize]);
            v.displayArrayD(arr, i, i+combsize, v.write_color);
            sorted = false;
        }
    }
    return sorted;
}

void shell_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;

    std::vector<int> gaps = {701, 301, 132, 57, 23, 10, 4, 1};
    for(int gapsize : gaps){
        //sort
        shell_sort_gapped_insertion(v, arr, gapsize);
    }
}
void shell_sort_gapped_insertion(Visualizer& v, std::vector<int>& arr, int gapsize){
    int n = arr.size();
    if(n < 2 || gapsize <= 0 || gapsize >= n)return;

    for(int i=gapsize;i<n;i++){
        int key = arr[i];
        v.displayArrayS(arr, i, v.read_color);
        int j = i;

        while(j >= gapsize){
            bool ifcond = arr[j-gapsize] <= key;
            v.displayArrayS(arr, j-gapsize, v.read_color);
            if(ifcond)break;

            arr[j] = arr[j-gapsize];
            //skipped: redundant
            //    v.displayArrayS(arr, j-gapsize, v.read_color);
            v.displayArrayS(arr, j, v.write_color);
            j -= gapsize;
        }
        arr[j] = key;
        v.displayArrayS(arr, j, v.write_color);
    }
}

void radix_sort_LSD(Visualizer& v, std::vector<int>& arr, int base){
    int n = arr.size();
    if(n < 2 || base < 2)return;
    //find max integer in array
    int max = arr[0];
    v.displayArrayS(arr, 0, v.read_color);
    for(int i=1;i<n;i++){
        max = (arr[i]>max) ? arr[i] : max;
        v.displayArrayS(arr, i, v.read_color);
    }

    //auxiliary array to store elements
    std::vector<int> aux(n);
    
    //auxiliary array to store digit positions
    std::vector<int> positions(base);

    //auxiliary array to store occurances for a digit
    std::vector<int> occurances(base);

    //Do rounds
    int divisor = 1;
    while(max != 0){
        max /= base;

        //count occurance of a digit
        for(int i=0;i<n;i++){
            v.displayArrayS(arr, i, v.read_color);
            int digit = (arr[i] / divisor) % base;
            occurances[digit]++;
        }
        //do running count and put in positions array
        int sum = 0;
        for(int i=0;i<base;i++){
            positions[i] = sum;
            sum += occurances[i];
            //reset occurances array
            occurances[i] = 0;
        }

        //go through the array for the current base and put it in the aux array based on positions array
        for(int i=0;i<n;i++){
            v.displayArrayS(arr, i, v.read_color);
            int digit = (arr[i] / divisor) % base;
            aux[positions[digit]] = arr[i];
            positions[digit]++;
        }

        //copy aux to arr
        for(int i=0;i+1<n;i+=2){
            arr[i] = aux[i];
            arr[i+1] = aux[i+1];
            v.displayArrayD(arr, i, i+1, v.write_color);
        }
        if(n % 2 != 0){
            arr[n-1] = aux[n-1];
            v.displayArrayS(arr, n-1, v.write_color);
        }
        divisor *= base;
    }

}
void radix_sort_LSD_base4(Visualizer& v, std::vector<int>& arr){
    radix_sort_LSD(v, arr, 4);
}

void radix_sort_MSD(Visualizer& v, std::vector<int>& arr, int base){
    int n = arr.size();
    if(n < 2 || base < 2)return;
    //find biggest number
    int max = arr[0];
    for(int i=1;i<n;i++){
        max = (arr[i] > max) ? arr[i] : max;
        v.displayArrayS(arr, i, v.read_color);
    }
    //find divisor
    int tmp = max;
    //divide tmp by base first, then finding divisor is finding power of base that is bigger than max
    tmp /= base;
    int divisor = 1;
    while(divisor < tmp){
        divisor *= base;
    }
    radix_sort_MSD_helper(v, arr, base, 0, n, divisor);
}
//sorts section where startI <= i < endI
void radix_sort_MSD_helper(Visualizer& v, std::vector<int>& arr, int base, int startI, int endI, int divisor){
    int n = endI-startI;
    if(base < 2 || divisor <= 0 || startI < 0 || endI < startI || endI > arr.size() || n < 2)return;

    //count how many values belong to each digit bucket
    std::vector<int> occurances(base);
    std::vector<int> positions(base);

    for(int i=startI;i<endI;i++){
        int digit = (arr[i] / divisor) % base;
        v.displayArrayS(arr, i, v.read_color);
        occurances[digit]++;
    }

    //calculate where each bucket starts
    int sum = startI;
    for(int i=0;i<base;i++){
        positions[i] = sum;
        sum += occurances[i];
    }

    //reuse occurances array as a temporary positions array
    for(int i=0;i<base;i++){
        occurances[i] = positions[i];
    }

    //distribute values into an auxiliary array
    std::vector<int> aux(n);
    for(int i=startI;i<endI;i++){
        int digit = (arr[i] / divisor) % base;
        aux[occurances[digit]-startI] = arr[i];
        v.displayArrayS(arr, i, v.read_color);
        occurances[digit]++;
    }

    //copy from aux to arr
    for(int i=startI;i+1<endI;i+=2){
        arr[i] = aux[i-startI];
        arr[i+1] = aux[i-startI+1];
        v.displayArrayD(arr, i, i+1, v.write_color);
    }
    if(n % 2 != 0){
        arr[endI-1] = aux[n-1];
        v.displayArrayS(arr, endI-1, v.write_color);
    }

    //sort buckets by recursion
    for(int i=0;i<base-1;i++){
        radix_sort_MSD_helper(v, arr, base, positions[i], positions[i+1], divisor/base);
    }
    radix_sort_MSD_helper(v, arr, base, positions[base-1], endI, divisor/base);
}
void radix_sort_MSD_base4(Visualizer& v, std::vector<int>& arr){
    radix_sort_MSD(v, arr, 4);
}

void bucket_sort_helper(Visualizer& v, std::vector<int>& arr, int NumOfBuckets){
    int n = arr.size();
    if(n < 2 || NumOfBuckets <= 0)return;
    //find max value
    int max = arr[0];
    v.displayArrayS(arr, 0, v.read_color);
    for(int i=1;i<n;i++){
        max = (arr[i]>max) ? arr[i] : max;
        v.displayArrayS(arr, i, v.read_color);
    }

    //bucket size
    int bucketSize = max / NumOfBuckets;

    //bucketing step
    std::vector<int> occurances(NumOfBuckets+1);
    std::vector<int> positions(NumOfBuckets+1);

    for(int i=0;i<n;i++){
        occurances[arr[i] / bucketSize]++;
        v.displayArrayS(arr, i, v.read_color);
    }

    int sum = 0;
    for(int i=0;i<NumOfBuckets+1;i++){
        positions[i] = sum;
        sum += occurances[i];
    }

    //copy positions to occurances so sorting uses occurances array
    for(int i=0;i<positions.size();i++){
        occurances[i] = positions[i];
    }

    //construct aux array, reuse occurances as positions
    std::vector<int> aux(n);

    for(int i=0;i<n;i++){
        aux[occurances[arr[i] / bucketSize]] = arr[i];
        occurances[arr[i] / bucketSize]++;
        v.displayArrayS(arr, i, v.read_color);
    }

    //copy aux array to array
    for(int i=0;i+1<n;i+=2){
        arr[i] = aux[i];
        arr[i+1] = aux[i+1];
        v.displayArrayD(arr, i, i+1, v.write_color);
    }
    if(n % 2 != 0){
        arr[n-1] = aux[n-1];
        v.displayArrayS(arr, n-1, v.write_color);
    }

    //sort each bucket
    for(int i=0;i<NumOfBuckets;i++){
        bucket_sort_sortbucket(v, arr, positions[i], positions[i+1]);
    }
    bucket_sort_sortbucket(v, arr, positions[NumOfBuckets], n);
}
void bucket_sort_sortbucket(Visualizer& v, std::vector<int>& arr, int startI, int endI){
    int n = endI-startI;
    if(n < 2)return;
    for(int i=startI;i<endI;i++){
        int key = arr[i];
        v.displayArrayS(arr, i, v.read_color);
        int j = i-1;

        while(1){
            bool whilecond = (j >= startI && arr[j] > key);
            v.displayArrayS(arr, j, v.read_color);
            if(!whilecond)break; //while loop condition

            arr[j+1] = arr[j];
            v.displayArrayS(arr, j, v.read_color);
            v.displayArrayS(arr, j+1, v.write_color);
            j--;
        }
        arr[j+1] = key;
        v.displayArrayS(arr, j+1, v.write_color);
    }




}
void bucket_sort(Visualizer& v, std::vector<int>& arr){
    bucket_sort_helper(v, arr, 50);
}

void counting_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;
    //find max value
    int max = arr[0];
    v.displayArrayS(arr, 0, v.read_color);
    for(int i=1;i<n;i++){
        max = (arr[i]>max) ? arr[i] : max;
        v.displayArrayS(arr, i, v.read_color);
    }

    //bucketing step
    std::vector<int> occurances(max+1);
    std::vector<int> positions(max+1);

    for(int i=0;i<n;i++){
        occurances[arr[i]]++;
        v.displayArrayS(arr, i, v.read_color);
    }

    int sum = 0;
    for(int i=0;i<=max;i++){
        positions[i] = sum;
        sum += occurances[i];
    }

    //copy positions to occurances so sorting uses occurances array
    for(int i=0;i<positions.size();i++){
        occurances[i] = positions[i];
    }

    //construct aux array, reuse occurances as positions
    std::vector<int> aux(n);

    for(int i=0;i<n;i++){
        aux[occurances[arr[i]]] = arr[i];
        occurances[arr[i]]++;
        v.displayArrayS(arr, i, v.read_color);
    }

    //copy aux array to array
    for(int i=0;i+1<n;i+=2){
        arr[i] = aux[i];
        arr[i+1] = aux[i+1];
        v.displayArrayD(arr, i, i+1, v.write_color);
    }
    if(n % 2 != 0){
        arr[n-1] = aux[n-1];
        v.displayArrayS(arr, n-1, v.write_color);
    }
}

//spaghetti sort(incomplete)

void gravity_sort(Visualizer& v, std::vector<int>& arr){
    bool fast = true;

    int n = arr.size();
    if(n < 2)return;

    //find max
    int max = arr[0];
    for(int i=1;i<n;i++){
        max = (arr[i] > max) ? arr[i] : max;
        if(!fast){
            v.displayArrayS(arr, i, v.read_color);
        }
    }
    
    std::vector<uint8_t> aux(n*max);
    
    //fill aux
    for(int i=0;i<n;i++){
        //fill beads in column
        int num = arr[i];
        if(!fast){
            v.displayArrayS(arr, i, v.read_color);
        }
        for(int j=0;j<num;j++){
            aux[i*n+j] = 1;
        }
    }


    bool sorted = false;
    while(!sorted){
        sorted = true;

        //shift beads over
        for(int i=0;i<max;i++){ //row(height)
            for(int j=n-2;j>=0;j--){ //right to left
                if(aux[j*n+i] && !aux[(j+1)*n+i]){
                    aux[j*n+i] = 0;
                    aux[(j+1)*n+i] = 1;
                    sorted = false;

                    arr[j]--;
                    arr[j+1]++;
                }
            }
        }
        if(fast){
            v.displayArray(arr);
        }
    }
}

void pancake_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;
    for(int i=0;i<n-1;i++){
        int min_I = i;
        //find index of smallest
        for(int j=i+1;j<n;j++){
            bool ifcond = arr[j] < arr[min_I];
            v.displayArrayD(arr, j, min_I, v.read_color);
            if(ifcond){
                min_I = j;
            }
        }

        //instead of swapping i and min_I, pancake flippy floppy two times
        pancake_sort_flip(v, arr, min_I, n);
        pancake_sort_flip(v, arr, i, n);
    }
}
void pancake_sort_flip(Visualizer& v, std::vector<int>& arr, int start, int end){
    int n = arr.size();
    int size = end-start;

    for(int i=0;i<size/2;i++){
        std::swap(arr[i+start], arr[end-1-i]);
    }
    v.displayArray(arr);
}

void cycle_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;

    for(int i=0;i<n-1;i++){
        int curr = arr[i];

        //find final pos of currently cycling number
        int finalpos = 0;
        for(int j=i;j<n;j++){
            if(arr[j] < cycle_num){
                finalpos++;
            }
        }

        //put cycle num in final pos if it is not already there
        if(finalpos != cycle_start){
            int tmp = arr[finalpos]; //save next cycle num
            arr[finalpos] = cycle_num;
            cycle_num = tmp;
        }
        else{
            //not a cycle
            break;
        }
        while(1){
        }

    }
}





void bogo_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    std::vector<int> new_arr(n);

    while(1){
        //check sorted
        bool sorted = true;
        for(int i=0;i<n-1;i++){
            bool ifcond = arr[i] > arr[i+1];
            v.displayArrayD(arr, i, i+1, v.read_color);
            if(ifcond){
                sorted = false;
                break;
            }
        }

        if(sorted)break;

        //if not sorted, copy new random array
        new_arr = shuffleArray(arr);

        for(int i=0;i+1<n;i+=2){
            arr[i] = new_arr[i];
            arr[i+1] = new_arr[i+1];
            v.displayArrayD(arr, i, i+1, v.write_color);
        }
        if(n % 2 != 0){
            arr[n-1] = new_arr[n-1];
            v.displayArrayS(arr, n-1, v.write_color);
        }
    }
}

void stalin_sort(Visualizer& v, std::vector<int>& arr){
    int n = arr.size();
    if(n < 2)return;
    for(int i=0;i<n-1;i++){
        bool ifcond = arr[i] > arr[i+1];
        v.displayArrayD(arr, i, i+1, v.read_color);
        if(ifcond){
            arr.erase(arr.begin() + i + 1);
            n--;
            i--;
        }
        v.displayArray(arr);
    }
}



