#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <unistd.h>
#include <ctype.h>
#include <string.h>

#include "options.h"
//./randall 50    // default i and o option used
    //./randall -i rdrand 50    // default o option used
    //./randall -i mrand 50    // default o option used
    //./randall -i /dev/random 50    // default o option used
    //./randall -o stdio 50    // default i option used, effectively same as ./randall 50
    //./randall -o  8 50 // default i option used, effectively prints 50 chars but at 8 bytes at a time, remaineder num of bytes printed after
    //./randall -i input_option -o output_mode 50 // uses input_option specified and output_mode specified to output 50 chars

int get_options(int argc, char **argv, int *input_option, int *output_mode,char *rand_dev_file_name, int *num_char_per_line, int *nbytes)
{
    *num_char_per_line = 0;
    
    if (argc < 2 || argc > 6)
    {
        fprintf(stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
        return 2;
    }
     
    if (argc == 2)
    {
        *input_option = RDRAND;
        *output_mode = STDIO;
        *nbytes = atoi(argv[1]);
        return 0;
    }

    int c;
    while ((c = getopt(argc, argv, "i:o")) != -1) {

        switch(c) {
            case 'i':
                if(strcmp(optarg, "rdrand")==0) {
                    // printf("Option i chosen with input=rdrand.\n");
                    *input_option = RDRAND;
                    *nbytes = atoi(argv[argc-1]);

                }
                else if(strcmp(optarg, "mrand48_r")==0) {
                    // printf("Option i chosen with input=mrand48_r.\n");
                    *input_option = MRAND48_R;
                    *nbytes = atoi(argv[argc-1]);
                }
                else if(optarg[0] == '/'){
                    *input_option = DEV_RAND;
                    strncpy(rand_dev_file_name, optarg, 256);
                    *nbytes = atoi(argv[argc-1]);
                    // printf("Option i chosen, so we will input from file=%s --rand_dev_file_name %s \n", optarg, rand_dev_file_name);
                }
                else{
                    fprintf(stderr, "Wrong input paramemter! Use -i input_option.");
                    return 1;
                }
                break;

            case 'o':
                int postOcount = 0;
                for(; optind < argc; optind++){    
                    postOcount++;
                    // if(argv[optind] == "-o")
                    //     postOcount = 0;
                    // printf("extra arguments at index %d: %s \n", optind, argv[optind]);
                    
                    }
                // printf("post)count: %d ", postOcount); 
                if(postOcount == 2 && (strcmp(argv[argc - 2], "stdio")== 0)) //-o stdio 40
                {
                    *nbytes = atoi(argv[argc-1]);
                    *output_mode = STDIO;

                }
                else if(postOcount == 2) // -o 4 6
                {
                    *nbytes = atoi(argv[argc-1]);
                    *num_char_per_line = atoi(argv[argc-2]);
                    *output_mode = WRITE_CONSOLE;

                }
                else if(postOcount == 1) //-o 4
                {
                    *nbytes = atoi(argv[argc-1]);
                    *output_mode = STDIO;
   
                }
                else{
                    fprintf(stderr, "Error: incorrect output mode selected! Use -i output_mode.");
                    return 1;
                }
                // printf("nbytes is %d and num chars per line is %d ", nbytes, num_char_per_line );
                
                
                // if (atoi(optarg) == -1)
                // {
                //     fprintf(stderr, "No output mode specified.");
                //     return 1;
                // }
                // else if(strcmp(optarg, "stdio")==0) {
                //     printf("Option chosen to send output to standard output.\n");
                //     *output_mode = STDIO;
				// 	*nbytes = atoi(argv[argc-1]);
                // }
                // else {

                    
                    // printf("Option chosen to send output to WRITE\n");
                    // *output_mode = STDIO;
                    // if(isdigit(argv[argc-1]) && isdigit(argv[argc-2]))
                    // {
                    //     *output_mode = WRITE_CONSOLE;
                    //     // *num_char_per_line = atoi(optarg);
                    //     *num_char_per_line = atoi(argv[argc-2]);
                    // }
                    // *nbytes = atoi(argv[argc-1]);
                // }
                break;
            default:
                printf("Error: Unknown option %c with argument %s\n", c, optarg);
                return 1;
            break;
        }
    }
    return 0;
}


int get_options_from_user(int argc, char **argv, int *input_option, int *output_mode, char *dev_file_name, int *num_char_per_line, long long *nbytes)
{
    #if 0
    
    *num_char_per_line = 0;
    char *endptr;
    if (argc < 2 || argc > 6)
    {
        fprintf(stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
        return 2;
    }
    //./randall 50    // default i and o option used
    //./randall -i rdrand 50    // default o option used
    //./randall -i mrand 50    // default o option used
    //./randall -i /dev/random 50    // default o option used
    //./randall -o stdio 50    // default i option used, effectively same as ./randall 50
    //./randall -o  8 50 // default i option used, effectively prints 50 chars but at 8 bytes at a time, remaineder num of bytes printed after
    //./randall -i input_option -o output_mode 50 // uses input_option specified and output_mode specified to output 50 chars 
    if (argc == 2)
    {
        *input_option = RDRAND;
        *output_mode = STDIO;
        *nbytes = strtoll(argv[1], &endptr, 10);
        return 0;
    }

    int c;
    while ((c = getopt(argc, argv, "i:o:")) != -1)
    {
        switch(c) {
            case 'i':
                if(strcmp(optarg, "rdrand")==0) {
                    printf("Option i chosen with input = rdrand.\n");
                    *input_option = RDRAND;
                }
                else if(strcmp(optarg, "mrand48_r")==0) {
                    printf("Option i chosen with input = mrand48_r.\n");
                    *input_option = MRAND48_R;
                }
                else if(optarg[0] == '/'){
                    *input_option = DEV_RAND;
                    strncpy(dev_file_name, optarg, 256);
                    printf("Option i chosen, so we will input from file=%s --dev_file_name %s \n", optarg,dev_file_name);
                }
                else{
                    fprintf(stderr, "Wrong input paramemter! Use -i input_option.");
                    return 1;
                }
                break;

            case 'o':
                if(strcmp(optarg, "stdio")==0) {
                    printf("Option chosen to send output to standard output.\n");
                    *output_mode = STDIO;
                    *nbytes = strtoll(argv[argc - 1], &endptr, 10);
                }
                else if(isdigit(atoi(optarg))) {
                    printf("Option chosen to send output to WRITE with num chars per line %s\n",optarg );
                    *output_mode = WRITE_CONSOLE;
                    *num_char_per_line = atoi(optarg);
                    *nbytes = strtoll(argv[argc - 1], &endptr, 10);
                    if(*num_char_per_line <= 0)
                    {
                        fprintf(stderr, "Error: incorrect number range inputted!");
                        return 1;  
                    }
                }
                else{
                    fprintf(stderr, "Error: incorrect output mode selected! Use -i output_mode.");
                    return 1;
                }
                break;
                
            default:
                printf("Error: Unknown option %c with argument %s\n", c, optarg);
            break;    
        }
        return 0;
    }
    #endif
}