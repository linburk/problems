#include "asm.h"
#include <stdio.h>
#include <stdlib.h>

void interpetate(FILE* code, FILE* in, FILE* out, FILE* oasm);

int main(int argc, char const** argv)
{
    FILE *code, *data, *oasm = NULL;
    if (argc < 4)
        abort();
    code = fopen(argv[1], "r");
    if (code == NULL)
        abort();
    data = fopen(argv[2], "r");
    if (data == NULL) {
        free(code);
        abort();
    }
    oasm = fopen(argv[3], "w");
    if (oasm == NULL) {
        fclose(code);
        fclose(data);
        abort();
    }
    interpetate(code, data, stdout, oasm);
    fclose(code);
    fclose(data);
    fclose(oasm);
    return 0;
}

void rin(unsigned char* r, FILE* in)
{
    unsigned tmp;
    fscanf(in, "%u", &tmp);
    *r = tmp;
}

void rout(unsigned char r, FILE* out)
{
    fprintf(out, "%u ", r);
}

void interpetate(FILE* code, FILE* in, FILE* out, FILE* oasm)
{
    char                 buffer[64];
    unsigned char        reg[4] = { 0 };
    struct instruction_t instr;
    int                  x;
    while (fscanf(code, "%x", &x) == 1) {
        instr = disassemble(x);
        instrtostr(buffer, sizeof buffer, instr);
        fprintf(oasm, "%s\n", buffer);
        switch (instr.opc) {
        case MOVI:
            reg[3] = instr.opn.imm;
            break;
        case ADD:
            reg[instr.opn.rd] += reg[instr.opn.rs];
            break;
        case SUB:
            reg[instr.opn.rd] -= reg[instr.opn.rs];
            break;
        case MUL:
            reg[instr.opn.rd] *= reg[instr.opn.rs];
            break;
        case DIV:
            reg[instr.opn.rd] /= reg[instr.opn.rs];
            break;
        case IN:
            rin(&reg[instr.opn.r], in);
            break;
        case OUT:
            rout(reg[instr.opn.r], out);
            break;
        default:
#if __STDC_VERSION__ >= 202311L
            fprintf(stderr, "[ 0x%x : 0b%b ]: Wrong instruction\n", x, x);
#else
            fprintf(stderr, "[ 0x%x ]: Wrong instruction\n", x);
#endif
            return;
        }
    }
}
