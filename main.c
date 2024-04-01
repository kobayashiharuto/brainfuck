#include <stdio.h>

#define MAX_STACK 256

int stack[MAX_STACK];
int top = -1;

void push(int value) {
    if (top >= (MAX_STACK - 1)) {
        printf("Stack Overflow\n");
    } else {
        stack[++top] = value;
    }
}

int pop() {
    if (top < 0) {
        printf("Stack Underflow\n");
        return -1;
    } else {
        return stack[top--];
    }
}

int main() {
    printf("section .bss\n");
    printf("array resb 30000\n");
    printf("section .text\n");
    printf("global _start\n");
    printf("_start:\n");
    printf("    mov rsi, array\n");

    int c, count;
    int loop_counter = 0;

    while ((c = getchar()) != EOF) {
        switch (c) {
            case '>':
                for (count = 1; (c = getchar()) == '>'; ++count);
                ungetc(c, stdin);
                printf("    add rsi, %d\n", count);
                break;
            case '<':
                for (count = 1; (c = getchar()) == '<'; ++count);
                ungetc(c, stdin);
                printf("    sub rsi, %d\n", count);
                break;
            case '+':
                for (count = 1; (c = getchar()) == '+'; ++count);
                ungetc(c, stdin);
                printf("    add byte [rsi], %d\n", count);
                break;
            case '-':
                for (count = 1; (c = getchar()) == '-'; ++count);
                ungetc(c, stdin);
                printf("    sub byte [rsi], %d\n", count);
                break;
            case '.':
                printf("    mov rax, 1\n");
                printf("    mov rdi, 1\n");
                printf("    mov rdx, 1\n");
                printf("    syscall\n");
                break;
            case ',':
                printf("    mov rax, 0\n");
                printf("    mov rdi, 0\n");
                printf("    mov rdx, 1\n");
                printf("    syscall\n");
                break;
            case '[':
                push(loop_counter);
                printf("loop_start_%d:\n", loop_counter);
                printf("    cmp byte [rsi], 0\n");
                printf("    je loop_end_%d\n", loop_counter);
                loop_counter++;
                break;
            case ']':
                if (top >= 0) {
                    int start_loop = pop();
                    printf("    jmp loop_start_%d\n", start_loop);
                    printf("loop_end_%d:\n", start_loop);
                }
                break;
        }
    }

    printf("    mov rax, 60\n");
    printf("    xor rdi, rdi\n");
    printf("    syscall\n");

    return 0;
}