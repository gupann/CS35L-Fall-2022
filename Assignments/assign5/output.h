#ifndef OUTPUT_H
#define OUTPUT_H

extern bool writebytes (unsigned long long x, int nbytes);
extern ssize_t writeLineByLine(unsigned long long buf, ssize_t outbytes);

#endif