#include <stdio.h>
// Dans cette exemple, les tâches sont ordonnnancé dans l'ordre des priorité statique.
// Structure d'une tâche 
typedef struct {
    int execution_time;
    int deadline;
    int period;
    int priority;
} Task;


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
    
    Task tasks[3] = {
        {2, 7, 7, 20},  
        {3, 11, 11, 15}, 
        {5, 13, 13, 10}  
    };

    // Nombre de tâches
    int n = 3;

    // Vérification de la faisabilité
    if (is_schedulable(tasks, n)) {
        printf("L'ensemble des tâches est faisable.\n");
    } else {
        printf("L'ensemble des tâches n'est pas faisable.\n");
    }

    return 0;
}

// gcc schedulability.c -o schedulability
//./schedulability

