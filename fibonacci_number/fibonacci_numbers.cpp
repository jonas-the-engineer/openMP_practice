#include <iostream>
#include <omp.h>

#define N 42

int fib_array[N];

int fib(int n){
    if(n == 0 || n == 1){
        return n;
    }
    return fib(n-1) + fib(n-2);
}

int main(){
    double time = omp_get_wtime();

    // fibonacci calculation
    for(int i = 0; i < N; i++){
        fib_array[i] = fib(i);
    }

    time = omp_get_wtime() - time;

    // fibonacci output
    for(int i = 0; i < N; i++){
        std::cout << "fib(" << i << ") = " << fib_array[i] << std::endl;
    }

    std::cout << "The calculation took " << (time * 1000) << " ms to run." << std::endl;
    return 0;
}