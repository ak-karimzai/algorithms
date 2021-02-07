#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int profit;
    int deadline;
} details;

typedef struct
{
    details *arr;
    int *done_time;
    int num_of_jobs;
    int max_time;
} job;

enum error_code
{
    ok,
    error
};

void input_jobs(job *jobs)
{
    jobs->max_time = 0;
    for (int i = 0; i < jobs->num_of_jobs; i++)
    {
        if (fscanf(stdin, "%d %d", &jobs->arr[i].profit, &jobs->arr[i].deadline) != 2 || jobs->arr[i].deadline <= 0 || jobs->arr[i].profit <= 0)
        {
            puts("incorrect input: try again!");
            i--;
            continue;
        }
        if (jobs->arr[i].deadline > jobs->max_time)
            jobs->max_time = jobs->arr[i].deadline;
    }
    if (jobs->max_time)
        jobs->done_time = calloc(jobs->max_time, sizeof(int));
}

void find_job_done_with_hours(job *jobs)
{
    for (int i = 0; i < jobs->num_of_jobs; i++)
    {
        if (jobs->done_time[jobs->arr[i].deadline - 1] == 0)
            jobs->done_time[jobs->arr[i].deadline - 1] = jobs->arr[i].profit;
        else if (jobs->done_time[jobs->arr[i].deadline - 1] < jobs->arr[i].profit)
            jobs->done_time[jobs->arr[i].deadline - 1] = jobs->arr[i].profit;
        else if (jobs->arr[i].deadline - 2 >= 0)
        {
            for (int j = jobs->arr[i].deadline - 2; j >= 0; j--)
            {
                if (jobs->done_time[j] == 0)
                {
                    jobs->done_time[j] = jobs->arr[i].profit;
                    break;
                }
                else if (jobs->done_time[j] < jobs->arr[i].profit)
                {
                    jobs->done_time[j] = jobs->arr[i].profit;
                    break;
                }
            }
        }
    }
}

void print_doned_job(job *jobs)
{
    for (int i = 0; i < jobs->max_time; i++)
        printf("Hour[%d] job with profit [%d]\n", i + 1, jobs->done_time[i]);
}

int main()
{
    int n, rc = ok;
    if (fscanf(stdin, "%d", &n) == 1 && n > 0)
    {
        job *jobs = malloc(sizeof(job));
        if (jobs)
        {
            jobs->num_of_jobs = n;
            jobs->arr = malloc(n * sizeof(details));
            if (jobs->arr)
            {
                input_jobs(jobs);
                find_job_done_with_hours(jobs);
                print_doned_job(jobs);
                free(jobs->arr);
                free(jobs->done_time);
            }
            else
            {
                puts("m-alloc error");
                rc = error;
            }
            free(jobs);
        }
        else
        {
            puts("m-alloc error");
            rc = error;
        }
    }
    return rc;
}