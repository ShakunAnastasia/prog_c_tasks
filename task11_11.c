#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME_LENGTH 50
#define MAX_PASSENGERS 100
#define FILENAME_LENGTH 100

typedef struct {
    int passenger_id;
    int item_count;
    double total_weight;
} Luggage;

typedef struct {
    char last_name[MAX_NAME_LENGTH];
} Passenger;

Passenger passengers[MAX_PASSENGERS];
Luggage luggage[MAX_PASSENGERS];
int passenger_count = 0;
int luggage_count = 0;

void load_passengers(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open passengers file %s\n", filename);
        return;
    }

    passenger_count = 0;
    while (passenger_count < MAX_PASSENGERS &&
           fscanf_s(file, "%49s", passengers[passenger_count].last_name, (unsigned)_countof(passengers[passenger_count].last_name)) == 1) {
        passenger_count++;
    }

    fclose(file);
    printf("Loaded %d passengers\n", passenger_count);
}

void load_luggage(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open luggage file %s\n", filename);
        return;
    }

    luggage_count = 0;
    while (luggage_count < MAX_PASSENGERS &&
           fscanf_s(file, "%d %d %lf",
               &luggage[luggage_count].passenger_id,
               &luggage[luggage_count].item_count,
               &luggage[luggage_count].total_weight) == 3) {
        luggage_count++;
    }

    fclose(file);
    printf("Loaded %d luggage records\n", luggage_count);
}

double calculate_overall_average_weight() {
    if (luggage_count == 0) return 0.0;

    double total_weight = 0.0;
    int total_items = 0;

    for (int i = 0; i < luggage_count; i++) {
        total_weight += luggage[i].total_weight;
        total_items += luggage[i].item_count;
    }

    if (total_items == 0) return 0.0;

    return total_weight / total_items;
}

double calculate_average_item_count() {
    if (luggage_count == 0) return 0.0;

    int total_items = 0;
    for (int i = 0; i < luggage_count; i++) {
        total_items += luggage[i].item_count;
    }

    return (double)total_items / luggage_count;
}

void find_passengers_with_similar_average_weight(double a) {
    printf("\na) Passengers with average weight within %.2f kg of overall average:\n", a);

    double overall_avg = calculate_overall_average_weight();
    printf("Overall average weight per item: %.2f kg\n", overall_avg);

    int found = 0;
    for (int i = 0; i < luggage_count; i++) {
        Luggage l = luggage[i];
        if (l.passenger_id < 1 || l.passenger_id > passenger_count || l.item_count == 0) continue;

        double passenger_avg = l.total_weight / l.item_count;
        double difference = fabs(passenger_avg - overall_avg);

        if (difference <= a) {
            printf("  %s: %.2f kg/item (difference: %.2f kg)\n",
                passengers[l.passenger_id - 1].last_name,
                passenger_avg, difference);
            found = 1;
        }
    }

    if (!found) {
        printf("  No passengers found\n");
    }
}

void find_passengers_by_item_count() {
    printf("\nb) Passengers analysis by item count:\n");

    double avg_items = calculate_average_item_count();
    printf("Average number of items: %.2f\n", avg_items);

    printf("Passengers with more than 2 items:\n");
    int found1 = 0;
    for (int i = 0; i < luggage_count; i++) {
        if (luggage[i].item_count > 2 && luggage[i].passenger_id >= 1 && luggage[i].passenger_id <= passenger_count) {
            printf("  %s: %d items\n",
                passengers[luggage[i].passenger_id - 1].last_name,
                luggage[i].item_count);
            found1 = 1;
        }
    }
    if (!found1) printf("  None\n");

    printf("Passengers with above average item count:\n");
    int found2 = 0;
    for (int i = 0; i < luggage_count; i++) {
        if (luggage[i].item_count > avg_items && luggage[i].passenger_id >= 1 && luggage[i].passenger_id <= passenger_count) {
            printf("  %s: %d items (average: %.2f)\n",
                passengers[luggage[i].passenger_id - 1].last_name,
                luggage[i].item_count, avg_items);
            found2 = 1;
        }
    }
    if (!found2) printf("  None\n");
}

void find_passenger_max_items_min_weight() {
    printf("\nc) Passenger with max items and min weight for that count:\n");

    if (luggage_count == 0) {
        printf("  No luggage data\n");
        return;
    }

    int max_items = 0;
    for (int i = 0; i < luggage_count; i++) {
        if (luggage[i].item_count > max_items) {
            max_items = luggage[i].item_count;
        }
    }

    int found_index = -1;
    double min_weight = -1.0;

    for (int i = 0; i < luggage_count; i++) {
        if (luggage[i].item_count == max_items) {
            if (found_index == -1 || luggage[i].total_weight < min_weight) {
                found_index = i;
                min_weight = luggage[i].total_weight;
            }
        }
    }

    if (found_index != -1 && luggage[found_index].passenger_id >= 1 && luggage[found_index].passenger_id <= passenger_count) {
        Luggage l = luggage[found_index];
        printf("  %s: %d items, %.2f kg (%.2f kg per item)\n",
            passengers[l.passenger_id - 1].last_name,
            l.item_count, l.total_weight, l.total_weight / l.item_count);
    }
    else {
        printf("  Not found\n");
    }
}

void find_passengers_similar_luggage(double a) {
    printf("\nd) Passengers with same item count and weight difference <= %.2f kg:\n", a);

    int found_any = 0;

    for (int i = 0; i < luggage_count - 1; i++) {
        for (int j = i + 1; j < luggage_count; j++) {
            if (luggage[i].item_count == luggage[j].item_count) {
                double weight_diff = fabs(luggage[i].total_weight - luggage[j].total_weight);
                if (weight_diff <= a &&
                    luggage[i].passenger_id >= 1 && luggage[i].passenger_id <= passenger_count &&
                    luggage[j].passenger_id >= 1 && luggage[j].passenger_id <= passenger_count) {
                    printf("  %s and %s: %d items, weight difference %.2f kg\n",
                        passengers[luggage[i].passenger_id - 1].last_name,
                        passengers[luggage[j].passenger_id - 1].last_name,
                        luggage[i].item_count, weight_diff);
                    found_any = 1;
                }
            }
        }
    }

    if (!found_any) {
        printf("  No such passenger pairs found\n");
    }
}

void find_passenger_single_heavy_item(double m) {
    printf("\ne) Passenger with single item weighing at least %.2f kg:\n", m);

    int found = 0;
    for (int i = 0; i < luggage_count; i++) {
        if (luggage[i].item_count == 1 && luggage[i].total_weight >= m &&
            luggage[i].passenger_id >= 1 && luggage[i].passenger_id <= passenger_count) {
            printf("  %s: 1 item, %.2f kg\n",
                passengers[luggage[i].passenger_id - 1].last_name,
                luggage[i].total_weight);
            found = 1;
        }
    }

    if (!found) {
        printf("  No such passenger found\n");
    }
}

int main() {
    char passengers_file[FILENAME_LENGTH];
    char luggage_file[FILENAME_LENGTH];

    printf("Enter passengers filename: ");
    if (scanf_s("%99s", passengers_file, (unsigned)sizeof(passengers_file)) != 1) {
        printf("Input error!\n");
        return 1;
    }

    printf("Enter luggage filename: ");
    if (scanf_s("%99s", luggage_file, (unsigned)sizeof(luggage_file)) != 1) {
        printf("Input error!\n");
        return 1;
    }

    load_passengers(passengers_file);
    load_luggage(luggage_file);

    if (passenger_count == 0 || luggage_count == 0) {
        printf("Error: No data loaded\n");
        return 1;
    }

    double a, m;

    printf("\nEnter value for 'a' (weight difference in kg): ");
    if (scanf_s("%lf", &a) != 1) {
        printf("Input error!\n");
        return 1;
    }

    printf("Enter value for 'm' (minimum weight for single item in kg): ");
    if (scanf_s("%lf", &m) != 1) {
        printf("Input error!\n");
        return 1;
    }

    find_passengers_with_similar_average_weight(a);
    find_passengers_by_item_count();
    find_passenger_max_items_min_weight();
    find_passengers_similar_luggage(a);
    find_passenger_single_heavy_item(m);

    return 0;
}