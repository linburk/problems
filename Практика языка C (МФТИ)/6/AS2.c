#include "asm.h"
#include <stdio.h>

int main()
{
    struct instruction_t instr;
    char                 buff[64];
    int                  x;
    while (scanf("%x", &x) == 1) {
        instr = disassemble(x);
        instrtostr(buff, sizeof buff, instr);
        printf("%s\n", buff);
    }
    return 0;
}
