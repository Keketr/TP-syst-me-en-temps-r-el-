#include <stdio.h>
#include <stdlib.h>

// Définir la structure de la tâche
typedef struct {
    int execution_time;
    int deadline;
    int period;
    int priority;
} Task;

// Fonction de comparaison pour trier par priorité (HPF)
int compare_priority(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return taskB->priority - taskA->priority; 
}

// Fonction de comparaison pour trier par période (RM - Rate Monotonic)
int compare_rm(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return taskA->period - taskB->period; 
}

// Fonction de comparaison pour trier par échéance (DM - Deadline Monotonic)
int compare_dm(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return taskA->deadline - taskB->deadline; 
}

// Fonction pour vérifier la faisabilité des tâches
int is_schedulable(Task tasks[], int n) {
    float utilization = 0.0;

    // Calcul de l'utilisation du processeur
    for (int i = 0; i < n; i++) {
        utilization += (float)tasks[i].execution_time / tasks[i].period;
    }

    // limite à 100%
    if (utilization <= 1.0) {
        return 1; 
    } else {
        return 0; 
    }
}

int main() {
    int n, ordonnancement;

    // nombre de tâches
    printf("Entrez le nombre de tâches : ");
    scanf("%d", &n);


    Task *tasks = (Task *)malloc(n * sizeof(Task));

    // Choix des specs de la tâches
    for (int i = 0; i < n; i++) {
        printf("\nTâche %d :\n", i + 1);
        printf("Durée d'exécution : ");
        scanf("%d", &tasks[i].execution_time);
        printf("Echéance : ");
        scanf("%d", &tasks[i].deadline);
        printf("Période : ");
        scanf("%d", &tasks[i].period);
        printf("Priorité (pour HPF uniquement, valeur plus élevée = plus prioritaire) : ");
        scanf("%d", &tasks[i].priority);
    }

    // Choisir l'algorithme d'ordonnancement
    printf("\nChoisissez l'algorithme d'ordonnancement :\n");
    printf("1. HPF (Highest Priority First)\n");
    printf("2. RM (Rate Monotonic)\n");
    printf("3. DM (Deadline Monotonic)\n");
    printf("Entrez votre choix : ");
    scanf("%d", &ordonnancement);

    // Tri des tâches en fonction de l'algorithme choisi
    if (ordonnancement == 1) {
        qsort(tasks, n, sizeof(Task), compare_priority); // HPF : Tri par priorité
        printf("\nOrdonnancement HPF sélectionné.\n");
    } else if (ordonnancement == 2) {
        qsort(tasks, n, sizeof(Task), compare_rm); // RM : Tri par période
        printf("\nOrdonnancement RM sélectionné.\n");
    } else if (ordonnancement == 3) {
        qsort(tasks, n, sizeof(Task), compare_dm); // DM : Tri par échéance
        printf("\nOrdonnancement DM sélectionné.\n");
    } else {
        printf("Choix invalide. Arrêt du programme.\n");
        free(tasks);
        return 1;
    }

    // Affiche les tâches triées 
    printf("\nTâches triées :\n");
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
