//
// Curly
// opcodes.c: Implements the opcodes of the virtual machine.
//
// jenra
// March 14 2020
//

#include "opcodes.h"
#include <stdio.h>

// The jump table for the opcodes.
int (*opcode_funcs[256])(CurlyVM* vm, uint8_t opcode, uint8_t* pc);

// UNKNOWN
// Implements an unknown opcode.
int opcode_unknown_func(CurlyVM* vm, uint8_t opcode, uint8_t* pc)
{
	printf("Unknown opcode: 0x%02X (ignored)\n", opcode);
	return 1;
}

// NOP
// Implements no op.
int opcode_nop_func(CurlyVM* vm, uint8_t opcode, uint8_t* pc)
{
	printf("doing nothing...\n");
	return 1;
}

// BREAK
// Implements break.
int opcode_break_func(CurlyVM* vm, uint8_t opcode, uint8_t* pc)
{
	printf("HALTING!!\n");
	vm->running = false;
	return 0;
}

// i64 VALUE, f64 VALUE
// Implements loading values onto the stack.
int opcode_load_func(CurlyVM* vm, uint8_t opcode, uint8_t* pc)
{
	bool long_op = opcode & 1;
	int index = *(++pc);

	if (long_op)
	{
		index |= *(++pc) <<  8
			  |  *(++pc) << 16;
	}

	int64_t value = vm->chunk->pool.values[index];
	return 2 << long_op;
}

// init_opcodes(void) -> void
// Initialises the jump table.
void init_opcodes()
{
	for (int i = 0; i < 256; i++)
	{
		opcode_funcs[i] = opcode_unknown_func;
	}

	opcode_funcs[OPCODE_NOP			] = opcode_nop_func;
	opcode_funcs[OPCODE_BREAK		] = opcode_break_func;
	opcode_funcs[OPCODE_LOAD		] = opcode_load_func;
	opcode_funcs[OPCODE_LOAD_LONG	] = opcode_load_func;
}
