#include "asm.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char const instr_regexp[][32] = {
    "MOVI [0-9]{1,3}",
    "ADD [A-D], [A-D]",
    "SUB [A-D], [A-D]",
    "MUL [A-D], [A-D]",
    "DIV [A-D], [A-D]",
    "IN [A-D]",
    "OUT [A-D]"
};
static char const opc_names[][8] = {
    "MOVI", "ADD", "SUB", "MUL", "DIV", "IN", "OUT"
};
static enum opcode_t const idxtoopc[] = {
    MOVI, ADD, SUB, MUL, DIV, IN, OUT
};
static const int opc_n = sizeof(instr_regexp) / sizeof(instr_regexp[0]);

struct instruction_t disassemble(unsigned char instr)
{
    struct instruction_t ret;
    if (instr >> 7 & 1) {
        if (instr >> 6 & 1) {
            switch (instr >> 2) {
            case IN:
            case OUT:
                ret.opc   = instr >> 2;
                ret.opn.r = instr & 0b11;
                break;
            default:
                ret.opc = ERR;
                break;
            }
        } else {
            switch (instr >> 4) {
            case ADD:
            case SUB:
            case MUL:
            case DIV:
                ret.opc    = instr >> 4;
                ret.opn.rd = instr >> 2 & 0b11;
                ret.opn.rs = instr & 0b11;
                break;
            default:
                ret.opc = ERR;
                break;
            }
        }
    } else {
        ret.opc     = MOVI;
        ret.opn.imm = instr;
    }
    return ret;
}

unsigned char assemble(struct instruction_t instr)
{
    unsigned char ret = 0;
    switch (instr.opc) {
    case MOVI:
        ret = instr.opn.imm;
        break;
    case ADD:
    case SUB:
    case MUL:
    case DIV:
        ret |= instr.opc << 4;
        goto two_operand;
    case IN:
    case OUT:
        ret |= instr.opc << 2;
        goto one_operand;
    case ERR:
        ret -= 1;
        break;
    one_operand:
        ret |= instr.opn.r;
        break;
    two_operand:
        ret |= instr.opn.rd << 2;
        ret |= instr.opn.rs;
        break;
    }
    return ret;
}

struct instruction_t strtoinstr(char* str)
{
    struct instruction_t ret = { 0 };
    regex_t              rgx;
    int                  i, j, tmp;
    char                 tmpd, tmps;
    int                  len;
    len = strlen(str);
    for (i = 0; i < opc_n; ++i) {
        regcomp(&rgx, instr_regexp[i], REG_EXTENDED);
        if (regexec(&rgx, str, 0, NULL, 0) == 0) {
            ret.opc = idxtoopc[i];
            j       = strlen(opc_names[i]) + 1;
            switch (ret.opc) {
            case MOVI:
                goto imm;
            case ADD:
            case SUB:
            case MUL:
            case DIV:
                goto two_operand;
            case IN:
            case OUT:
                goto one_operand;
            default:
                break;
            imm:
                sscanf(str + j, "%u", &tmp);
                if (tmp >> 8) {
                    ret.opc = ERR;
                    break;
                }
                ret.opn.imm = tmp;
                break;
            one_operand:
                sscanf(str + j, "%c", &tmpd);
                ret.opn.r = tmpd - 'A';
                break;
            two_operand:
                sscanf(str + j, "%c, %c", &tmpd, &tmps);
                ret.opn.rd = tmpd - 'A';
                ret.opn.rs = tmps - 'A';
                break;
            }
            regfree(&rgx);
            return ret;
        }
        regfree(&rgx);
    }
    ret.opc = ERR;
    return ret;
}

char* instrtostr(char* dst, int dst_sz, struct instruction_t instr)
{
    char buff[16] = { 0 };
    int  i        = 0;
    switch (instr.opc) {
    case MOVI:
        sprintf(buff, "MOVI ");
        i += 5;
        goto imm;
    case ADD:
        sprintf(buff, "ADD ");
        i += 4;
        goto two_operand;
    case SUB:
        sprintf(buff, "SUB ");
        i += 4;
        goto two_operand;
    case MUL:
        sprintf(buff, "MUL ");
        i += 4;
        goto two_operand;
    case DIV:
        sprintf(buff, "DIV ");
        i += 4;
        goto two_operand;
    case IN:
        sprintf(buff, "IN ");
        i += 3;
        goto one_operand;
    case OUT:
        sprintf(buff, "OUT ");
        i += 4;
        goto one_operand;
    default:
        sprintf(buff, "ERROR");
        break;
    imm:
        sprintf(buff + i, "%u", instr.opn.imm);
        break;
    one_operand:
        sprintf(buff + i, "%c", 'A' + instr.opn.r);
        break;
    two_operand:
        sprintf(buff + i, "%c, %c", 'A' + instr.opn.rd, 'A' + instr.opn.rs);
        break;
    }
    if (strlen(buff) >= dst_sz)
        return NULL;
    strcpy(dst, buff);
    return dst;
}
