#ifndef __LOCAL_H__
#define __LOCAL_H__

// 1180414 Yazan Daibes
// 1181557 Kareen Karam
// 1180424 Omar Qattosh

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h> // for EBSY
#include <unistd.h>

#define ORIGINAL "\x1B[0m"
#define RED_COLOR "\x1B[31m"
#define GREEN_COLOR "\x1B[32m"
#define YELLOW_COLOR "\x1B[33m"
#define BLUE_COLOR "\x1B[34m"
#define PURPLE_COLOR "\x1B[35m"
#define CYAN_COLOR "\x1B[36m"
#define WHITE_COLOR "\x1B[37m"

#define INPUT_FILE "./input.txt"

struct attributes
{
    int min_step;
    int max_step;
    int num_steps;
    int thread_ID[10];
    int num_laptops;
    
    int i;
};

#endif