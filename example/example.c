#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "tagging_macros.h"

int main(int argc, char* argv[]) {
    int i;
    int64_t *tag_in = malloc(8);
    int64_t *tag_tmp = malloc(8);
    int64_t *tag_out = malloc(8);

    *tag_in = -1;
    *tag_tmp = 0;
    *tag_out = 0;

    // initialize tag of i from tag_in location
    LOAD_TAG(i, tag_in);

    // save tag of i to tag_tmp location
    STORE_TAG(i, tag_tmp);
    printf("%s, %d args: Hello %s", argv[0], argc-1, "World");
    LOAD_TAG(i, tag_tmp);


    // dump tag of i to tag_out location
    STORE_TAG(i, tag_out);

    printf("tag_in = 0x%lx\n", *tag_in);
    printf("tag_tmp = 0x%lx\n", *tag_tmp);
    printf("tag_out = 0x%lx\n", *tag_out);

    return 0;
}
