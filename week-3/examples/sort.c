#include<stdio.h>
#include<cs50.h>

int main(void) {
    int numbers[] = {10, 2, 4, 1, 40, 7, 88, 56, 90, 19};
    int len = 10;

    // print numbers before
    printf("Before sort: \n");
    for (int i = 0; i < len; i++) {
        printf("%d ", numbers[i]);
    }

     printf("\n");


     // sort in descending order using selection sort
     int largest = -1, temp = -1, largest_idx = -1, j = -1;

     // get largest number in every iteration
     // swap with number at ith index
     // repeat till end of array
     for (int i = 0; i < len; i++) {
        largest = -1;

        for(j = i; j < len; j++) {

            if(numbers[j] > largest) {
                largest = numbers[j];
                largest_idx = j;
            }

        }
        // swap i and j
        temp = numbers[largest_idx];
        numbers[largest_idx] = numbers[i];
        numbers[i] = largest;
    }

    // print numbers before
    printf("After sort: \n");
    for (int i = 0; i < len; i++) {
        printf("%d ", numbers[i]);
    }

    printf("\n");
}
