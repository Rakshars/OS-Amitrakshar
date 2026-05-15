#include <stdio.h>

#define MAX 10

struct Task {
    int id;
    int execution;
    int period;
    int deadline;
    int remaining;
};

// Function to find GCD
int gcd(int a, int b) {

    if (b == 0)
        return a;

    return gcd(b, a % b);
}

// Function to find LCM
int lcm(int a, int b) {

    return (a * b) / gcd(a, b);
}

// Function to calculate Hyperperiod
int calculateHyperperiod(struct Task t[], int n) {

    int h = t[0].period;

    for (int i = 1; i < n; i++) {
        h = lcm(h, t[i].period);
    }

    return h;
}

// Function to take input
void inputTasks(struct Task t[], int n) {

    printf("\n========== ENTER TASK DETAILS ==========\n");

    for (int i = 0; i < n; i++) {

        t[i].id = i + 1;

        printf("\nTask T%d\n", t[i].id);

        printf("Enter Execution Time : ");
        scanf("%d", &t[i].execution);

        printf("Enter Period Time    : ");
        scanf("%d", &t[i].period);

        printf("Enter Deadline Time  : ");
        scanf("%d", &t[i].deadline);

        t[i].remaining = 0;
    }
}

// Rate Monotonic Scheduling
void RM(struct Task t[], int n, int h) {

    printf("\n\n========== RATE MONOTONIC SCHEDULING ==========\n");

    printf("\nTime\tRunning Task\n");
    printf("-----------------------------\n");

    for (int time = 0; time < h; time++) {

        // Release tasks
        for (int i = 0; i < n; i++) {

            if (time % t[i].period == 0) {
                t[i].remaining = t[i].execution;
            }
        }

        int selected = -1;

        // Select task with smallest period
        for (int i = 0; i < n; i++) {

            if (t[i].remaining > 0 &&
               (selected == -1 ||
                t[i].period < t[selected].period)) {

                selected = i;
            }
        }

        // Execute selected task
        if (selected != -1) {

            printf("%d\tT%d\n", time, t[selected].id);

            t[selected].remaining--;
        }
        else {

            printf("%d\tIDLE\n", time);
        }
    }
}

// Earliest Deadline First Scheduling
void EDF(struct Task t[], int n, int h) {

    printf("\n\n========== EARLIEST DEADLINE FIRST ==========\n");

    int dynamicDeadline[MAX];

    printf("\nTime\tRunning Task\n");
    printf("-----------------------------\n");

    // Initialize deadlines
    for (int i = 0; i < n; i++) {
        dynamicDeadline[i] = t[i].deadline;
    }

    for (int time = 0; time < h; time++) {

        // Release tasks
        for (int i = 0; i < n; i++) {

            if (time % t[i].period == 0) {

                t[i].remaining = t[i].execution;

                dynamicDeadline[i] = time + t[i].deadline;
            }
        }

        int selected = -1;

        // Select task with earliest deadline
        for (int i = 0; i < n; i++) {

            if (t[i].remaining > 0 &&
               (selected == -1 ||
                dynamicDeadline[i] < dynamicDeadline[selected])) {

                selected = i;
            }
        }

        // Execute selected task
        if (selected != -1) {

            printf("%d\tT%d\n", time, t[selected].id);

            t[selected].remaining--;
        }
        else {

            printf("%d\tIDLE\n", time);
        }
    }
}

// Main Function
int main() {

    int n;

    printf("Enter Number of Tasks: ");
    scanf("%d", &n);

    struct Task t[MAX];

    inputTasks(t, n);

    int hyperperiod = calculateHyperperiod(t, n);

    printf("\nCalculated Hyperperiod = %d\n", hyperperiod);

    RM(t, n, hyperperiod);

    EDF(t, n, hyperperiod);

    return 0;
}
