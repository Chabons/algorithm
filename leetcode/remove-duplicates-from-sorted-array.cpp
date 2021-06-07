#include <stdio.h>

template <int N>
int removeDumplicate(int (&a)[N]) {
    int idx = 0;
    for (int i = 1; i < N; ++i) {
        if (a[i] != a[idx]) {
            a[++idx] = a[i];
        }
    }

    return N > 0 ? idx + 1 : 0;
}

int main(int argc, const char **argv) {
    int a[10] = {0,0,1,1,2,2,3,3,4,4};
    int n = removeDumplicate(a);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", a[i]);

    }
    return 0;
}
