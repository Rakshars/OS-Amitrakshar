#include <stdio.h>

void nonpreemptive(int n, int pid[], int at[], int bt[], int pri[]);
void preemptive(int n, int pid[], int at[], int bt[], int pri[]);

int main()
{
    int n, choice;
    int pid[100], at[100], bt[100], pri[100];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter Process ID, Arrival Time, Burst Time and Priority: ");
        scanf("%d %d %d %d", &pid[i], &at[i], &bt[i], &pri[i]);
    }

    printf("Enter the choice:\n1. Non-Preemptive\n2. Preemptive\n");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            nonpreemptive(n, pid, at, bt, pri);
            break;

        case 2:
            preemptive(n, pid, at, bt, pri);
            break;

        default:
            printf("INVALID CHOICE\n");
    }

    return 0;
}



void nonpreemptive(int n, int pid[], int at[], int bt[], int pri[])
{
    int ct[100], tat[100], wt[100];
    int completed[100] = {0};

    int current_time = 0, done = 0;

    while (done < n)
    {
        int idx = -1, min_pri = 9999;

        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && at[i] <= current_time)
            {
                if (pri[i] < min_pri)
                {
                    min_pri = pri[i];
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            ct[idx] = current_time + bt[idx];
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            current_time = ct[idx];
            completed[idx] = 1;
            done++;
        }
        else
        {
            current_time++;
        }
    }

    float awt = 0, atat = 0;

    printf("\nPID\tAT\tBT\tPRI\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], pri[i],
               ct[i], tat[i], wt[i]);

        awt += wt[i];
        atat += tat[i];
    }

    printf("\nAverage WT: %.2f", awt / n);
    printf("\nAverage TAT: %.2f\n", atat / n);
}



void preemptive(int n, int pid[], int at[], int bt[], int pri[])
{
    int ct[100], tat[100], wt[100];
    int rt[100];

    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    int current_time = 0, done = 0;

    while (done < n)
    {
        int idx = -1, min_pri = 9999;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= current_time && rt[i] > 0)
            {
                if (pri[i] < min_pri)
                {
                    min_pri = pri[i];
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            rt[idx]--;
            current_time++;

            if (rt[idx] == 0)
            {
                ct[idx] = current_time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                done++;
            }
        }
        else
        {
            current_time++;
        }
    }

    float awt = 0, atat = 0;

    printf("\nPID\tAT\tBT\tPRI\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], pri[i],
               ct[i], tat[i], wt[i]);

        awt += wt[i];
        atat += tat[i];
    }

    printf("\nAverage WT: %.2f", awt / n);
    printf("\nAverage TAT: %.2f\n", atat / n);
}
