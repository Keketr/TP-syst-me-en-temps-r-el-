#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int execution_time;
    int deadline;
    int period;
    int priority;
} Task;

// Fonction de comparaison pour trier les tâches par priorité (ordre décroissant)
int compare_priority(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return taskB->priority - taskA->priority; // Tri décroissant (tâches avec priorités élevées en premier)
}


int is_schedulable(Task tasks[], int n) {
    float utilization = 0.0;

    // Calcul de l'utilisation du processeur
    for (int i = 0; i < n; i++) {
        utilization += (float)tasks[i].execution_time / tasks[i].period;
    }

    // Condition de faisabilité basée sur l'utilisation (limite de 100%)
    if (utilization <= 1.0) {
        return 1; 
    } else {
        return 0; 
    }
}

int main() {
    int n;

    // Demander à l'utilisateur le nombre de tâches
    printf("Entrez le nombre de tâches : ");
    scanf("%d", &n);

    // Allouer dynamiquement de la mémoire pour les tâches
    Task *tasks = (Task *)malloc(n * sizeof(Task));

    // Entrer les informations pour chaque tâche
    for (int i = 0; i < n; i++) {
        printf("\nTâche %d :\n", i + 1);
        printf("Durée d'exécution : ");
        scanf("%d", &tasks[i].execution_time);
        printf("Echéance : ");
        scanf("%d", &tasks[i].deadline);
        printf("Période : ");
        scanf("%d", &tasks[i].period);
        printf("Priorité (valeur plus élevée = plus prioritaire) : ");
        scanf("%d", &tasks[i].priority);
    }

    // Trier les tâches par priorité
    qsort(tasks, n, sizeof(Task), compare_priority);

    // Afficher les tâches triées (facultatif, pour vérification)
    printf("\nTâches triées par priorité (de la plus haute à la plus basse) :\n");
    for (int i = 0; i < n; i++) {
        printf("Tâche %d : Durée d'exécution = %d, Echéance = %d, Période = %d, Priorité = %d\n",
               i + 1, tasks[i].execution_time, tasks[i].deadline, tasks[i].period, tasks[i].priority);
    }


    if (is_schedulable(tasks, n)) {
        printf("\nL'ensemble des tâches est faisable.\n");
    } else {
        printf("\nL'ensemble des tâches n'est pas faisable.\n");
    }


    free(tasks);

    return 0;
}
