#include "asm.h"
#include <stdio.h>

int main()
{
    struct instruction_t instr;
    char                 buff[64];
    int                  x;
    while (fgets(buff, sizeof buff, stdin) == buff) {
        instr = strtoinstr(buff);
        if (instr.opc == ERR) {
            printf("ERROR ");
        } else {
            x = assemble(instr);
            printf("0x%x ", x);
        }
    }
    return 0;
}
