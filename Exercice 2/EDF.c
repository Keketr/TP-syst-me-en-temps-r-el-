#include <stdio.h>
#include <stdlib.h>

// Définir la structure de la tâche
typedef struct {
    int id;
    int execution_time;
    int remaining_time;
    int deadline;
    int period;
    int next_deadline;  
} Task;

// Fonction de comparaison pour trier par échéance (pour EDF)
int compare_edf(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return taskA->next_deadline - taskB->next_deadline;  
}

// Fonction pour simuler l'ordonnancement EDF
void schedule_edf(Task tasks[], int n, int total_time) {
    int current_time = 0;

    while (current_time < total_time) {
        
        qsort(tasks, n, sizeof(Task), compare_edf);

        // Trouver la prochaine tâche à exécuter
        int selected_task = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                selected_task = i;
                break;
            }
        }

        if (selected_task == -1) {
            // Si aucune tâche n'est prête, avancer dans le temps
            printf("Temps %d : Aucune tâche à exécuter, le processeur est inactif.\n", current_time);
            current_time++;
            continue;
        }

        // Exécuter la tâche sélectionnée pendant une unité de temps
        printf("Temps %d : Exécution de la tâche %d (Echéance absolue : %d)\n", current_time, tasks[selected_task].id, tasks[selected_task].next_deadline);
        tasks[selected_task].remaining_time--;
        current_time++;

        // Vérifier si la tâche est terminée
        if (tasks[selected_task].remaining_time == 0) {
            printf("Tâche %d terminée à t = %d\n", tasks[selected_task].id, current_time);
            // Réinitialiser la tâche pour la période suivante
            tasks[selected_task].remaining_time = tasks[selected_task].execution_time;
            tasks[selected_task].next_deadline += tasks[selected_task].period;  // Mise à jour de la prochaine échéance
        }
    }
}

int main() {
    int n, total_time;

    
    printf("Entrez le nombre de tâches : ");
    scanf("%d", &n);

    
    Task *tasks = (Task *)malloc(n * sizeof(Task));

    
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nTâche %d :\n", tasks[i].id);
        printf("Durée d'exécution : ");
        scanf("%d", &tasks[i].execution_time);
        tasks[i].remaining_time = tasks[i].execution_time;  // Initialiser le temps restant
        printf("Echéance initiale : ");
        scanf("%d", &tasks[i].deadline);
        tasks[i].next_deadline = tasks[i].deadline;  // Initialiser la première échéance
        printf("Période : ");
        scanf("%d", &tasks[i].period);
    }

   
    printf("\nEntrez le temps total de simulation : ");
    scanf("%d", &total_time);

    // Simuler l'ordonnancement EDF
    schedule_edf(tasks, n, total_time);

   
    free(tasks);

    return 0;
}
