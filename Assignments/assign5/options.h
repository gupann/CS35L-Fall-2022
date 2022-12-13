#ifndef OPTIONS_H
#define OPTIONS_H


enum INPUT_OPT {RDRAND  = 1, MRAND48_R  = 2, DEV_RAND =3};
enum OUTPUT_OPT {STDIO  = 1, WRITE_CONSOLE = 2};

extern int get_options_from_user(int argc, char **argv, int *input_option, int *output_mode,char *dev_file_name, int *num_char_per_line, long long *nBytes);
int get_options(int argc, char **argv, int *input_option, int *output_mode,char *rand_dev_file_name, int *num_char_per_line, int *nbytes);

#endif