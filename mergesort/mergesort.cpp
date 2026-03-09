#include <iostream>
#include <omp.h>
#include <random>

#define N 100000
#define M 16

int array[N];
int array_copyspace[N]; // half of that would be enough in theory, but less readable (my opinion)

void fill_array_with_random_numbers(){
    std::random_device rd;  // Hardware-Seed
    std::mt19937 gen(rd()); // Mersenne-Twister Engine
    std::uniform_int_distribution<> distr(1, 100);

    for(int i = 0; i < N; ++i) {
        array[i] = distr(gen);
    }
}

void cout_first_M_elements(){
    std::cout << std::endl << "{";
    for(int i = 0; i < M && i < N; i++){
        std::cout << array[i] << " , ";
    }
    std::cout << std::endl;
}

bool check_if_array_is_sorted(){
    if(N != 0){
        int last_element = array[0];
        int new_element;
        for(int index = 1; index < N; index++){
            new_element = array[index];
            if(new_element < last_element){
                return false;
            }
            last_element = new_element;
        }
    }
    return true;
}

// we assume the memory of arr/arr_copyspace is legal in [start, end)
void merge(int* arr, int* arr_copyspace, int start, int end){
    int mid = start + (end - start) / 2;
    for(int i = start; i < end; i++){
        arr_copyspace[i] = arr[i];
    }

    int index = start;
    int i = start; 
    int j = mid;
    while(i < mid && j < end){
        int lower = arr_copyspace[i];
        int upper = arr_copyspace[j];
        if(lower <= upper){
            arr[index] = lower;
            i++;
        } else {
            arr[index] = upper;
            j++;
        }
        index++;
    }
    while(i < mid){
        arr[index] = arr_copyspace[i];
        i++;
        index++;
    }

    // this second loop is not necessary, but it increases readability (my opinion)
    while(j < end){
        arr[index] = array_copyspace[j];
        j++;
        index++;
    }
}

// we assume the memory of arr/arr_copyspace is legal in [start, end)
void mergesort(int* arr, int* arr_copyspace, int start, int end){
    if(start >= end-1){
        return;
    }

    int mid = start + (end - start) / 2;
    mergesort(arr, arr_copyspace, start, mid);
    mergesort(arr, arr_copyspace, mid, end);
    merge(arr, arr_copyspace, start, end);
}

int main(){
    fill_array_with_random_numbers();
    cout_first_M_elements();

    double time = omp_get_wtime();
    mergesort(array, array_copyspace, 0, N);
    time = omp_get_wtime() - time;

    cout_first_M_elements();

    bool sorted = check_if_array_is_sorted();
    if(sorted){
        std::cout << "The array is sorted." << std::endl;
    } else {
        std::cout << "The array is not sorted." << std::endl;
    }

    std::cout << "The calculation took " << (time * 1000) << " ms to run." << std::endl;
    return 0;
}