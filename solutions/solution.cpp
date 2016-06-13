#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

int const n = 5000;
int const k = 2000;
int const x =  100;

int main (void) {
    mt19937 gen (12345);
    uniform_int_distribution <> one_bit (0, 1);
    char buf[n];
    int res;

    for (int attempt = 0; attempt < x; attempt++) {
        for (int position = 0; position < n; position++) {
            buf[position] = '0' + one_bit (gen);
        }
        printf("%s\n", buf);
        fflush(stdout);
        scanf("%d", &res);
    }
    return 0;
}
