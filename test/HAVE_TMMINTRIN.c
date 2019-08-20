#pragma GCC target("ssse3")
#include <tmmintrin.h>

int main()
{
    __m64 x = _mm_abs_pi32(_m_from_int(0));

    return 0;
}