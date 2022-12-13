#ifndef RAND64_SW_H
#define RAND64_SW_H

extern void
software_rand64_init (void);

extern
void software_rand64_file_init (char * s);

extern unsigned long long
software_rand64 (void);

extern void
software_rand64_fini (void);

void mrand48_r_init (char *filename);

long int software_mrand48_r (void);

void mrand48_r_fini (void);

#endif