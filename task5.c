#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 50
#define MAX_MOUNTAINS 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    double height;
} Mountain;

void input_mountain(Mountain* mountain) {
    printf("Enter mountain name: ");
    if (scanf_s("%49s", mountain->name, (unsigned)_countof(mountain->name)) != 1) {
        printf("Error reading mountain name.\n");
        mountain->name[0] = '\0';
        while (getchar() != '\n');
    }

    printf("Enter mountain height (in meters): ");
    while (scanf("%lf", &mountain->height) != 1 || mountain->height <= 0) {
        printf("Error: Height must be a positive number. Try again: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
}

void print_mountain(const Mountain* mountain) {
    printf("Mountain: %s, Height: %.2f meters\n", mountain->name, mountain->height);
}

int input_mountains(Mountain mountains[], int max_size) {
    int n;
    printf("Enter number of mountains (max %d): ", max_size);
    while (scanf("%d", &n) != 1 || n <= 0 || n > max_size) {
        printf("Error: Number must be between 1 and %d. Try again: ", max_size);
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    for (int i = 0; i < n; i++) {
        printf("\nMountain %d:\n", i + 1);
        input_mountain(&mountains[i]);
    }
    return n;
}

void print_mountains(const Mountain mountains[], int count) {
    printf("\nAll mountains:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. ", i + 1);
        print_mountain(&mountains[i]);
    }
}

void find_highest_mountain(const Mountain mountains[], int count) {
    if (count == 0) {
        printf("No mountains in the array.\n");
        return;
    }

    double max_height = mountains[0].height;
    int max_index = 0;

    for (int i = 1; i < count; i++) {
        if (mountains[i].height > max_height) {
            max_height = mountains[i].height;
            max_index = i;
        }
    }

    printf("\nHighest mountain: %s (%.2f meters)\n",
        mountains[max_index].name, mountains[max_index].height);
}

void find_mountain_height(const Mountain mountains[], int count) {
    if (count == 0) {
        printf("No mountains in the array.\n");
        return;
    }

    char search_name[MAX_NAME_LENGTH];
    printf("Enter mountain name to search: ");
    if (scanf_s("%49s", search_name, (unsigned)_countof(search_name)) != 1) {
        printf("Error reading mountain name.\n");
        search_name[0] = '\0';
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    int found_index = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(mountains[i].name, search_name) == 0) {
            found_index = i;
            break;
        }
    }

    if (found_index != -1) {
        printf("Mountain '%s' height: %.2f meters\n",
            mountains[found_index].name, mountains[found_index].height);
    }
    else {
        printf("Mountain with name '%s' not found in the array.\n", search_name);
    }
}

int main() {
    Mountain mountains[MAX_MOUNTAINS];
    int mountain_count = 0;
    int choice;

    printf("Task 5.\n");

    do {
        printf("\nMain menu.\n");
        printf("1. Input mountains\n");
        printf("2. Display all mountains\n");
        printf("3. Find highest mountain\n");
        printf("4. Find mountain height by name\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Error: Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            mountain_count = input_mountains(mountains, MAX_MOUNTAINS);
            break;

        case 2:
            if (mountain_count > 0) {
                print_mountains(mountains, mountain_count);
            }
            else {
                printf("No mountains to display. Please input mountains first.\n");
            }
            break;

        case 3:
            if (mountain_count > 0) {
                find_highest_mountain(mountains, mountain_count);
            }
            else {
                printf("No mountains to search. Please input mountains first.\n");
            }
            break;

        case 4:
            if (mountain_count > 0) {
                find_mountain_height(mountains, mountain_count);
            }
            else {
                printf("No mountains to search. Please input mountains first.\n");
            }
            break;

        case 5:
            printf("Exiting program.\n");
            break;

        default:
            printf("Error: Invalid choice. Please enter a number between 1 and 5.\n");
            break;
        }

    } while (choice != 5);

    return 0;
}