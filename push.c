#include "monty.h"
#include "lists.h"
void initializeStack() {
    stack.array = (int *)malloc(STACK_SIZE * sizeof(int));
    if (stack.array == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for the stack\n");
        exit(EXIT_FAILURE);
    }
    stack.top = -1;
}

void push(int value, int line_number) {
    if (stack.top == STACK_SIZE - 1) {
        fprintf(stderr, "L%d: Stack overflow\n", line_number);
        exit(EXIT_FAILURE);
    }

    stack.top++;
    stack.array[stack.top] = value;
}

void pall() {
    int i;
    for (i = stack.top; i >= 0; i--) {
        printf("%d\n", stack.array[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char opcode[100];
    int value, line_number = 1;

    initializeStack();

    while (fscanf(file, "%s", opcode) != EOF) {
        if (strcmp(opcode, "push") == 0) {
            if (fscanf(file, "%d", &value) != 1) {
                fprintf(stderr, "L%d: usage: push integer\n", line_number);
                exit(EXIT_FAILURE);
            }
            push(value, line_number);
        } else if (strcmp(opcode, "pall") == 0) {
            pall();
        } else {
            fprintf(stderr, "L%d: unknown opcode %s\n", line_number, opcode);
            exit(EXIT_FAILURE);
        }
        line_number++;
    }

    fclose(file);
    free(stack.array); // Free allocated memory
    return 0;
}
