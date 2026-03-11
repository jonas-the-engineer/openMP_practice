#include "../fill_array.cpp"

void bubblesort(int *arr, int size){
    // start and left for left element (comparater needs 2 input elements)
    int end = size - 2;
    for(int start = 0; start < (size-1); start++){
        for(int left = end; left >= start; left--){
            int right = left + 1;
            if(arr[left] > arr[right]){
                int left_copy = arr[left];
                arr[left] = arr[right];
                arr[right] = left_copy;
            }
        }
    }
}


int main(){
    fill_array_with_random_numbers();
    cout_first_M_elements();

    bool sorted = check_if_array_is_sorted_parallel_for();
    if(sorted){
        std::cout << "The array is sorted." << std::endl;
    } else {
        std::cout << "The array is not sorted." << std::endl;
    }

    double time = omp_get_wtime();
    bubblesort(array, N);
    time = omp_get_wtime() - time;

    cout_first_M_elements();

    sorted = check_if_array_is_sorted_parallel_for();
    if(sorted){
        std::cout << "The array is sorted." << std::endl;
    } else {
        std::cout << "The array is not sorted." << std::endl;
    }

    std::cout << "The calculation took " << (time * 1000) << " ms to run." << std::endl;
    return 0;
}