#include <stdio.h>
#include <stdlib.h>

// Structure to represent an activity with a start and finish time.
typedef struct {
    int start;
    int finish;
} Activity;

/**
 * @brief Comparison function for qsort.
 *
 * This function is required by the C standard library's qsort function.
 * It compares two activities based on their finish times.
 * It casts the void pointers to Activity pointers to access the struct members.
 *
 * @param a A const void pointer to the first activity.
 * @param b A const void pointer to the second activity.
 * @return An integer less than, equal to, or greater than zero if the first
 * argument is considered to be respectively less than, equal to, or
 * greater than the second.
 */
int compareActivities(const void* a, const void* b) {
    Activity* activityA = (Activity*)a;
    Activity* activityB = (Activity*)b;
    return (activityA->finish - activityB->finish);
}

/**
 * @brief Solves the Activity Selection problem using a greedy approach.
 *
 * Sorts the activities by finish time and then selects the maximum
 * number of non-overlapping activities.
 *
 * @param activities An array of Activity structs.
 * @param n The number of activities in the array.
 */
void printMaxActivities(Activity activities[], int n) {
    // 1. Sort the activities based on their finish time in ascending order.
    qsort(activities, n, sizeof(Activity), compareActivities);

    printf("The following activities are selected:\n");

    // 2. The first activity is always selected.
    int last_selected_index = 0;
    printf("(%d, %d)\n", activities[last_selected_index].start, activities[last_selected_index].finish);

    // 3. Iterate through the rest of the activities.
    for (int i = 1; i < n; i++) {
        // If the current activity's start time is after or at the same time as the
        // finish time of the last selected activity, then select it.
        if (activities[i].start >= activities[last_selected_index].finish) {
            printf("(%d, %d)\n", activities[i].start, activities[i].finish);
            last_selected_index = i; // Update the last selected activity
        }
    }
}

int main() {
    // Example set of activities
    Activity activities[] = {
        {5, 9}, {1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}
    };

    // Calculate the number of activities
    int n = sizeof(activities) / sizeof(activities[0]);

    printMaxActivities(activities, n);

    return 0;
}