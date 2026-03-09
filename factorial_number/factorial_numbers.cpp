#include <iostream>
#include <omp.h>

#define N 33

int fac_array[N];

int fac(int n){
    if(n == 0 || n == 1){
        return 1;
    }
    return n * fac(n-1);
}

int main(){
    double time = omp_get_wtime();

    // factorial calculation
    for(int i = 0; i < N; i++){
        fac_array[i] = fac(i);
    }

    time = omp_get_wtime() - time;

    // factorial output
    for(int i = 0; i < N; i++){
        std::cout << "fac(" << i << ") = " << fac_array[i] << std::endl;
    }

    std::cout << "The calculation took " << (time * 1000) << " ms to run." << std::endl;
    return 0;
}