
#include <stdio.h>  
#include <stdlib.h>  
#include <getopt.h>  
  
static int cnt = 1;  
  
static void print(int optc, int argc, char *argv[], int optind, char *optarg)  
{  
    int i;  
  
    printf("%02d: optc - '%c', argv: ", cnt++, optc);  
    for (i = 0; i < argc; i++) {  
        printf("%s ", argv[i]);  
    }  
    printf("---- *optarg= %s\n", *optarg);
    printf("---- optind = %d\n", optind);  
}  
  
int main(int argc, char *argv[])  
{  
    int optc;  
  
    print('0', argc, argv, optind, optarg);  
  
    while ((optc = getopt(argc, argv, ":ab:c:de::")) != -1) {  
        print(optc, argc, argv, optind, optarg);  
        switch (optc) {  
            default:  
                break;  
        }  
    }  
  
    print('0', argc, argv, optind, optarg);  
  
    exit(EXIT_SUCCESS);  
} 
