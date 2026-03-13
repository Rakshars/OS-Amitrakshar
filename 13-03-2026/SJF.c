#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int remaining_bt;
    int completed;
};

void nonPreemptive(struct Process p[], int n) {
    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    while (completed < n) {
        int idx = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].completed == 0) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            current_time += p[idx].bt;
            p[idx].ct = current_time;

            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].completed = 1;
            completed++;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
        }
        else {
            current_time++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

void preemptive(struct Process p[], int n) {
    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
        p[i].remaining_bt = p[i].bt;

    while (completed < n) {
        int idx = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].remaining_bt > 0) {
                if (p[i].remaining_bt < min_bt) {
                    min_bt = p[i].remaining_bt;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].remaining_bt--;
            current_time++;

            if (p[idx].remaining_bt == 0) {
                p[idx].ct = current_time;

                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                total_wt += p[idx].wt;
                total_tat += p[idx].tat;

                completed++;
            }
        }
        else {
            current_time++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

int main() {

    int n, choice;
    struct Process p[50];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess P%d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        p[i].completed = 0;
    }

    printf("\nCPU Scheduling Menu\n");
    printf("1. SJF Non Preemptive\n");
    printf("2. SJF Preemptive (SRTF)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {

        case 1:
            nonPreemptive(p, n);
            break;

        case 2:
            preemptive(p, n);
            break;

        default:
            printf("Invalid choice\n");
    }

    return 0;
}
