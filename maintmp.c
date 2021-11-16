#include "local.h"

void steps(struct attributes *);
pthread_mutex_t count_mutex[10];

pthread_cond_t count_threshold_cv = PTHREAD_COND_INITIALIZER; // we will connect this condition with an event
int indx[10]={0,0,0,0,0,0,0,0,0,0};

int main(void)
{
    pthread_t technical_emp_threads[10][10];
    int thread_ids[10];
    int thread_ids_tmp[10];
    pthread_t tmp_thread[10];
    FILE *fptr_input;
    struct attributes attrb_Struct[10];
   

    for (int i = 0; i < 3; i++)
    {
        pthread_mutex_init(&count_mutex[i], NULL);
    }
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<read the input file>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    char inp_file_values[31][40];

    if ((fptr_input = fopen(INPUT_FILE, "r")) == NULL)
    {
        perror("INPUT_FILE");
        exit(-1);
    }

    // read the file
    for (int i = 0; i < 4; i++)
    {
        fscanf(fptr_input, "%s\n", inp_file_values[i]);
        printf("inp_file_values[%d] =  %s\n", i, inp_file_values[i]);
    }

    
   

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<creating threads>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    for (int i = 0; i < 3; i++) // lines
    {
         attrb_Struct[i].num_laptops = 0;
        attrb_Struct[i].min_step = atoi(inp_file_values[1]);
        attrb_Struct[i].max_step = atoi(inp_file_values[3]);
        attrb_Struct[i].num_steps = 0;
        attrb_Struct[i].i = i;
      
        
        
        for (int j = 0; j < 10; j++) // each line has 10 technical_emp
        {
           // printf(" attrb_Struct.thread_ID[%d][0] = %d \n",j, attrb_Struct.thread_ID[j]);
            attrb_Struct[i].thread_ID[j] = j;
        //    printf("thread_ids[%d] = %d\n", j, attrb_Struct.thread_ID[j]);
            if (pthread_create(&technical_emp_threads[i][j], NULL, (void *)steps, &attrb_Struct[i]) != 0)
            {
                perror("Failed to create thread");
                return 1;
            }
        }
        sleep(1);
        printf("===============================================================\n");
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (pthread_join(technical_emp_threads[i][j], NULL) != 0)
                return 2;
        }
    }

    return 0;
}



void steps(struct attributes *attrib_strct_fnc)
{
    
    
    
    if (pthread_mutex_lock(&count_mutex[attrib_strct_fnc->i]) == 0)
    {
        printf("Technical employee with ID = %d has started working on step #%d (Line = %i) \n", attrib_strct_fnc->thread_ID[indx[attrib_strct_fnc->i]]+1, attrib_strct_fnc->num_steps + 1,attrib_strct_fnc->i);
        sleep((int)(attrib_strct_fnc->min_step + rand() % attrib_strct_fnc->max_step));
         printf("sleep = %d\n", (int)(attrib_strct_fnc->min_step + rand() % attrib_strct_fnc->max_step));
        attrib_strct_fnc->num_steps = (attrib_strct_fnc->num_steps) + 1;
        

      
            printf("Technical employee with ID = %d has finished working on step #%d (Line = %i) \n",attrib_strct_fnc->thread_ID[indx[attrib_strct_fnc->i]]+1, attrib_strct_fnc->num_steps,attrib_strct_fnc->i);

        if (attrib_strct_fnc->num_steps == 10)
        {
            attrib_strct_fnc->num_laptops++;
           
            printf("Number of laptops = %d For Line (%d) \n", attrib_strct_fnc->num_laptops,attrib_strct_fnc->i);
            attrib_strct_fnc->num_steps = 0;
            indx[attrib_strct_fnc->i] = 0;
           
        }
        indx[attrib_strct_fnc->i]++;
        pthread_mutex_unlock(&count_mutex[attrib_strct_fnc->i]);
    }
    else
    {
        printf("Thread ID = %d didn't lock\n",attrib_strct_fnc->thread_ID[indx[attrib_strct_fnc->i]]+1);
        indx[attrib_strct_fnc->i]++;
        exit(-1);
    }
}