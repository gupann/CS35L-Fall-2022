#ifndef CHECKCPU_H
#define CHECKCPU_H

/* Description of the current CPU.  */
struct cpuid { unsigned eax, ebx, ecx, edx; };

extern _Bool
rdrand_supported (void);

#endif