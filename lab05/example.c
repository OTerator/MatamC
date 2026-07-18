#include <stdio.h>
#include <string.h>

int main(int argc, const char* argv[]) {
    printf("argc = %d\n", argc);

    for(int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);

        if(strcmp(argv[i], "1") == 0) {
            printf("success!\n");
        }
    }

    return 0;
}
