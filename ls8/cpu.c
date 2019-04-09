#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cpu.h"

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address) {
  return cpu->ram[address]; //recieves cpu and address and returns the value at the address in RAM
}

void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value) {
  cpu->ram[address] = value; 
}

void cpu_load(struct cpu *cpu, char *args[])
{
  /* char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  }; */

  /* int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address] = args[i];
    address++;
    printf("Address: %d, %d \n", address, cpu->ram[address]);
  } */

  // TODO: Replace this with something less hard-coded
  FILE *fp;
  char data[1024];
  unsigned char address = 0;
  fp = fopen(args[1], "r");

  if(!fp) {
    printf("Error opening file \n");
    exit(1);
  }
  
  while(fgets(data, sizeof data, fp) != NULL) {
    unsigned char byte = strtol(data, NULL, 2);
    if (data == NULL) {
      continue;
    }
    cpu->ram[address++] = byte;
  }

  fclose(fp);

}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction
  int PC = cpu->PC;
  unsigned char *ram = cpu->ram;
  unsigned char operand1, operand2, instruction;
  while (running) {
    /* printf("%d \n", PC);
    printf("Ram: %d \n", ram[PC]); */
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    instruction = ram[PC];
    // 2. Figure out how many operands this next instruction requires
    
    // 3. Get the appropriate value(s) of the operands following this instruction
    switch(instruction){ 
      case LDI:
        operand1 = ram[cpu->PC+1]; //The variables set in this switch don't work yet so this is pointless for now. 
        operand2 = ram[cpu->PC+2];
        break;
      case PRN: 
        operand1 = ram[cpu->PC+1];
        break;
    }
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    
    switch(instruction){
      case HLT:
        running = 0;
        break;
      case LDI:
        cpu->registers[operand1] = operand2;
        PC+=3;
        break;
      case PRN: 
        printf("%d", cpu->registers[operand1]);
        PC+=2;
        break;



    }
    
    // 6. Move the PC to the next instruction.
    
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->PC = 0;
  /* cpu->registers = calloc(8, sizeof(unsigned char));
  cpu->ram = calloc(256, sizeof(unsigned char)); */
}
