#include <stdio.h>

#define BUFFER_SIZE 1024
#define true 1
#define false 0

int flag_buf = 0;
char buf [2][BUFFER_SIZE];

// TODO<psdh> decide on states
typedef enum
{
    ST_DONE,
} states;

// TODO<psdh> add appropriate tokens to return
typedef enum
{
    TK_RETURN,
    TK_IF,
} tokens;

char get_char_onebyone(FILE* fd)
{
    char c;
    if ((c = fgetc(fd)) != EOF)
    {
        printf("%c\n", c);
        return 0;
    }
    else
    {
        printf("end\n");
        return 1;
    }
}

// This will load 2048 bytes in one shot to the new buffer
int get_char(FILE* fd)
{
    int k = fread(buf[flag_buf], 1, BUFFER_SIZE, fd);

    // keep inverting the buffers to be used!
    flag_buf = 1 - flag_buf;
    printf("length read: %d\n", k);
    return k == BUFFER_SIZE?false:true;
}

// TODO<psdh> profile the performance between the buffered and char by char approaches
// TODO<psdh> find and add a better test file (instead of stack.c)
int main()
{
    FILE* fd;
    fd = fopen("stack.c", "rb");

    while(!get_char(fd))
        printf("%s\n", buf[1-flag_buf]);

    // for testing correct use of the 2 input buffers
    // TODO<psdh> add test for correct use of BUFFER_SIZE
    printf("READ FROM HERE");
    printf("%s \n\n\n\n", buf[0]);
    printf("%s \n\n\n\n", buf[1]);


    // while(!get_char_onebyone(fd));
}
