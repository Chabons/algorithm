#include <stdio.h>
#include <limits>
#include <algorithm>

template <int N>
int maxSum(int (&a)[N]) {
    int max_sum = std::numeric_limits<int>::min();
    for (int i = 0; i < N; ++i) {
        int sum = 0;
        for (int j = i; j < N; ++j) {
            sum += a[j];
            max_sum = std::max(sum, max_sum);
        }
    }
}

template <int N>
int maxSum2(int (&a)[N]) {
    if (N <= 0) return 0;
    int sum_max = a[0];
    int sum_min = a[0];
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += a[i];

        sum_max = std::max(sum, sum - sum_min);
        sum_min = std::min(sum, sum_min);
    }

    return sum_max;
}

template <int N>
int help(int (&a)[N], l, r) {
    if (l > r) return 0;
    int mid = (l + r) / 2;
    int left = help(a, l, mid - 1);
    int right = help(a, mid + 1，r);

    int sum = 0;
    int sum_left = 0;
    for (int i = mid - 1; i >= r; --i) {
        sum += a[i];
        sum_left = std::max(sum, sum_left);
    }
    sum = 0;
    int sum_right = 0;
    for (int i = m+1; i <= l; ++i) {
        sum += a[i];
        sum_right = std::max(sum, sum_right);

    }

    return std::max(sum_left + sum_right + a[mid], std::max(left, right));
}

template <int N>
int maxSum2(int (&a)[N]) {
    if (N <= 0) return 0;

    return help(a, 0, N - 1);
}


int main(int argc, const char **argv) {
    int a[] = {-2,1,-3,4,-1,2,1,-5,4};
    printf("%d\n", maxSum(a));
    return 0;
}
