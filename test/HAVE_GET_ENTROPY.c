#include <stdlib.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#ifdef HAVE_SYS_RANDOM_H
# include <sys/random.h>
#endif

int main()
{
    #ifdef __APPLE__
    # error getentropy() is currently disabled on Apple operating systems
    #endif

    unsigned char buf;
    (void) getentropy((void *) &buf, 1U);
}