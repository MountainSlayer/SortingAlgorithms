//Purpose: Implementing quicksort
//Quicksort is an unstable sort (the relative ordering of
//items with the same value is not preserved)
//Time complexity: O(n * h) where h is the height of the
//recursion tree. In the best and the average case, time
//complexity is O(nlogn). This happens when the pivot
//chosen in each step is close to the middle position
//in the array. The worst case time complexity is O(n^2)
//and happens when the pivot chosen in each step is
//either at the start or the end position of the array.
//But this case is very rare since the biggest or the
//smallest element would have to be selected in each step.
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void swap(int A[], int pos_1, int pos_2){
    int temp = A[pos_1];
    A[pos_1] = A[pos_2];
    A[pos_2] = temp;
}

int partition(int A[], int low, int high, int pivot){
    int final_pivot;
    //swap pivot with low
    swap(A, low, pivot);
    int left = low + 1;
    int right = high;
    while(left < right){
        //move left until we find a value > pivot value
        //remember that we put the pivot value in A[low]
        while(left < right && A[left] <= A[low]){
            left ++;
        }
        //move right until we find a value < pivot value
        while(left < right && A[right] >= A[low]){
            right --;
        }
        //swap values so that they are in the correct side
        //of the pivot
        swap(A, left, right);
    }
    if(A[right] <= A[low]){
        final_pivot = right;
    }
    else{
        final_pivot = right - 1;
    }
    swap(A, low, final_pivot);
    //return the new pivot position since it may have changed
    return final_pivot;
}

void quicksort_helper(int A[], int low, int high){
    if(low < high){
        srand(time(NULL));                              //initialize a random seed
        int pivot = rand() % (high - low + 1) + low;    //generate a random from low to high inclusive
        pivot = partition(A, low, high, pivot);
        quicksort_helper(A, low, pivot - 1);
        quicksort_helper(A, pivot + 1, high);
    }
}

void quicksort(int A[], int length){
    quicksort_helper(A, 0, length - 1);
}

void print_list(int A[], int length){
    for(int i = 0; i < length; i ++){
        cout << A[i] << " ";
    }
    cout << endl;
}

int main(){
    int A[] = { 4, 5, 7, 1, 8, 10, -2, 4, 1, 11 };
    int length = 10;
    print_list(A, length);
    quicksort(A, length);
    print_list(A, length);
    return 0;
}
