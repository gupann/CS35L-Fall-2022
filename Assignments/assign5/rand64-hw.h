#ifndef RAND64_HW_H
#define RAND64_HW_H

extern void hardware_rand64_init (void);
extern unsigned long long hardware_rand64 (void);
extern void hardware_rand64_fini (void);

#endif