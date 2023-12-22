/*
    C program to call ARMv7 assembly subroutines
    that uses floating-point operations

    output for this data

      hw = 90.2, exam 1 =  90, exam 2 =  60; grade needed = 134.72
      hw = 90.2, exam 1 =  90, exam 2 =  80; grade needed = 104.72
      hw = 90.2, exam 1 = 100, exam 2 = 100; grade needed =  62.22
*/

#include <stdio.h>
#include <inttypes.h>

float floatAvg(float *hw, int n);
// given array of floats and the length of the array
// returns the average of the elements


float exam3Agrade(float hw, int32_t exam1, int32_t exam2);
// given homework average, exam 1, and exam 2
// return grade needed on final exam to receive an
//   overall course grade of 90 (could exceed 100)
// overall = 25%(hw_avg) + 25%(e1) + 30%(e2) + 20%(final)


int main(void) {
    float hw[] = {85.3, 90.5, 95.1, 85.2, 95};
    float final, hwAvg;

    int32_t g[][3] = {{ 85,  90,  60},  
                  { 95,  90,  80},
                  {100, 100, 100}};
    int32_t e1, e2;
    int i, rows, n;

    rows = sizeof(g)/sizeof(g[0]);
    n = sizeof(hw)/sizeof(hw[0]);
    hwAvg = floatAvg(hw, n);

    for(i = 0; i < rows; i++) {
        e1 = g[i][1];  e2 = g[i][2];
        final = exam3Agrade(hwAvg, e1, e2);
        printf("hw = %.1f, exam 1 = %3d, exam 2 = %3d; ", hwAvg, e1, e2);
        printf("grade needed = %6.2f\n", final);
    }
}

