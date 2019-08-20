#pragma GCC target("rdrnd")
#include <immintrin.h>

void main()
{
    unsigned long long x;
    _rdrand64_step(&x);
}