#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME "rectangles.dat"
#define MAX_RECTANGLES 100

typedef struct {
    int id;
    double top_left_x;
    double top_left_y;
    double bottom_right_x;
    double bottom_right_y;
} Rectangle;

double calculateArea(const Rectangle* rect) {
    double width = rect->bottom_right_x - rect->top_left_x;
    double height = rect->top_left_y - rect->bottom_right_y;
    return (width < 0 ? -width : width) * (height < 0 ? -height : height);
}

void createSampleFile() {
    printf("Creating sample file...\n");
    FILE* file = fopen(FILENAME, "wb");
    if (!file) {
        printf("Error creating file\n");
        return;
    }

    Rectangle rects[] = {
        {1, 0.0, 5.0, 4.0, 0.0},   // area: 20
        {2, 1.0, 8.0, 5.0, 2.0},   // area: 24  
        {3, 2.0, 6.0, 6.0, 1.0},   // area: 20
        {4, 0.0, 10.0, 3.0, 0.0},  // area: 30
        {5, 1.0, 7.0, 4.0, 3.0}    // area: 12
    };

    for (int i = 0; i < 5; i++) {
        fwrite(&rects[i], sizeof(Rectangle), 1, file);
    }
    fclose(file);
    printf("Sample file created\n\n");
}

void displayAllRectangles() {
    printf("All rectangles:\n");
    FILE* file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    Rectangle rect;
    printf("ID   TL_X    TL_Y    BR_X    BR_Y    Area\n");
    printf("-----------------------------------------\n");

    while (fread(&rect, sizeof(Rectangle), 1, file)) {
        double area = calculateArea(&rect);
        printf("%-4d %-7.1f %-7.1f %-7.1f %-7.1f %-7.1f\n",
            rect.id, rect.top_left_x, rect.top_left_y,
            rect.bottom_right_x, rect.bottom_right_y, area);
    }
    fclose(file);
    printf("\n");
}

int findRectangleWithMaxArea(double* maxArea) {
    FILE* file = fopen(FILENAME, "rb");
    if (!file) return -1;

    Rectangle rect;
    int maxId = -1;
    *maxArea = -1;

    while (fread(&rect, sizeof(Rectangle), 1, file)) {
        double area = calculateArea(&rect);
        if (area > *maxArea) {
            *maxArea = area;
            maxId = rect.id;
        }
    }
    fclose(file);
    return maxId;
}

bool deleteRectangleById(int id) {
    FILE* file = fopen(FILENAME, "rb");
    if (!file) return false;

    Rectangle rects[MAX_RECTANGLES];
    int count = 0;
    Rectangle temp;
    bool found = false;

    while (fread(&temp, sizeof(Rectangle), 1, file)) {
        if (temp.id == id) {
            found = true;
        }
        else {
            rects[count++] = temp;
        }
    }
    fclose(file);

    if (!found) {
        printf("Rectangle %d not found\n", id);
        return false;
    }

    file = fopen(FILENAME, "wb");
    if (!file) return false;

    for (int i = 0; i < count; i++) {
        fwrite(&rects[i], sizeof(Rectangle), 1, file);
    }
    fclose(file);
    printf("Rectangle %d deleted\n", id);
    return true;
}

bool updateRectangleById(int id, double x1, double y1, double x2, double y2) {
    FILE* file = fopen(FILENAME, "rb+");
    if (!file) return false;

    Rectangle rect;
    bool found = false;

    while (fread(&rect, sizeof(Rectangle), 1, file)) {
        if (rect.id == id) {
            found = true;
            fseek(file, -((long)sizeof(Rectangle)), SEEK_CUR);
            Rectangle newRect = { id, x1, y1, x2, y2 };
            fwrite(&newRect, sizeof(Rectangle), 1, file);
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("Rectangle %d not found\n", id);
        return false;
    }
    printf("Rectangle %d updated\n", id);
    return true;
}

bool addRectangle(int id, double x1, double y1, double x2, double y2) {
    FILE* file = fopen(FILENAME, "rb");
    if (file) {
        Rectangle rect;
        while (fread(&rect, sizeof(Rectangle), 1, file)) {
            if (rect.id == id) {
                printf("ID %d already exists\n", id);
                fclose(file);
                return false;
            }
        }
        fclose(file);
    }

    file = fopen(FILENAME, "ab");
    if (!file) return false;

    Rectangle newRect = { id, x1, y1, x2, y2 };
    fwrite(&newRect, sizeof(Rectangle), 1, file);
    fclose(file);

    printf("Rectangle %d added\n", id);
    return true;
}

int main() {
    printf("Rectangle Manager\n\n");

    createSampleFile();
    displayAllRectangles();

    double maxArea;
    int maxId = findRectangleWithMaxArea(&maxArea);
    printf("Max area: Rectangle %d (%.1f)\n\n", maxId, maxArea);

    printf("Deleting rectangle 3...\n");
    deleteRectangleById(3);
    displayAllRectangles();
 
    printf("Updating rectangle 2...\n");
    updateRectangleById(2, 0.0, 10.0, 8.0, 0.0);
    displayAllRectangles();

    printf("Adding rectangle 6...\n");
    addRectangle(6, 2.0, 9.0, 7.0, 2.0);
    displayAllRectangles();

    maxId = findRectangleWithMaxArea(&maxArea);
    printf("New max area: Rectangle %d (%.1f)\n\n", maxId, maxArea);

    printf("Done!\n");
    return 0;
}