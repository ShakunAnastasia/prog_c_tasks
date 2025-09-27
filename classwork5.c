#include <stdio.h>
#include <math.h>

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();

int main() {

	int choice;
	printf("Enter task number (1-7): ");
	scanf_s("%d", &choice);

	if (choice == 1) task1();
	else if (choice == 2) task2();
	else if (choice == 3) task3();
	else if (choice == 4) task4();
	else if (choice == 5) task5();
	else if (choice == 6) task6();
	else if (choice == 7) task7();
	else printf("Invalid number.\n");

}

void task1() {

    unsigned char n;

    printf("Enter natural number n < 64: ");
    scanf_s("%hhu", &n);

    if (n >= 64) {
        printf("Error: n must be less than 64!\n");
        return;
    }

    unsigned int result = 1u << n;

    printf("2^%u = %u\n", n, result);
}

void task2() {

    unsigned int n, k;

    printf("Enter number n: ");
    scanf_s("%u", &n);
    printf("Enter bit position k (0-based): ");
    scanf_s("%u", &k);

    unsigned int result = n | (1u << k);

    printf("Original number: %u (binary: ", n);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
    printf(")\n");

    printf("Result: %u (binary: ", result);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (result >> i) & 1);
    }
    printf(")\n");

    printf("Set bit %d to 1\n", k);
}

void task3() {
   
    unsigned long long m;
    unsigned int k;

    printf("Enter 64-bit number m: ");
    scanf_s("%llu", &m);
    printf("Enter bit position k: ");
    scanf_s("%u", &k);

    if (k >= 64) {
        printf("Error: k must be less than 64!\n");
        return;
    }

    unsigned long long result = m & ~(1ULL << k);

    printf("%llu\n", result);
    printf("0x%llx\n", result);
}

void task4() {

    unsigned int n;

    printf("Enter 32-bit number: ");
    scanf_s("%u", &n);

    unsigned int first_high = (n >> 24) & 0xFF;
    unsigned int last_high = (n >> 16) & 0xFF;

    unsigned int result = n;
    result = (result & ~(0xFF << 24)) | (last_high << 24);
    result = (result & ~(0xFF << 16)) | (first_high << 16);

    printf("%u\n", result);
    printf("0x%x\n", result);

}

void task5() {

    unsigned int n;

    printf("Enter number: ");
    scanf_s("%u", &n);

    int max_count = 0;
    int current_count = 0;

    for (int i = 0; i < 32; i++) {
        if (n & (1u << i)) {
            current_count++;
            if (current_count > max_count) {
                max_count = current_count;
            }
        }
        else {
            current_count = 0;
        }
    }

    printf("%d\n", max_count);
}

void task6() {

    int x;

    printf("Enter number x: ");
    scanf_s("%d", &x);

    int y1 = ((x & (x - 1)) > 0);
    printf("y = ((x & (x-1)) > 0) = %d\n", y1);
    printf("This checks if x is NOT a power of two\n");

    int y2 = x & (-x);
    printf("y = x & (-x) = %d\n", y2);
    printf("This extracts the lowest set bit of x\n");

    printf("\nVerification for different x values:\n");
    printf("x\tx&(x-1)>0\tx&(-x)\tMeaning\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    int test_values[] = { 0, 1, 2, 3, 4, 5, 8, 15 };
    for (int i = 0; i < 8; i++) {
        int test_x = test_values[i];
        int res1 = ((test_x & (test_x - 1)) > 0);
        int res2 = test_x & (-test_x);
        printf("%d\t%d\t\t%d\t", test_x, res1, res2);

        if (test_x == 0) printf("x=0 (special case)\n");
        else if (res1 == 0) printf("Power of two\n");
        else printf("Not power of two, lowest bit=%d\n", res2);
    }
}

void task7() {

    unsigned int x = 0x12345678;
    unsigned char* bytes = (unsigned char*)&x;

    printf("Number: 0x%x\n", x);
    printf("Byte order in memory: ");

    for (int i = 0; i < 4; i++) {
        printf("%02x ", bytes[i]);
    }
    printf("\n");

    if (bytes[0] == 0x78) {
        printf("Architecture: Little Endian\n");
    }
    else if (bytes[0] == 0x12) {
        printf("Architecture: Big Endian\n");
    }
    else {
        printf("Architecture: Middle Endian (Mixed)\n");
    }
}