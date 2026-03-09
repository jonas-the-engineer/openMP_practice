#include <iostream>
#include <omp.h>
#include <random>

#define N 32

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