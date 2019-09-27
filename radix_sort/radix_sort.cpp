#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <int N>
int max_bit(int(&data)[N]) {
    int hight = 10;
    int bit = 1;
    for (int i = 0; i < N; ++i) {
        while(data[i] >= hight) {
            ++bit;
            hight *= 10;
        }
    }

    return bit;
}

template <int N>
void radix_sort_LSD(int(&data)[N], int bit) {
    if (bit <= 0) return;
    int count[10] = {0};
    int tmp[N] = {0};
    int radix = 1;

    for (int i = 1; i <= bit; ++i) {
        memset(count, 0x00, 10 * sizeof(int));

        for (int j = 0; j < N; ++j) {
            int mod = (data[j] / radix) % 10;
            ++(count[mod]);
        }
        for (int j = 1; j < 10; ++j) {
            count[j] += count[j - 1];
        }
        for (int j = N - 1; j >= 0; --j) {
            int mod = (data[j] / radix) % 10;
            tmp[count[mod] - 1] = data[j];
            --(count[mod]);
        }
        for (int  j = 0; j < N; ++j) {
            data[j] = tmp[j];
        }

        radix *= 10;
    }
}



int main(int argc, const char **argv) {
    int array[6] = {100, 300, 2, 102, 3, 101};
    int bit = max_bit(array);
    radix_sort_LSD(array, bit);
    for (int i = 0; i < 6; ++i) {
        printf("%d\n", array[i]);
    }

    return 0;
}
