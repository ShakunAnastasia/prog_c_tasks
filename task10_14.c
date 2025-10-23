#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    MALE,
    FEMALE
} Gender;

typedef struct {
    int nameIndex;
    Gender gender;
    double height;
} Person;

double calculateAverageFemaleHeight(const char** names, const Person* people, int count);
const char* findTallestMaleName(const char** names, const Person* people, int count);
void findPeopleWithSameHeight(const char** names, const Person* people, int count);
void printAllPeople(const char** names, const Person* people, int count);

void printAllPeople(const char** names, const Person* people, int count) {
    printf("\nAll people data:\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %-10s | Gender: %-6s | Height: %.1f cm\n",
            names[people[i].nameIndex],
            people[i].gender == FEMALE ? "Female" : "Male",
            people[i].height);
    }
}

double calculateAverageFemaleHeight(const char** names, const Person* people, int count) {
    double totalHeight = 0.0;
    int femaleCount = 0;

    for (int i = 0; i < count; i++) {
        if (people[i].gender == FEMALE) {
            totalHeight += people[i].height;
            femaleCount++;
        }
    }

    if (femaleCount == 0) {
        printf("No females found in the dataset.\n");
        return -1.0;
    }

    return totalHeight / femaleCount;
}

const char* findTallestMaleName(const char** names, const Person* people, int count) {
    double maxHeight = -1.0;
    int tallestMaleIndex = -1;

    for (int i = 0; i < count; i++) {
        if (people[i].gender == MALE && people[i].height > maxHeight) {
            maxHeight = people[i].height;
            tallestMaleIndex = people[i].nameIndex;
        }
    }

    if (tallestMaleIndex == -1) {
        printf("No males found in the dataset.\n");
        return NULL;
    }

    return names[tallestMaleIndex];
}

void findPeopleWithSameHeight(const char** names, const Person* people, int count) {
    bool foundPairs = false;

    printf("People with the same height:\n");

    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (fabs(people[i].height - people[j].height) < 0.001) {
                printf("  - %s and %s (both %.1f cm)\n",
                    names[people[i].nameIndex],
                    names[people[j].nameIndex],
                    people[i].height);
                foundPairs = true;
            }
        }
    }

    if (!foundPairs) {
        printf("  No people with the same height found.\n");
    }
}

int createSampleData(char*** names, Person** people) {
    char** sampleNames = (char**)malloc(8 * sizeof(char*));
    sampleNames[0] = "Anna";
    sampleNames[1] = "John";
    sampleNames[2] = "Maria";
    sampleNames[3] = "Michael";
    sampleNames[4] = "Sophia";
    sampleNames[5] = "David";
    sampleNames[6] = "Emma";
    sampleNames[7] = "Robert";

    Person* samplePeople = (Person*)malloc(8 * sizeof(Person));

    // Anna female, 165 cm
    samplePeople[0] = (Person){ 0, FEMALE, 165.0 };
    // John male, 180 cm
    samplePeople[1] = (Person){ 1, MALE, 180.0 };
    // Maria female, 170 cm
    samplePeople[2] = (Person){ 2, FEMALE, 170.0 };
    // Michael male, 175 cm
    samplePeople[3] = (Person){ 3, MALE, 175.0 };
    // Sophia female, 165 cm
    samplePeople[4] = (Person){ 4, FEMALE, 165.0 };
    // David male, 185 cm
    samplePeople[5] = (Person){ 5, MALE, 185.0 };
    // Emma female, 170 cm
    samplePeople[6] = (Person){ 6, FEMALE, 170.0 };
    // Robert male, 180 cm
    samplePeople[7] = (Person){ 7, MALE, 180.0 };

    *names = sampleNames;
    *people = samplePeople;

    return 8;
}

int inputDataManually(char*** names, Person** people) {
    int count;

    printf("Enter number of people: ");
    scanf("%d", &count);

    char** nameArray = (char**)malloc(count * sizeof(char*));
    Person* peopleArray = (Person*)malloc(count * sizeof(Person));

    printf("\nEnter data for %d people:\n", count);
    for (int i = 0; i < count; i++) {
        nameArray[i] = (char*)malloc(50 * sizeof(char));

        printf("\nPerson %d:\n", i + 1);
        printf("  Name: ");
        scanf("%49s", nameArray[i]);

        printf("  Gender (0 for Male, 1 for Female): ");
        int genderInput;
        scanf("%d", &genderInput);
        peopleArray[i].gender = (genderInput == 1) ? FEMALE : MALE;

        printf("  Height (cm): ");
        scanf("%lf", &peopleArray[i].height);

        peopleArray[i].nameIndex = i;
    }

    *names = nameArray;
    *people = peopleArray;

    return count;
}

void freeData(char** names, Person* people, int count, bool manualInput) {
    if (manualInput) {
        for (int i = 0; i < count; i++) {
            free(names[i]);
        }
    }
    free(names);
    free(people);
}

int main() {
    printf("~People data analysis system~\n\n");

    char** names = NULL;
    Person* people = NULL;
    int count = 0;

    int choice;
    printf("Choose data input method:\n");
    printf("1 - Use sample data\n");
    printf("2 - Enter data manually\n");
    printf("Your choice: ");
    scanf("%d", &choice);

    bool manualInput = false;

    if (choice == 1) {
        count = createSampleData(&names, &people);
        printf("Sample data loaded successfully.\n");
    }
    else {
        count = inputDataManually(&names, &people);
        manualInput = true;
        printf("Manual data input completed.\n");
    }

    printAllPeople((const char**)names, people, count);

    printf("~ Task a: Average Female Height~\n");
    double avgHeight = calculateAverageFemaleHeight((const char**)names, people, count);
    if (avgHeight > 0) {
        printf("Average height of females: %.2f cm\n\n", avgHeight);
    }

    printf("~ Task b: Tallest Male~\n");
    const char* tallestMale = findTallestMaleName((const char**)names, people, count);
    if (tallestMale != NULL) {
        printf("Tallest male: %s\n\n", tallestMale);
    }

    printf("~ Task c: People with Same Height~\n");
    findPeopleWithSameHeight((const char**)names, people, count);

    freeData(names, people, count, manualInput);

    printf("\nComplete!\n");
    return 0;
}