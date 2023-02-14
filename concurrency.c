#include <stdio.h>

void bitonic(int arr[], int n) {
    for(int k = 2; k <=n; k*=2) { // k is doubled every iteration
        for(int j = k/2; j>0; j/=2) { // j is halved at every iteration, with truncation of fractional parts
            for(int i = 0; i<n; i++) {
                int l = i ^ j;
                if(l > i) {
                    if(  ( (i & k) == 0 && (arr[i] > arr[l]) ) 
                    || (i & k) != 0 && (arr[i] < arr[l]) ) {
                        int temp = arr[i];
                        arr[i] = arr[l];
                        arr[l] = temp;
                    }
                }
            }
        }
    }
}

int main()
{
    int arr[] = { 2, 4, 5, 3, 1 , 1, 2, 10, 123, 41, 32, 123, 512, 19, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
  
    
    bitonic(arr, n);
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
