#include <stdlib.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#ifdef HAVE_SYS_RANDOM_H
# include <sys/random.h>
#endif

int main()
{
    unsigned char buf;
    (void) getrandom((void *) &buf, 1U, 0U);
}