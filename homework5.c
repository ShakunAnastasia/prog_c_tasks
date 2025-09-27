#include <stdio.h>

void task1();
void task2();

int main() {
	
	int choice;
	printf("Enter task number (1-2): ");
	scanf_s("%d", &choice);

	if (choice == 1) {
		task1();
	}
	else if (choice == 2) {
		task2();
	}
	else {
		printf("Invalid task number.\n");
	}
}

void task1() {

    unsigned int m;
    unsigned int j;

    printf("Enter 32-bit number m: ");
    scanf_s("%u", &m);
    printf("Enter bit position j: ");
    scanf_s("%u", &j);

    if (j >= 32) {
        printf("Error: j must be less than 32!\n");
        return;
    }

    unsigned int result = m & ~(1u << j);

    printf("%u\n", result);
    printf("0x%x\n", result);

}

void task2() {

    unsigned int n;

    printf("Enter natural number: ");
    scanf_s("%u", &n);

    printf("Binary representation: ");
    for (int i = 31; i >= 0; i--) {
        if (n & (1u << i)) {
            printf("X");
        }
        else {
            printf("Y");
        }
    }
    printf("\n");

}