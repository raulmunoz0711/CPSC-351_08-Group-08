#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Cross platform
#ifdef _WIN32
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define sleep_ms(ms) usleep((ms) * 1000)
#endif

typedef struct {
    char id[20];
    char tag[10];       // [Member] or [VIP]
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    bool isCompleted;
} Player;
 
void resetPlayers(Player p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].completionTime = 0;
        p[i].waitingTime = 0;
        p[i].turnaroundTime = 0;
        p[i].isCompleted = false;
    }
}
 
// Server time 00:00 start
void printTime(int seconds) {
    printf("%02d:%02d", seconds / 60, seconds % 60);
}
 
// Show arrival time
void showArrivals(Player p[], int n) {
    printf("Server started at 00:00\n\n");
    sleep_ms(800);
 
    for (int i = 0; i < n; i++) {
        printf("  ");
        printTime(p[i].arrivalTime);
        printf("  %s %s has joined the server queue\n", p[i].id, p[i].tag);
        sleep_ms(900);
    }
}
 
// FCFS algo
void runFCFS(Player p[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrivalTime) currentTime = p[i].arrivalTime;
        p[i].completionTime = currentTime + p[i].burstTime;
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime    = p[i].turnaroundTime - p[i].burstTime;
        currentTime = p[i].completionTime;
    }
}
 
// SJF algo
void runSJF(Player p[], int n) {
    int currentTime = 0, completed = 0;
    while (completed < n) {
        int bestIdx = -1, minBurst = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && !p[i].isCompleted) {
                if (p[i].burstTime < minBurst) {
                    minBurst = p[i].burstTime;
                    bestIdx = i;
                }
            }
        }
        if (bestIdx == -1) { currentTime++; continue; }
        p[bestIdx].completionTime = currentTime + p[bestIdx].burstTime;
        p[bestIdx].turnaroundTime = p[bestIdx].completionTime - p[bestIdx].arrivalTime;
        p[bestIdx].waitingTime    = p[bestIdx].turnaroundTime - p[bestIdx].burstTime;
        p[bestIdx].isCompleted    = true;
        completed++;
        currentTime = p[bestIdx].completionTime;
    }
}
 
// Prio Search Algo
void runPriority(Player p[], int n) {
    int currentTime = 0, completed = 0;
    while (completed < n) {
        int bestIdx = -1, highestPrio = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && !p[i].isCompleted) {
                if (p[i].priority < highestPrio) {
                    highestPrio = p[i].priority;
                    bestIdx = i;
                } else if (p[i].priority == highestPrio) {
                    if (bestIdx == -1 || p[i].arrivalTime < p[bestIdx].arrivalTime)
                        bestIdx = i;
                }
            }
        }
        if (bestIdx == -1) { currentTime++; continue; }
        p[bestIdx].completionTime = currentTime + p[bestIdx].burstTime;
        p[bestIdx].turnaroundTime = p[bestIdx].completionTime - p[bestIdx].arrivalTime;
        p[bestIdx].waitingTime    = p[bestIdx].turnaroundTime - p[bestIdx].burstTime;
        p[bestIdx].isCompleted    = true;
        completed++;
        currentTime = p[bestIdx].completionTime;
    }
}
 
// Print results after algorithm runs
void showResults(Player p[], int n, char* algoName) {
    float totalWT = 0, totalTAT = 0, totalCT = 0;
 
    printf("\n--- %s ---\n\n", algoName);
    sleep_ms(400);
 
    for (int i = 0; i < n; i++) {
        printf("  ");
        printTime(p[i].completionTime);
        printf("  %s %s left after waiting %ds (server processed in %ds)\n",
               p[i].id, p[i].tag, p[i].waitingTime, p[i].burstTime);
        totalWT  += p[i].waitingTime;
        totalTAT += p[i].turnaroundTime;
        totalCT  += p[i].completionTime;
        sleep_ms(700);
    }
 
    printf("\n  Avg Wait Time: %.1fs  |  Avg Turnaround Time: %.1fs  |  Avg Completion Time: %.1fs\n",
           totalWT / n, totalTAT / n, totalCT / n);
}
 
int main() {
    Player players[] = {
        {"User1", "[Member]", 0,  6, 2},
        {"User2", "[Member]", 1,  3, 2},
        {"User3", "[VIP]",    2,  5, 1},
        {"User4", "[Member]", 4,  1, 2},
        {"User5", "[VIP]",    6,  4, 1}
    };
    int n = 5;
 
    // Show arrivals once
    showArrivals(players, n);
 
    printf("\n\nPress Enter to run simulations...");
    getchar();
 
    // FCFS
    runFCFS(players, n);
    showResults(players, n, "First Come First Serve");
    resetPlayers(players, n);
 
    printf("\nPress Enter for next algorithm...");
    getchar();
 
    // SJF
    runSJF(players, n);
    showResults(players, n, "Shortest Job First");
    resetPlayers(players, n);
 
    printf("\nPress Enter for next algorithm...");
    getchar();
 
    // Priority
    runPriority(players, n);
    showResults(players, n, "Priority Scheduling");
 
    printf("\n\nDone.\n");
    return 0;
}
 