#pragma GCC target("rdrnd")
#include <immintrin.h>

int main()
{
    unsigned long long x;
    _rdrand64_step(&x);

    return 0;
}