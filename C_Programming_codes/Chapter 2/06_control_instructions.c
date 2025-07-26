// Sequence control instruction
#include <stdio.h>

int main() {
    // Sequence of instructions
    int a = 5, b = 3;
    int sum = a + b;      // First instruction
    int product = a * b;  // Second instruction

    printf("Sum: %d\n", sum);         // Third instruction
    printf("Product: %d\n", product); // Fourth instruction

    return 0;
}

//  Decision (if-else) control instruction
#include <stdio.h>

int main() {
    int number = 10;

    // Decision using if-else
    if (number > 0) {
        printf("The number is positive.\n");
    } else if (number < 0) {
        printf("The number is negative.\n");
    } else {
        printf("The number is zero.\n");
    }

    return 0;
}

//Loop (for loop) control instruction
#include <stdio.h>

int main() {
    // Loop example: for loop to print numbers 1 to 5
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }

    printf("\n");

    return 0;
}
 
// Case (switch) control instruction
#include <stdio.h>

int main() {
    int day = 3;

    // Case (switch statement)
    switch (day) {
        case 1:
            printf("Monday\n");
            break;
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        case 4:
            printf("Thursday\n");
            break;
        case 5:
            printf("Friday\n");
            break;
        case 6:
            printf("Saturday\n");
            break;
        case 7:
            printf("Sunday\n");
            break;
        default:
            printf("Invalid day\n");
            break;
    }

    return 0;
}
