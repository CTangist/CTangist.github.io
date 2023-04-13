#include <iostream>

using namespace std;

int* listMul(int a[], int b[], int length) {
    int *c = new int[length];
    for (int i=0; i<length; ++i) {
        c[i] = a[i] * b[i];
    }

    return c;
}

int main() {
    int a[1000000], b[1000000] = {0};
    int length = sizeof(a)/sizeof(a[0]);
    for (int i=0; i<length; ++i) {
        a[i] = b[i] = i;
    }

    clock_t start_time=clock();
    int *c = listMul(a, b, length);
    clock_t end_time=clock();
    delete[] c;
    cout << "The run time is: " <<(double)(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;

    return 0;
}