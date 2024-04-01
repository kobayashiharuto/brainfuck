#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    char array[30000] = {0};
    char *ptr = array;

    // BrainfuckプログラムをCコードに変換して出力する
    printf("#include <stdio.h>\n");
    printf("#include <time.h>\n\n");
    printf("int main() {\n");
    printf("    clock_t start, end;\n");
    printf("    double cpu_time_used;\n");
    printf("    start = clock();\n\n");
    printf("    char array[30000] = {0};\n");
    printf("    char *ptr = array;\n");
    
    int c, count;
    while ((c = getchar()) != EOF) {
        switch (c) {
            case '>':
                for (count = 1; (c = getchar()) == '>'; ++count);
                ungetc(c, stdin); // 最後に読み込んだ文字をストリームに戻す
                printf("    ptr += %d;\n", count);
                break;
            case '<':
                for (count = 1; (c = getchar()) == '<'; ++count);
                ungetc(c, stdin); // 最後に読み込んだ文字をストリームに戻す
                printf("    ptr -= %d;\n", count);
                break;
            case '+':
                for (count = 1; (c = getchar()) == '+'; ++count);
                ungetc(c, stdin);
                printf("    *ptr += %d;\n", count);
                break;
            case '-':
                for (count = 1; (c = getchar()) == '-'; ++count);
                ungetc(c, stdin);
                printf("    *ptr -= %d;\n", count);
                break;
            case '.': printf("    putchar(*ptr);\n"); break;
            case ',': printf("    *ptr = getchar();\n"); break;
            case '[': printf("    while (*ptr) {\n"); break;
            case ']': printf("    }\n"); break;
        }
    }
    
    // 実行時間計測終了と結果の出力
    printf("\n    end = clock();\n");
    printf("    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;\n");
    printf("    printf(\"Execution Time: %%f seconds\\n\", cpu_time_used);\n");
    printf("    return 0;\n");
    printf("}\n");
    return 0;
}
