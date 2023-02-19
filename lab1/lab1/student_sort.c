#include "sort-harness.h"
#include <immintrin.h>
#include <x86intrin.h>

/*
void compare(float a[], int i, int j, int direction) {
  if ( (a[i] > a[j] && direction == 1) || 
      (a[i] < a[j] && direction == 0)) {
        float temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
}
*/


void bitonic_merge(float a[], float low, int count, int direction) {
  if(count > 1) {
    int k = count/2;
    _m128 k4 = _mm_set1_ps(k);
    int end_loop = 0;
    for(int i = low; i<low+k; i+=4) {

      // compare and swap
      _m128 low4 = _mm_set1_ps(i);
      _m128 first_half_element4 = _mm_loadu_ps(&a[i]);
      _m128 second_half_element4 = _mm_loadu_ps(&a[i+k]);

      _m128 compare_lower4 = _mm_cmplt_ps(first_half_element4, second_half_element4);
      _m128 compare_higher4 = _mm_cmplt_ps(second_half_element4, first_half_element4);
      int mask1 = _mm_movemask(compare_lower4);
      int mask2 = _mm_movemask(compare_higher4);

      if( ( direction == 1 && mask2 == -1) || (direction == 0 && mask1 == -1)) {
        // swap
        _m128 temp4 = first_half_element4;
        _mm_storeu_ps(&(a[i]), second_half_element4);
        _mm_storeu_ps(&(a[i+k]), temp4);
      }
      
    }
    bitonic_merge(a, low, k, direction);
    bitonic_merge(a, low+k, k, direction);
  }
}

void bitonic_sort(float a[], float low, int count, int direction) {
  if(count > 1) {
    int k = count/2;

    bitonic_sort(a, low, k, 1);

    bitonic_sort(a, low+k, k, 0);

    bitonic_merge(a, low, count, direction);
  }
}

void student_sort(float a[], int size) {
      int size = sizeof(a) / sizeof(a[0]);
      bitonic_sort(a, )
      //david_sort(a, size);
    }
  
