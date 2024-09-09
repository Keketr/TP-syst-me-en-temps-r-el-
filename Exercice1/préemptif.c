//Ordonnancement préemptif : Le système peut interrompre une tâche en cours pour en exécuter une autre qui a une priorité plus élevée.
//Ordonnancement non-préemptif : Une tâche en cours d'exécution ne peut pas être interrompue jusqu'à ce qu'elle se termine, même si une tâche avec une priorité plus élevée arrive.

#include <stdio.h>
#include <stdlib.h>

// Définir la structure de la tâche
typedef struct {
    int id;
    int execution_time;
    int deadline;
    int period;
    int priority;
    int remaining_time; // Pour simuler l'exécution progressive
} Task;

// Fonction pour simuler un ordonnanceur préemptif ou non-préemptif
void schedule_tasks(Task tasks[], int n, int preemptive) {
    int current_time = 0;
    int tasks_completed = 0;
    
    while (tasks_completed < n) {
        int highest_priority_task = -1;

        // Trouver la tâche prête à être exécutée avec la plus haute priorité
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0 && (highest_priority_task == -1 || tasks[i].priority > tasks[highest_priority_task].priority)) {
                highest_priority_task = i;
            }
        }

        if (highest_priority_task == -1) {
            // Si aucune tâche n'est prête, avancer dans le temps
            current_time++;
            continue;
        }

        printf("Temps %d : Exécution de la tâche %d (Priorité : %d)\n", current_time, tasks[highest_priority_task].id, tasks[highest_priority_task].priority);

        if (preemptive) {
            // Mode préemptif : on exécute la tâche pendant 1 unité de temps, puis on vérifie à nouveau
            tasks[highest_priority_task].remaining_time--;
            current_time++;
        } else {
            // Mode non-préemptif : on exécute la tâche jusqu'à ce qu'elle soit terminée
            current_time += tasks[highest_priority_task].remaining_time;
            tasks[highest_priority_task].remaining_time = 0;
        }

        // Si la tâche est terminée
        if (tasks[highest_priority_task].remaining_time == 0) {
            printf("Tâche %d terminée à t = %d\n", tasks[highest_priority_task].id, current_time);
            tasks_completed++;
        }
    }
}

int main() {
    int n, preemptive;

    // Demander à l'utilisateur le nombre de tâches
    printf("Entrez le nombre de tâches : ");
    scanf("%d", &n);

    // Allouer dynamiquement de la mémoire pour les tâches
    Task *tasks = (Task *)malloc(n * sizeof(Task));

    // Entrer les informations pour chaque tâche
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nTâche %d :\n", tasks[i].id);
        printf("Durée d'exécution : ");
        scanf("%d", &tasks[i].execution_time);
        tasks[i].remaining_time = tasks[i].execution_time; // Initialiser le temps restant
        printf("Echéance : ");
        scanf("%d", &tasks[i].deadline);
        printf("Période : ");
        scanf("%d", &tasks[i].period);
        printf("Priorité : ");
        scanf("%d", &tasks[i].priority);
    }

    // Demander si l'ordonnancement doit être préemptif ou non
    printf("\nChoisissez le type d'ordonnancement :\n");
    printf("1. Préemptif\n");
    printf("2. Non-préemptif\n");
    printf("Entrez votre choix : ");
    scanf("%d", &preemptive);

    // Simuler l'ordonnancement
    schedule_tasks(tasks, n, preemptive == 1);

    // Libérer la mémoire allouée
    free(tasks);

    return 0;
}
