/* COVERAGE: getrlimit old_getrlimit setrlimit */
/* 'old_getrlimit' isn't a separate syscall from 'getrlimit'. On some
 * platforms (like i386), getrlimit is implemented via
 * old_getrlimit. */

#include <sys/time.h>
#include <sys/resource.h>

struct rlimit rlim;

int main()
{

    // --- first try out normal operation ---

    getrlimit(RLIMIT_CPU, &rlim);
    //staptest// getrlimit (RLIMIT_CPU, XXXX) = 0

    setrlimit(RLIMIT_CPU, &rlim);
    //staptest// setrlimit (RLIMIT_CPU, \[NNNN,NNNN\]) = 0

    // --- then check nasty calls ---

    getrlimit(-1, &rlim);
    //staptest// getrlimit (RLIM_INFINITY, XXXX) = NNNN (EINVAL)

    getrlimit(-15, &rlim);
    //staptest// getrlimit (0xfffffff1, XXXX) = NNNN (EINVAL)

    getrlimit(RLIMIT_CPU, (struct rlimit *)-1);
#ifdef __s390__
    //staptest// getrlimit (RLIMIT_CPU, 0x[7]?[f]+) = NNNN (EFAULT)
#else
    //staptest// getrlimit (RLIMIT_CPU, 0x[f]+) = NNNN (EFAULT)
#endif

    setrlimit(-1, &rlim);
    //staptest// setrlimit (RLIM_INFINITY, \[NNNN,NNNN\]) = NNNN (EINVAL)

    setrlimit(RLIMIT_CPU, (const struct rlimit *)-1);
#ifdef __s390__
    //staptest// setrlimit (RLIMIT_CPU, 0x[7]?[f]+) = NNNN (EFAULT)
#else
    //staptest// setrlimit (RLIMIT_CPU, 0x[f]+) = NNNN (EFAULT)
#endif

    return 0;
}
