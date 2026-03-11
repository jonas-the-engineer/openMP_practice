#include <iostream>
#include <omp.h>
#include <random>

#define N 10

int array[N];
int array_copyspace[N]; // half of that would be enough in theory, but less readable (my opinion)

void fill_array_with_random_numbers(){
    std::random_device rd;  // Hardware-Seed
    std::mt19937 gen(rd()); // Mersenne-Twister Engine
    std::uniform_int_distribution<> distr(1, 10000);

    for(int i = 0; i < N; ++i) {
        array[i] = distr(gen);
    }
}

#define M 32

void cout_first_M_elements(){
    std::cout << std::endl << "{";
    for(int i = 0; i < M && i < N; i++){
        std::cout << array[i] << " , ";
    }
    std::cout << std::endl;
}

bool check_if_array_is_sorted_parallel_for(){
    if(N == 0){
        return true;
    }
    bool sorted = true;

    #pragma omp parallel for default(none) shared(array) reduction(&&: sorted)
    for(int curr = 1; curr < N; curr++){
        int last = curr - 1;
        sorted = sorted && (array[curr] >= array[last]);
    }

    return sorted;
}

bool check_if_array_is_sorted_parallel(){
    if(N == 0){
        return true;
    }
    bool sorted = true;
    int num_threads_global;

    #pragma omp parallel default(none) shared(array, num_threads_global) reduction(&&: sorted)
    {
        int id = omp_get_thread_num();
        if(id == 0){
            num_threads_global = omp_get_num_threads();
        }
        #pragma omp barrier

        int num_threads = num_threads_global;
        int interval_length = N / num_threads;
        int start = interval_length * id;
        int end_inclusive = start + interval_length - 1;
        if(id == num_threads - 1){
            end_inclusive = N - 1;
        }

        // I divide the work into intervals and boundaries to 
        // practice splitting work up this way, because this 
        // style is used to solve differential equations

        // check all intervals
        for(int i = start; i < end_inclusive; i++){
            int curr = i;
            int next = i + 1;
            sorted = sorted && (array[curr] <= array[next]);
        }

        // check all boundaries
        #pragma omp barrier
        #pragma omp single
        {
            for(int left = interval_length - 1; left < (N-1); left += interval_length){
                int right = left + 1;
                sorted = sorted && (array[left] <= array[right]);
            }
        }
    }

    return sorted;
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