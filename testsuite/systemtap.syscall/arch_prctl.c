/* COVERAGE: arch_prctl */

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

#ifdef __NR_arch_prctl

#include <asm/prctl.h>
#include <sys/prctl.h>

// This decl is missing from glibc; it's a deprecated syscall.
#define arch_prctl(x,y) syscall(__NR_arch_prctl,x,y)

int main()
{
    unsigned long fs;
    arch_prctl(ARCH_GET_FS, &fs);
    //staptest// arch_prctl (ARCH_GET_FS, XXXX) = 0

    arch_prctl(-1, &fs);
    //staptest// arch_prctl (-1, XXXX) = NNNN (EINVAL)

    // 2 variants: one for get- and one for set- cmds:
    // int arch_prctl(int code, unsigned long addr);
    // int arch_prctl(int code, unsigned long *addr);

    // Also the syscall is x86_64 specific, so __WORDSIZE == 64.

    arch_prctl(0, (unsigned long *)-1);
    //staptest// arch_prctl (0, 18446744073709551615) = NNNN (EINVAL)

    arch_prctl(0, (unsigned long)-1);
    //staptest// arch_prctl (0, 18446744073709551615) = NNNN (EINVAL)

    return 0;
}
#else
int main()
{
    return 0;
}
#endif
