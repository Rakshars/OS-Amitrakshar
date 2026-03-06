#include <stdio.h>

int main() {
    int n, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], CT[n], TAT[n], WT[n], PID[n];

    for(i = 0; i < n; i++) {
        PID[i] = i + 1;
        printf("\nProcess %d\n", PID[i]);

        printf("Enter Arrival Time: ");
        scanf("%d", &AT[i]);

        printf("Enter Burst Time: ");
        scanf("%d", &BT[i]);
    }

    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(AT[i] > AT[j]) {

                int temp;

                temp = AT[i];
                AT[i] = AT[j];
                AT[j] = temp;

                temp = BT[i];
                BT[i] = BT[j];
                BT[j] = temp;

                temp = PID[i];
                PID[i] = PID[j];
                PID[j] = temp;
            }
        }
    }

    int current_time = 0;
    float totalWT = 0, totalTAT = 0;

    for(i = 0; i < n; i++) {

        if(current_time < AT[i]) {
            current_time = AT[i];
        }

        CT[i] = current_time + BT[i];
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];

        current_time = CT[i];

        totalWT += WT[i];
        totalTAT += TAT[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               PID[i], AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
