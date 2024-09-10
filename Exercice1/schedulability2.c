#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure d'une tâche
typedef struct {
    int execution_time;
    int deadline;
    int period;
    int priority;
    int next_start;  // Le temps du prochain événement pour la tâche
} Task;

// Structure d'événement
typedef struct {
    int task_index;
    int event_time;
} Event;

// Fonction pour trier les événements par temps d'événement
int compare_events(const void *a, const void *b) {
    Event *eventA = (Event *)a;
    Event *eventB = (Event *)b;
    return eventA->event_time - eventB->event_time;
}

// Fonction pour vérifier la faisabilité des tâches
int is_schedulable(Task tasks[], int n) {
    float utilization = 0.0;

    // Calcul de l'utilisation du processeur
    for (int i = 0; i < n; i++) {
        utilization += (float)tasks[i].execution_time / tasks[i].period;
    }

    // Condition de faisabilité basée sur l'utilisation (limite de 100%)
    return (utilization <= 1.0) ? 1 : 0;
}

// Fonction pour simuler l'exécution par événements
void run_scheduler(Task tasks[], int n, int total_time) {
    // Tableau des événements (une tâche peut avoir plusieurs événements sur la durée de simulation)
    Event *events = (Event *)malloc(n * sizeof(Event));
    
    // Initialiser les événements initiaux
    for (int i = 0; i < n; i++) {
        events[i].task_index = i;
        events[i].event_time = tasks[i].next_start;
    }

    // Exécuter tant que le temps n'a pas dépassé la durée totale de simulation
    int current_time = 0;
    while (current_time < total_time) {
        // Trier les événements en fonction de l'heure de l'événement
        qsort(events, n, sizeof(Event), compare_events);

        // Chercher le prochain événement à exécuter
        for (int i = 0; i < n; i++) {
            if (events[i].event_time >= current_time) {
                int task_index = events[i].task_index;
                printf("Temps %d : Exécution de la tâche %d (Priorité : %d)\n",
                       current_time, task_index + 1, tasks[task_index].priority);

                // La tâche est exécutée, mettre à jour son prochain temps d'événement
                current_time += tasks[task_index].execution_time;
                tasks[task_index].next_start += tasks[task_index].period;
                events[i].event_time = tasks[task_index].next_start;
                break;
            }
        }
    }

    // Libérer la mémoire des événements
    free(events);
}

int main() {
    // Créer les tâches avec leurs caractéristiques
    Task tasks[3] = {
        {2, 7, 7, 20},  // Tâche 1
        {3, 11, 11, 15}, // Tâche 2
        {5, 13, 13, 10}  // Tâche 3
    };

    // Initialiser le prochain démarrage des tâches à 0 (démarrage immédiat)
    for (int i = 0; i < 3; i++) {
        tasks[i].next_start = 0;
    }

    int n = 3;
    int total_time = 30; // Temps total de simulation

    // Vérification de la faisabilité
    if (is_schedulable(tasks, n)) {
        printf("L'ensemble des tâches est faisable.\n");
        // Exécution du simulateur basé sur les événements
        run_scheduler(tasks, n, total_time);
    } else {
        printf("L'ensemble des tâches n'est pas faisable.\n");
    }

    return 0;
}
