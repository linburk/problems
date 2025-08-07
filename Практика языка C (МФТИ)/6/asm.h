#pragma once

enum register_t {
    A = 0b00,
    B = 0b01,
    C = 0b10,
    D = 0b11,
    RLAST
};

enum opcode_t {
    MOVI = 0b0,
    ADD  = 0b1000,
    SUB  = 0b1001,
    MUL  = 0b1010,
    DIV  = 0b1011,
    IN   = 0b110000,
    OUT  = 0b110001,
    ERR  = 0b1111,
};

union operand_t {
    struct {
        unsigned char rd, rs;
    };
    unsigned char r;
    unsigned char imm;
};

struct instruction_t {
    enum opcode_t   opc;
    union operand_t opn;
};

struct instruction_t disassemble(unsigned char instr);

unsigned char assemble(struct instruction_t instr);

struct instruction_t strtoinstr(char* str);

char* instrtostr(char* dst, int dst_sz, struct instruction_t instr);
