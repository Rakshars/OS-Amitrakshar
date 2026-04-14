#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

// FCFS using CT → TAT → WT
void fcfs(struct Process p[], int n, int start_time) {
    int i;
    int current_time = start_time;

    for (i = 0; i < n; i++) {

        // Handle idle CPU
        if (current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }

        // Completion Time
        current_time += p[i].burst_time;
        p[i].completion_time = current_time;

        // Turnaround Time
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;

        // Waiting Time
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    }
}

// Display
void display(struct Process p[], int n, char name[]) {
    int i;
    float total_wt = 0, total_tat = 0;

    printf("\n%s Queue:\n", name);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].completion_time,
               p[i].turnaround_time,
               p[i].waiting_time);

        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }

    printf("Average WT = %.2f\n", total_wt / n);
    printf("Average TAT = %.2f\n", total_tat / n);
}

int main() {
    int n_sys, n_user, i;
    int system_end_time;

    // System processes
    printf("Enter number of System Processes: ");
    scanf("%d", &n_sys);

    struct Process sys[n_sys];

    for (i = 0; i < n_sys; i++) {
        sys[i].id = i + 1;
        printf("\nSystem Process P%d\n", sys[i].id);
        printf("Enter Arrival Time: ");
        scanf("%d", &sys[i].arrival_time);
        printf("Enter Burst Time: ");
        scanf("%d", &sys[i].burst_time);
    }

    // User processes
    printf("\nEnter number of User Processes: ");
    scanf("%d", &n_user);

    struct Process user[n_user];

    for (i = 0; i < n_user; i++) {
        user[i].id = i + 1;
        printf("\nUser Process P%d\n", user[i].id);
        printf("Enter Arrival Time: ");
        scanf("%d", &user[i].arrival_time);
        printf("Enter Burst Time: ");
        scanf("%d", &user[i].burst_time);
    }

    // Execute system queue
    fcfs(sys, n_sys, 0);

    // Get system completion time
    system_end_time = sys[n_sys - 1].completion_time;

    // Execute user queue after system finishes
    fcfs(user, n_user, system_end_time);

    // Display
    display(sys, n_sys, "System (High Priority)");
    display(user, n_user, "User (Low Priority)");

    return 0;
}
