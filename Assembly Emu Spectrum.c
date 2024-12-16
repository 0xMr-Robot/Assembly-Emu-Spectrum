#define _CRT_SECURE_NO_WARNINGS
#define MEMORY_SIZE 10000  // Adjust this value as needed
#define INITIAL_CAPACITY 1000 // Initial capacity for instructions and labels
#include <ctype.h> // Added to fix 'toupper' undefined
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#define MEMORY_H

#ifdef _WIN32
#include <string.h>
#define strcasecmp _stricmp
#else
#include <strings.h>
#endif

// Enum to represent number formats
typedef enum {
    Decimal,
    HEX
} NumberFormat;

// Instruction types (expanded)
typedef enum {
    // Data Movement
    INST_MOV,       // Move data
    INST_PUSH,      // Push to stack
    INST_POP,       // Pop from stack
    INST_XCHG,      // Exchange register values

    // Arithmetic
    INST_ADD,       // Addition
    INST_SUB,       // Subtraction
    INST_MUL,       // Multiplication
    INST_DIV,       // Division
    INST_INC,       // Increment
    INST_DEC,       // Decrement
    INST_NEG,       // Negate
    INST_CMP,       // Compare

    // Logical
    INST_AND,       // Bitwise AND
    INST_OR,        // Bitwise OR
    INST_XOR,       // Bitwise XOR
    INST_NOT,       // Bitwise NOT

    // Shift and Rotate
    INST_SHL,       // Shift Left
    INST_SHR,       // Shift Right
    INST_ROL,       // Rotate Left
    INST_ROR,       // Rotate Right

    // Control Flow
    INST_JMP,       // Unconditional Jump
    INST_JE,        // Jump if Equal
    INST_JNE,       // Jump if Not Equal
    INST_JG,        // Jump if Greater
    INST_JGE,       // Jump if Greater or Equal
    INST_JL,        // Jump if Less
    INST_JLE,       // Jump if Less or Equal
    INST_JA,        // Jump if Above (Unsigned Greater)
    INST_JAE,       // Jump if Above or Equal (Unsigned Greater or Equal)
    INST_JB,        // Jump if Below (Unsigned Less)
    INST_JBE,       // Jump if Below or Equal (Unsigned Less or Equal)
    INST_JO,        // Jump if Overflow
    INST_JNO,       // Jump if No Overflow
    INST_JS,        // Jump if Sign (Negative)
    INST_JNS,       // Jump if No Sign (Non-Negative)
    INST_JP,        // Jump if Parity Even
    INST_JNP,       // Jump if No Parity (Parity Odd)

    // Custom Instructions
    INST_POW,       // Power operation
    INST_ROOT,      // Root operation
    INST_AVG,       // Average operation
    INST_MOD,       // Mod operation
    INST_MIRROR,    // Mirror operation
    INST_ISPRIME,   // Check if the num is prime operation
    INST_MAX,       // Choose the max num of 3 PARAMETERS
    INST_MIN,       // Choose the min num of 3 parameters

    // Misc
    INST_LABEL,     // Label for jumps
    INST_COMMENT,
    INST_NOP,        // No operation
    INST_INT         // INT
} InstructionType;

#define MEMORY_SIZE 1024 * 1024  // Memory size is 1MB
uint8_t memory[MEMORY_H];
void write_memory(void* emu, uint64_t address, uint64_t value,size_t size);
uint64_t read_memory(void* emu, uint64_t address, size_t size) {
    // Check if the address is within valid memory bounds
    if (address >= MEMORY_SIZE || address + size > MEMORY_SIZE) {
        fprintf(stderr, "Error: Memory access out of bounds at address 0x%llx\n", address);
        return 0;
    }

    // Handle different size reads
    uint64_t result = 0;
    switch (size) {
        case sizeof(uint8_t):
            result = *(uint8_t*)&memory[address];
        break;
        case sizeof(uint16_t):
            result = *(uint16_t*)&memory[address];
        break;
        case sizeof(uint32_t):
            result = *(uint32_t*)&memory[address];
        break;
        case sizeof(uint64_t):
            result = *(uint64_t*)&memory[address];
        break;
        default:
            fprintf(stderr, "Error: Unsupported memory read size %zu\n", size);
        return 0;
    }

    return result;
}

// Comprehensive Emulator Structure with Multiple Register Sizes
typedef struct {
    // General-purpose registers with multiple sizes
    union {
        struct {
            union {
                uint64_t rax;   // 64-bit
                struct {
                    uint32_t eax;   // 32-bit
                };
            };
            union {
                uint64_t rbx;
                struct {
                    uint32_t ebx;

                };
            };
            union {
                uint64_t rcx;
                struct {
                    uint32_t ecx;

                };
            };
            union {
                uint64_t rdx;
                struct {
                    uint32_t edx;

                };
            };
            union {
                uint64_t rsi;
                struct {
                    uint32_t esi;

                };
            };
            union {
                uint64_t rdi;
                struct {
                    uint32_t edi;

                };
            };
            union {
                uint64_t rsp;
                struct {
                    uint32_t esp;

                };
            };
            union {
                uint64_t rbp;
                struct {
                    uint32_t ebp;

                };
            };
            // Additional general-purpose registers
            union {
                uint64_t r8;
                struct {
                    uint32_t r8d;

                };
            };
            union {
                uint64_t r9;
                struct {
                    uint32_t r9d;

                };
            };
            union {
                uint64_t r10;
                struct {
                    uint32_t r10d;

                };
            };
            union {
                uint64_t r11;
                struct {
                    uint32_t r11d;

                };
            };
            union {
                uint64_t r12;
                struct {
                    uint32_t r12d;

                };
            };
            union {
                uint64_t r13;
                struct {
                    uint32_t r13d;

                };
            };
            union {
                uint64_t r14;
                struct {
                    uint32_t r14d;

                };
            };
            union {
                uint64_t r15;
                struct {
                    uint32_t r15d;

                };
            };
        };
        uint64_t registers[16];  // Allow indexing by number
    };

    // Instruction pointer
    uint64_t rip;

    // Flags register (more comprehensive)
    struct {
        uint8_t carry : 1;      // CF: Carry flag
        uint8_t reserved1 : 1;  // Reserved
        uint8_t parity : 1;     // PF: Parity flag
        uint8_t reserved2 : 1;  // Reserved
        uint8_t auxiliary : 1;  // AF: Auxiliary carry flag
        uint8_t reserved3 : 1;  // Reserved
        uint8_t zero : 1;       // ZF: Zero flag
        uint8_t sign : 1;       // SF: Sign flag
        uint8_t trap : 1;       // TF: Trap flag
        uint8_t interrupt : 1;  // IF: Interrupt flag
        uint8_t direction : 1;  // DF: Direction flag
        uint8_t overflow : 1;   // OF: Overflow flag
        uint8_t reserved4 : 4;  // Reserved for future use
        uint8_t alignment : 1;  // Alignment check flag
    } flags;

    // Segment registers
    uint16_t cs, ds, ss, es, fs, gs;

    // Memory representation
    uint8_t* memory;
    size_t memory_size;

    // Stack
    uint8_t* stack;
    size_t stack_size;
} Emulator;


// Instruction structure with NumberFormat
typedef struct {
    InstructionType type;
    char label[32];        // Label name (for INST_LABEL)
    uint64_t* dest_reg;    // Destination register
    uint64_t* src_reg;     // Source register (if applicable)
    uint64_t* aux_reg;     // Auxiliary register (for some operations)
    uint64_t immediate;    // Immediate value
    bool dest_is_memory;   // True if destination is memory
    bool src_is_memory;    // True if source is memory
    bool jump_is_memory;
    bool aux_is_memory;
    uint64_t memory_address;
    uint64_t target_address;
    NumberFormat format;   // Number format of the immediate value
    uint64_t rd;           // Instruction index
    uint64_t dest_mem_address;
    uint64_t src_mem_address;
    uint64_t aux_mem_address;
    uint64_t jump_mem_address;
    uint64_t aux_immediate;
    uint64_t src_immediate;
    char dest_reg_name[32]; // Original destination register name
    char src_reg_name[32];  // Original source register name
    char aux_reg_name[32];  // Original Aux Register Name
    uint64_t function;
    char* immediate_string;
    bool src_is_string;     // Added: True if source is a string literal
    char src_string[256];   // Added: Buffer to hold the string literal
} Instruction;

//Function to parse labels and map them to instruction indices
typedef struct {
    char label[32];
    size_t index;
} Label;


// Global interrupt handler map
typedef void (*InterruptHandler)(Emulator*, Instruction*);
InterruptHandler interrupt_handlers[256] = { NULL };

// Global tracing flag
bool tracing_enabled = false;

// Function prototypes
Emulator* create_emulator(size_t memory_size, size_t stack_size);
void destroy_emulator(Emulator* emu);
void execute_instruction(Emulator* emu, Instruction* inst, size_t inst_num, Label* labels, size_t label_count);
void print_emulator_state(Emulator* emu, const char* phase);
void print_reg(const char* name, uint64_t value, NumberFormat format, size_t size);
const char* get_register_name(Emulator* emu, uint64_t* reg_ptr);
uint64_t* get_register_pointer(Emulator* emu, const char* reg_name);
InstructionType get_instruction_type(const char* instr_str);
void execute_file_instructions(Emulator* emu, const char* filename);
void run_comprehensive_example(Emulator* emu);
void resize_instructions(Instruction** instructions, size_t* capacity);
void resize_labels(Label** labels, size_t* capacity);
void demonstrate_memory_operations(Emulator* emu);
void int_21h_handler(Emulator* emu, Instruction* inst);
void int_22h_handler(Emulator* emu, Instruction* inst);
void int_23h_handler(Emulator* emu, Instruction* inst);
void initialize_interrupt_handlers() {
    interrupt_handlers[0x21] = int_21h_handler; // Map INT 21h to the MessageBox handler
    interrupt_handlers[0x22] = int_22h_handler; // Map INT 22h to the WriteConsole handler
    interrupt_handlers[0x23] = int_23h_handler; // Map INT 23h to the ReadConsole handler
}

uint64_t pop(Emulator* emu);
void push(Emulator* emu, uint64_t value);
void push_to_stack(Emulator* emu, uint64_t value);
uint64_t pop_from_stack(Emulator* emu);

// Custom instruction implementations
void execute_root_instruction(Emulator* emu, Instruction* inst);
void execute_avg_instruction(Emulator* emu, Instruction* inst);
void execute_pow_instruction(Emulator* emu, Instruction* inst);
void execute_mod_instruction(Emulator* emu, Instruction* inst);
bool is_prime(uint64_t n);
void execute_isprime_instruction(Emulator* emu, Instruction* inst);
uint64_t mirror_decimal(uint64_t decimal_value);
void execute_mirror_instruction(Emulator* emu, Instruction* inst);
void execute_min_instruction(Emulator* emu, Instruction* inst);
void execute_max_instruction(Emulator* emu, Instruction* inst);

// Create a new emulator instance
Emulator* create_emulator(size_t memory_size, size_t stack_size) {
    Emulator* emu = malloc(sizeof(Emulator));
    if (!emu) {
        fprintf(stderr, "Memory allocation failed for emulator\n");
        exit(1);
    }

    // Zero out all registers
    memset(emu->registers, 0, sizeof(emu->registers));

    // Initialize flags
    memset(&emu->flags, 0, sizeof(emu->flags));

    // Initialize segment registers
    emu->cs = emu->ds = emu->ss = emu->es = emu->fs = emu->gs = 0;

    // Allocate memory
    emu->memory = calloc(memory_size, sizeof(uint8_t));
    if (!emu->memory) {
        fprintf(stderr, "Memory allocation failed for emulator memory\n");
        free(emu);
        exit(1);
    }
    emu->memory_size = memory_size;

    // Allocate stack
    emu->stack = calloc(stack_size, sizeof(uint8_t));
    if (!emu->stack) {
        fprintf(stderr, "Memory allocation failed for stack\n");
        free(emu->memory);
        free(emu);
        exit(1);
    }
    emu->stack_size = stack_size;

    // Initialize stack pointer (pointing to the top of the stack)
    emu->rsp = (uint64_t)(uintptr_t)(emu->stack) + stack_size - sizeof(uint64_t);

    // Initialize instruction pointer
    emu->rip = 0;

    return emu;
}



void initialize_emulator(Emulator* emu, size_t memory_size, size_t stack_size) {
    // Allocate memory for main memory
    emu->memory = (uint8_t*)malloc(memory_size);
    if (!emu->memory) {
        fprintf(stderr, "Failed to allocate emulator memory!\n");
        exit(1);
    }
    emu->memory_size = memory_size;
    memset(emu->memory, 0, memory_size); // Initialize memory to zero

    // Allocate memory for the stack
    emu->stack = (uint8_t*)malloc(stack_size);
    if (!emu->stack) {
        fprintf(stderr, "Failed to allocate stack memory!\n");
        free(emu->memory); // Clean up memory if stack allocation fails
        exit(1);
    }
    emu->stack_size = stack_size;
    memset(emu->stack, 0, stack_size); // Initialize stack to zero

    // Initialize the stack pointer (RSP) to the top of the stack
    emu->rsp = stack_size;

    printf("Emulator initialized with %zu bytes of memory and %zu bytes of stack.\n", memory_size, stack_size);
}


void push(Emulator* emu, uint64_t value) {
    if (emu->rsp < sizeof(uint64_t)) {
        fprintf(stderr, "Stack overflow!\n");
        exit(1);
    }
    emu->rsp -= sizeof(uint64_t); // Decrement stack pointer
    memcpy(&emu->stack[emu->rsp], &value, sizeof(uint64_t)); // Write to stack
}

uint64_t pop(Emulator* emu) {
    if (emu->rsp >= emu->stack_size) {
        fprintf(stderr, "Stack underflow!\n");
        exit(1);
    }
    uint64_t value = 0;
    memcpy(&value, &emu->stack[emu->rsp], sizeof(uint64_t)); // Read from stack
    emu->rsp += sizeof(uint64_t); // Increment stack pointer
    return value;
}


// Function to resize the instruction array
void resize_instructions(Instruction** instructions, size_t* capacity) {
    *capacity *= 2;
    *instructions = realloc(*instructions, *capacity * sizeof(Instruction));
    if (*instructions == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for instructions\n");
        exit(1);
    }
}

// Function to resize the label array
void resize_labels(Label** labels, size_t* capacity) {
    *capacity *= 2;
    *labels = realloc(*labels, *capacity * sizeof(Label));
    if (*labels == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for labels\n");
        exit(1);
    }
}

void int_21h_handler(Emulator* emu, Instruction* inst) {
    if (inst->immediate == 0x09) { // Display a message
        // Read the value from memory starting at the address in RAX
        uint64_t message_address = emu->rax;
        if (message_address >= MEMORY_SIZE) { // Check bounds
            fprintf(stderr, "Error: Message address out of bounds\n");
            exit(EXIT_FAILURE);
        }

        // Read the ASCII string from memory
        char message[256]; // Buffer to hold the message
        size_t i = 0;
        while (i < sizeof(message) - 1) {
            uint8_t byte = read_memory(emu, message_address + i, sizeof(uint8_t));
            message[i++] = byte;
            if (byte == '\0') break; // Stop at null terminator
        }
        message[i] = '\0'; // Ensure null-termination

        // Display the message in a message box
        MessageBoxA(NULL, message, "Message from Emulator", MB_OK);
    }
}
void int_22h_handler(Emulator* emu, Instruction* inst) {
    if (inst->immediate == 0x01) { // Write a text value to the console
        // Read the value from memory starting at the address in RAX
        uint64_t value_address = emu->rax;
        if (value_address >= MEMORY_SIZE) { // Check bounds
            fprintf(stderr, "Error: Value address out of bounds\n");
            exit(EXIT_FAILURE);
        }

        // Read the ASCII string from memory
        char message[256]; // Buffer to hold the message
        size_t i = 0;
        while (i < sizeof(message) - 1) {
            uint8_t byte = read_memory(emu, value_address + i, sizeof(uint8_t));
            if (byte == '\0') break; // Stop at null terminator
            message[i++] = byte;
        }
        message[i] = '\0'; // Null-terminate the string

        // Write the ASCII string to the console
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD bytesWritten;
        WriteConsole(hConsole, message, strlen(message), &bytesWritten, NULL);
    }
}
void int_23h_handler(Emulator* emu, Instruction* inst) {
    if (inst->immediate == 0x01) { // Read from console
        char buffer[256];
        // Read input from the console
        printf("Enter Input: ");  // Added space here
        HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
        DWORD bytesRead;
        ReadConsole(hConsole, buffer, 255, &bytesRead, NULL);
        buffer[bytesRead] = '\0'; // Null-terminate the string

        // Debug log: Print the input string
        printf("INT 23h: Read input value: '0x%llX' \n", buffer);  // Added newline here

        // Write the input string to memory starting at the address in RAX
        uint64_t value_address = emu->rax;

        // Debug log: Print the memory address
        printf("INT 23h: Writing to memory address: 0x%llX\n", value_address);  // Added newline here

        // Check if the memory address is valid
        if (value_address >= MEMORY_SIZE) {
            fprintf(stderr, "Error: Memory address 0x%llX is out of bounds\n", value_address);
            exit(EXIT_FAILURE);
        }

        // Check if the input string fits in memory
        if (value_address + bytesRead > MEMORY_SIZE) {
            fprintf(stderr, "Error: Input string too large for memory\n");
            exit(EXIT_FAILURE);
        }

        // Write each character to memory
        for (size_t i = 0; i < bytesRead; ++i) {
            write_memory(emu, value_address + i, buffer[i], sizeof(uint8_t));
        }

        // Null-terminate the string in memory
        write_memory(emu, value_address + bytesRead, '\0', sizeof(uint8_t));

        // Debug log: Confirm the write operation
       printf("INT 23h: Wrote value 0x%llX to memory address 0x%llX\n", buffer, value_address);  // Added newline here
    }
}

// Free emulator resources
void destroy_emulator(Emulator* emu) {
    if (emu) {
        free(emu->memory);
        free(emu->stack);
        free(emu);
    }
}

// Function to get register name from pointer (Updated)
const char* get_register_name(Emulator* emu, uint64_t* reg_ptr) {
    void* ptr = (void*)reg_ptr; // Cast to void* to allow comparison

    // Check 32-bit registers first
    if (ptr == (void*)&emu->eax) return "EAX";
    if (ptr == (void*)&emu->ebx) return "EBX";
    if (ptr == (void*)&emu->ecx) return "ECX";
    if (ptr == (void*)&emu->edx) return "EDX";
    if (ptr == (void*)&emu->esi) return "ESI";
    if (ptr == (void*)&emu->edi) return "EDI";
    if (ptr == (void*)&emu->esp) return "ESP";
    if (ptr == (void*)&emu->ebp) return "EBP";
    if (ptr == (void*)&emu->r8d) return "R8D";
    if (ptr == (void*)&emu->r9d) return "R9D";
    if (ptr == (void*)&emu->r10d) return "R10D";
    if (ptr == (void*)&emu->r11d) return "R11D";
    if (ptr == (void*)&emu->r12d) return "R12D";
    if (ptr == (void*)&emu->r13d) return "R13D";
    if (ptr == (void*)&emu->r14d) return "R14D";
    if (ptr == (void*)&emu->r15d) return "R15D";

    // Then check 64-bit registers
    if (ptr == (void*)&emu->rax) return "RAX";
    if (ptr == (void*)&emu->rbx) return "RBX";
    if (ptr == (void*)&emu->rcx) return "RCX";
    if (ptr == (void*)&emu->rdx) return "RDX";
    if (ptr == (void*)&emu->rsi) return "RSI";
    if (ptr == (void*)&emu->rdi) return "RDI";
    if (ptr == (void*)&emu->rsp) return "RSP";
    if (ptr == (void*)&emu->rbp) return "RBP";
    if (ptr == (void*)&emu->r8) return "R8";
    if (ptr == (void*)&emu->r9) return "R9";
    if (ptr == (void*)&emu->r10) return "R10";
    if (ptr == (void*)&emu->r11) return "R11";
    if (ptr == (void*)&emu->r12) return "R12";
    if (ptr == (void*)&emu->r13) return "R13";
    if (ptr == (void*)&emu->r14) return "R14";
    if (ptr == (void*)&emu->r15) return "R15";

    return "UNKNOWN";
}



// Function to get register pointer from name
uint64_t* get_register_pointer(Emulator* emu, const char* reg_name) {
    // Convert register name to uppercase for case-insensitive comparison
    char reg_upper[16];
    size_t len = strlen(reg_name);
    if (len >= sizeof(reg_upper)) len = sizeof(reg_upper) - 1;
    for (size_t i = 0; i < len; i++) {
        reg_upper[i] = toupper((unsigned char)reg_name[i]);
    }
    reg_upper[len] = '\0';

    if (strcmp(reg_upper, "RAX") == 0) return &emu->rax;
    if (strcmp(reg_upper, "EAX") == 0) return (uint64_t*)&emu->eax;

    if (strcmp(reg_upper, "RBX") == 0) return &emu->rbx;
    if (strcmp(reg_upper, "EBX") == 0) return (uint64_t*)&emu->ebx;

    if (strcmp(reg_upper, "RCX") == 0) return &emu->rcx;
    if (strcmp(reg_upper, "ECX") == 0) return (uint64_t*)&emu->ecx;


    if (strcmp(reg_upper, "RDX") == 0) return &emu->rdx;
    if (strcmp(reg_upper, "EDX") == 0) return (uint64_t*)&emu->edx;


    if (strcmp(reg_upper, "RSI") == 0) return &emu->rsi;
    if (strcmp(reg_upper, "ESI") == 0) return (uint64_t*)&emu->esi;


    if (strcmp(reg_upper, "RDI") == 0) return &emu->rdi;
    if (strcmp(reg_upper, "EDI") == 0) return (uint64_t*)&emu->edi;



    if (strcmp(reg_upper, "RSP") == 0) return &emu->rsp;
    if (strcmp(reg_upper, "ESP") == 0) return (uint64_t*)&emu->esp;


    if (strcmp(reg_upper, "RBP") == 0) return &emu->rbp;
    if (strcmp(reg_upper, "EBP") == 0) return (uint64_t*)&emu->ebp;


    if (strcmp(reg_upper, "R8") == 0) return &emu->r8;
    if (strcmp(reg_upper, "R8D") == 0) return (uint64_t*)&emu->r8d;


    if (strcmp(reg_upper, "R9") == 0) return &emu->r9;
    if (strcmp(reg_upper, "R9D") == 0) return (uint64_t*)&emu->r9d;


    if (strcmp(reg_upper, "R10") == 0) return &emu->r10;
    if (strcmp(reg_upper, "R10D") == 0) return (uint64_t*)&emu->r10d;

    if (strcmp(reg_upper, "R11") == 0) return &emu->r11;
    if (strcmp(reg_upper, "R11D") == 0) return (uint64_t*)&emu->r11d;

    if (strcmp(reg_upper, "R12") == 0) return &emu->r12;
    if (strcmp(reg_upper, "R12D") == 0) return (uint64_t*)&emu->r12d;

    if (strcmp(reg_upper, "R13") == 0) return &emu->r13;
    if (strcmp(reg_upper, "R13D") == 0) return (uint64_t*)&emu->r13d;

    if (strcmp(reg_upper, "R14") == 0) return &emu->r14;
    if (strcmp(reg_upper, "R14D") == 0) return (uint64_t*)&emu->r14d;


    if (strcmp(reg_upper, "R15") == 0) return &emu->r15;
    if (strcmp(reg_upper, "R15D") == 0) return (uint64_t*)&emu->r15d;

    return NULL;
}

// Function to determine register size based on register name
size_t get_register_size(const char* reg_name) {
    // Convert register name to uppercase for case-insensitive comparison
    char reg_upper[16];
    size_t len = strlen(reg_name);
    if (len >= sizeof(reg_upper)) len = sizeof(reg_upper) - 1;
    for (size_t i = 0; i < len; i++) {
        reg_upper[i] = toupper((unsigned char)reg_name[i]);
    }
    reg_upper[len] = '\0';

    // Determine size based on suffix
    if (strstr(reg_upper, "D")) return 32;
    if (strlen(reg_upper) >= 2 && reg_upper[1] == 'D') return 32;
    if (strlen(reg_upper) >= 2 && reg_upper[1] == 'I') return 16;
    return 64;
}

// Function to map instruction string to enum (case-insensitive)
InstructionType get_instruction_type(const char* instr_str) {
    if (strcasecmp(instr_str, "MOV") == 0) return INST_MOV;
    if (strcasecmp(instr_str, "PUSH") == 0) return INST_PUSH;
    if (strcasecmp(instr_str, "POP") == 0) return INST_POP;
    if (strcasecmp(instr_str, "XCHG") == 0) return INST_XCHG;
    if (strcasecmp(instr_str, "ADD") == 0) return INST_ADD;
    if (strcasecmp(instr_str, "SUB") == 0) return INST_SUB;
    if (strcasecmp(instr_str, "MUL") == 0) return INST_MUL;
    if (strcasecmp(instr_str, "DIV") == 0) return INST_DIV;
    if (strcasecmp(instr_str, "INC") == 0) return INST_INC;
    if (strcasecmp(instr_str, "DEC") == 0) return INST_DEC;
    if (strcasecmp(instr_str, "NEG") == 0) return INST_NEG;
    if (strcasecmp(instr_str, "CMP") == 0) return INST_CMP;
    if (strcasecmp(instr_str, "AND") == 0) return INST_AND;
    if (strcasecmp(instr_str, "OR") == 0) return INST_OR;
    if (strcasecmp(instr_str, "XOR") == 0) return INST_XOR;
    if (strcasecmp(instr_str, "NOT") == 0) return INST_NOT;
    if (strcasecmp(instr_str, "SHL") == 0) return INST_SHL;
    if (strcasecmp(instr_str, "SHR") == 0) return INST_SHR;
    if (strcasecmp(instr_str, "ROL") == 0) return INST_ROL;
    if (strcasecmp(instr_str, "ROR") == 0) return INST_ROR;
    if (strcasecmp(instr_str, "JMP") == 0) return INST_JMP;
    if (strcasecmp(instr_str, "JE") == 0) return INST_JE;
    if (strcasecmp(instr_str, "JNE") == 0) return INST_JNE;
    if (strcasecmp(instr_str, "JG") == 0) return INST_JG;
    if (strcasecmp(instr_str, "JGE") == 0) return INST_JGE;
    if (strcasecmp(instr_str, "JL") == 0) return INST_JL;
    if (strcasecmp(instr_str, "JLE") == 0) return INST_JLE;
    if (strcasecmp(instr_str, "JA") == 0) return INST_JA;
    if (strcasecmp(instr_str, "JAE") == 0) return INST_JAE;
    if (strcasecmp(instr_str, "JB") == 0) return INST_JB;
    if (strcasecmp(instr_str, "JBE") == 0) return INST_JBE;
    if (strcasecmp(instr_str, "JO") == 0) return INST_JO;
    if (strcasecmp(instr_str, "JNO") == 0) return INST_JNO;
    if (strcasecmp(instr_str, "JS") == 0) return INST_JS;
    if (strcasecmp(instr_str, "JNS") == 0) return INST_JNS;
    if (strcasecmp(instr_str, "JP") == 0) return INST_JP;
    if (strcasecmp(instr_str, "JNP") == 0) return INST_JNP;
    if (strcasecmp(instr_str, "POW") == 0) return INST_POW;
    if (strcasecmp(instr_str, "ROOT") == 0) return INST_ROOT;
    if (strcasecmp(instr_str, "AVG") == 0) return INST_AVG;
    if (strcasecmp(instr_str, "MOD") == 0) return INST_MOD;
    if (strcasecmp(instr_str, "MIRROR") == 0) return INST_MIRROR;
    if (strcasecmp(instr_str, "ISPRIME") == 0) return INST_ISPRIME;
    if (strcasecmp(instr_str, "MAX") == 0) return INST_MAX;
    if (strcasecmp(instr_str, "MIN") == 0) return INST_MIN;
    if (strcasecmp(instr_str, "INT") == 0) return INST_INT;
    if (instr_str[0] == ';') return INST_COMMENT; // Handle comments starting with ';'
    if (strcasecmp(instr_str, "NOP") == 0) return INST_NOP;
    if (strchr(instr_str, ':') != NULL) return INST_LABEL; // Handle labels ending with ':'
    return INST_NOP; // Default to NOP for unknown instructions
}

// Function to find a label in the label array
size_t find_label(const Label* labels, size_t label_count, const char* label) {
    for (size_t i = 0; i < label_count; i++) {
        if (strcmp(labels[i].label, label) == 0) {
            return labels[i].index;
        }
    }
    return -1; // Label not found
}

// Function to write a 64-bit value to memory
void write_memory(void* emu, uint64_t address, uint64_t value, size_t size) {
    // Check if the address is within valid memory bounds
    if (address >= MEMORY_SIZE || address + size > MEMORY_SIZE) {
        fprintf(stderr, "Error: Memory access out of bounds at address 0x%llx\n", address);
        return;
    }

    // Handle different size writes
    switch (size) {
        case sizeof(uint8_t):
            *(uint8_t*)&memory[address] = (uint8_t)value;
        break;
        case sizeof(uint16_t):
            *(uint16_t*)&memory[address] = (uint16_t)value;
        break;
        case sizeof(uint32_t):
            *(uint32_t*)&memory[address] = (uint32_t)value;
        break;
        case sizeof(uint64_t):
            *(uint64_t*)&memory[address] = value;
        break;
        default:
            fprintf(stderr, "Error: Unsupported memory write size %zu\n", size);
        return;
    }
}


// Custom ROOT instruction implementation
void execute_root_instruction(Emulator* emu, Instruction* inst) {
    // Get base value
    uint64_t base;
    if (inst->src_reg) {
        base = *inst->src_reg;
        printf("ROOT: Using base value from register: %lu\n", base);
    }
    else if (inst->src_is_memory) {
        base = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
        printf("ROOT: Using base value from memory [0x%lx]: %lu\n", inst->src_mem_address, base);
    }
    else {
        base = inst->immediate;
        printf("ROOT: Using immediate base value: %lu\n", base);
    }

    // Get exponent value
    uint64_t exponent;
    if (inst->aux_reg) {
        exponent = *inst->aux_reg;
        printf("ROOT: Using exponent from register: %lu\n", exponent);
    }
    else if (inst->aux_is_memory) {
        exponent = read_memory(emu, inst->aux_mem_address, sizeof(uint64_t));
        printf("ROOT: Using exponent from memory [0x%lx]: %lu\n", inst->aux_mem_address, exponent);
    }
    else {
        exponent = inst->aux_immediate;
        printf("ROOT: Using immediate exponent value: %lu\n", exponent);
    }

    // Check for zero exponent
    if (exponent == 0) {
        fprintf(stderr, "ROOT: Division by zero (exponent is zero)\n");
        return;
    }

    // Calculate the root
    double result = pow((double)base, 1.0 / (double)exponent);
    uint64_t final_result = (uint64_t)result;

    // Store result
    if (inst->dest_reg) {
        *inst->dest_reg = final_result;
        printf("ROOT: Stored result in register: %lu\n", final_result);
    }
    else if (inst->dest_is_memory) {
        write_memory(emu, inst->dest_mem_address, final_result, sizeof(uint64_t));
        printf("ROOT: Stored result in memory [0x%lx]: %lu\n", inst->dest_mem_address, final_result);
    }

    // Update flags
    emu->flags.zero = (final_result == 0);
    emu->flags.sign = (final_result & (1ULL << 63)) != 0;
}

// Custom AVG instruction implementation
void execute_avg_instruction(Emulator* emu, Instruction* inst) {
    uint64_t val1 = 0, val2 = 0, val3 = 0;

    // Get first value (always from destination register)
    if (!inst->dest_reg) {
        fprintf(stderr, "AVG: First operand must be a register\n");
        return;
    }
    val1 = *inst->dest_reg;
    printf("AVG: First value from register: 0x%llX\n", (unsigned long long)val1);

    // Get second value (from register, memory, or immediate)
    if (inst->src_reg) {
        val2 = *inst->src_reg;
        printf("AVG: Second value from register: 0x%llX\n", (unsigned long long)val2);
    }
    else if (inst->src_is_memory) {
        val2 = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
        printf("AVG: Second value from memory: 0x%llX\n", (unsigned long long)val2);
    }
    else if (inst->src_immediate) {
        val2 = inst->immediate;
        printf("AVG: Second value from immediate: 0x%llX\n", (unsigned long long)val2);
    }
    else {
        fprintf(stderr, "AVG: Invalid second operand\n");
        return;
    }

    // Get third value (from register, memory, or immediate)
    if (inst->aux_reg) {
        val3 = *inst->aux_reg;
        printf("AVG: Third value from register: 0x%llX\n", (unsigned long long)val3);
    }
    else if (inst->aux_is_memory) {
        val3 = read_memory(emu, inst->aux_mem_address, sizeof(uint64_t));
        printf("AVG: Third value from memory: 0x%llX\n", (unsigned long long)val3);
    }
    else if (inst->aux_immediate) {
        val3 = inst->aux_immediate;
        printf("AVG: Third value from immediate: 0x%llX\n", (unsigned long long)val3);
    }
    else {
        fprintf(stderr, "AVG: Invalid third operand\n");
        return;
    }

    // Calculate average
    uint64_t sum = val1 + val2 + val3;
    uint64_t avg = sum / 3;

    // Store result in destination register
    *inst->dest_reg = avg;
    printf("AVG: Result 0x%llX stored in destination register\n", (unsigned long long)avg);

    // Update flags
    emu->flags.zero = (avg == 0);
    emu->flags.sign = (avg & (1ULL << 63)) ? 1 : 0;
}

// Custom POW instruction implementation

void execute_pow_instruction(Emulator* emu, Instruction* inst) {
    uint64_t base = 0, exponent = 0;

    // Determine the base value (from memory or register)
    if (inst->dest_is_memory) {
        base = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
        printf("POW: Reading base value 0x%llX from memory address 0x%llX\n",
               base, inst->dest_mem_address);
    } else if (inst->dest_reg) {
        base = (*inst->dest_reg);
        printf("POW: Using base value 0x%llX from destination register\n",
               base);
    } else {
        fprintf(stderr, "POW: Invalid destination operand\n");
        return;
    }

    // Determine the exponent value (from memory, register, or immediate)
    if (inst->src_is_memory) {
        exponent = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
        printf("POW: Reading exponent value 0x%llX from memory address 0x%llX\n",
               exponent, inst->src_mem_address);
    } else if (inst->src_reg) {
        exponent = (*inst->src_reg);
        printf("POW: Using exponent value 0x%llX from source register\n",
               exponent);
    } else {
        exponent = (inst->immediate);
        printf("POW: Using immediate exponent value 0x%llX\n", exponent);
    }

    // Perform the power operation
    double result = pow((double)base, (double)exponent);

    // Check if the result is within the valid range for uint64_t
    if (result > (double)UINT64_MAX || result < 0) {
        fprintf(stderr, "POW: Result overflow or invalid (result = %lf)\n", result);
        return;
    }

    // Check if the result is an exact integer
    if (result != floor(result)) {
        fprintf(stderr, "POW: Result is not an exact integer (result = %lf)\n", result);
        return;
    }

    // Convert the result to uint64_t
    uint64_t res = (uint64_t)result;

    // Handle result based on destination operand type
    if (inst->dest_is_memory) {
        write_memory(emu, inst->dest_mem_address, res, sizeof(uint64_t));
        printf("POW: Writing result 0x%llX to memory address 0x%llX\n",
               res, inst->dest_mem_address);
    } else if (inst->dest_reg) {
        *inst->dest_reg = res;
        printf("POW: Writing result 0x%llX to destination register\n", res);
    }
}

// Custom MOD instruction implementation
void execute_mod_instruction(Emulator* emu, Instruction* inst) {
    uint64_t dividend = 0, divisor = 0;

    // Determine the dividend (destination operand)
    if (inst->dest_is_memory) {
        dividend = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
        printf("MOD: Reading dividend value 0x%llX from memory address 0x%llX\n",
            (uint64_t)dividend, inst->dest_mem_address);
    }
    else if (inst->dest_reg) {
        dividend = (*inst->dest_reg);
        printf("MOD: Using dividend value 0x%llX from destination register\n",
            (uint64_t)dividend);
    }
    else {
        fprintf(stderr, "MOD: Invalid destination operand\n");
        return;
    }

    // Determine the divisor (source operand)
    if (inst->src_is_memory) {
        divisor = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
        printf("MOD: Reading divisor value 0x%llX from memory address 0x%llX\n",
            (uint64_t)divisor, inst->src_mem_address);
    }
    else if (inst->src_reg) {
        divisor = (*inst->src_reg);
        printf("MOD: Using divisor value 0x%llX from source register\n",
            (uint64_t)divisor);
    }
    else {
        divisor = (inst->immediate);
        printf("MOD: Using immediate divisor value 0x%llX\n", (uint64_t)divisor);
    }

    // Handle division by zero
    if (divisor == 0) {
        fprintf(stderr, "MOD: Division by zero error\n");
        return;
    }

    // Perform the modulus operation
    uint64_t result = dividend % divisor;

    // Handle result based on destination operand type
    if (inst->dest_is_memory) {
        write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));
        printf("MOD: Writing result 0x%llX to memory address 0x%llX\n",
            (uint64_t)result, inst->dest_mem_address);
    }
    else if (inst->dest_reg) {
        *inst->dest_reg = result;
        printf("MOD: Writing result 0x%llX to destination register\n", (uint64_t)result);
    }

    // Set flags (optional, if flags are implemented in the emulator)
    emu->flags.zero = (result == 0) ? 1 : 0;         // Zero Flag (ZF)
    emu->flags.sign = (result & (1ULL << 63)) ? 1 : 0; // Sign Flag (SF)
}

// Function to check if a number is prime
bool is_prime(uint64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (uint64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Function to execute the isprime instruction
void execute_isprime_instruction(Emulator* emu, Instruction* inst) {
    if (!inst->src_reg && !inst->src_is_memory) {
        fprintf(stderr, "ISPRIME: Invalid source operand\n");
        return;
    }

    uint64_t src_value = 0;

    // Determine the source operand value (memory or register)
    if (inst->src_is_memory) {
        src_value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
        printf("ISPRIME: Reading source value 0x%llX from memory address 0x%llX\n",
            (uint64_t)src_value, inst->src_mem_address);
    }
    else if (inst->src_reg) {
        src_value = *inst->src_reg;
        printf("ISPRIME: Using source value 0x%llX from source register\n",
            (uint64_t)src_value);
    }

    bool prime = is_prime(src_value);

    if (inst->dest_reg) {
        *inst->dest_reg = prime ? 1 : 0;
        printf("ISPRIME: Writing result 0x%llX to destination register\n", (uint64_t)(prime ? 1 : 0));
    }
    else if (inst->dest_is_memory) {
        write_memory(emu, inst->dest_mem_address, prime ? 1 : 0, sizeof(uint64_t));
        printf("ISPRIME: Writing result 0x%llX to memory address 0x%llX\n",
            (uint64_t)(prime ? 1 : 0), inst->dest_mem_address);
    }
    else {
        fprintf(stderr, "ISPRIME: Invalid destination operand\n");
        return;
    }

    printf("Executed ISPRIME Instruction: %" PRIu64 " is %s\n",
        src_value, prime ? "TRUE" : "FALSE");

    // Determine register size and ensure the result fits if the destination is a register
    if (inst->dest_reg) {
        const char* dest_name = get_register_name(emu, inst->dest_reg);
        size_t size = get_register_size(dest_name);

        // Ensure the result fits in the register size
        if (size == 32 && *inst->dest_reg > 0xFFFFFFFF) {
            fprintf(stderr, "Error: Result 0x%016" PRIx64 " exceeds 32-bit register size for %s\n",
                *inst->dest_reg, dest_name);
        }
    }
}

// Function to mirror decimal bits
uint64_t mirror_decimal(uint64_t decimal_value) {
    uint64_t mirrored = 0;
    uint64_t temp = decimal_value;

    // Calculate the bit-width of the decimal value
    int bit_width = 0;
    if (decimal_value == 0) bit_width = 1;
    while (temp > 0) {
        temp >>= 1;
        bit_width++;
    }

    // Perform bit mirroring
    for (int i = 0; i < bit_width; ++i) {
        mirrored <<= 1;                         // Shift mirrored value left
        mirrored |= (decimal_value & 1);        // Add the least significant bit of value to mirrored
        decimal_value >>= 1;                    // Shift decimal_value right to process the next bit
    }

    return mirrored;
}

// Custom MIRROR instruction implementation
void execute_mirror_instruction(Emulator* emu, Instruction* inst) {
    if (!inst->src_reg && !inst->src_is_memory) {
        fprintf(stderr, "MIRROR: Invalid source operand\n");
        return;
    }

    uint64_t src_value = 0;

    // Determine the source operand value (memory or register)
    if (inst->src_is_memory) {
        src_value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
        printf("MIRROR: Reading source value 0x%llX from memory address 0x%llX\n",
            (uint64_t)src_value, inst->src_mem_address);
    }
    else if (inst->src_reg) {
        src_value = *inst->src_reg;
        printf("MIRROR: Using source value 0x%llX from source register\n",
            (uint64_t)src_value);
    }

    uint64_t mirrored_value = mirror_decimal(src_value);

    // Store the result
    if (inst->dest_reg) {
        *inst->dest_reg = mirrored_value;
        printf("MIRROR: Writing result 0x%llX to destination register\n", (uint64_t)mirrored_value);
    }
    else if (inst->dest_is_memory) {
        write_memory(emu, inst->dest_mem_address, mirrored_value, sizeof(uint64_t));
        printf("MIRROR: Writing result 0x%llX to memory address 0x%llX\n",
            (uint64_t)mirrored_value, inst->dest_mem_address);
    }
    else {
        fprintf(stderr, "MIRROR: Invalid destination operand\n");
        return;
    }

    printf("Executed MIRROR Instruction: Mirror of %" PRIu64 " = %" PRIu64 "\n", src_value, mirrored_value);

    // Ensure the result fits in the destination register size
    if (inst->dest_reg) {
        const char* dest_name = get_register_name(emu, inst->dest_reg);
        size_t size = get_register_size(dest_name);

        // Ensure the result fits in the register size
        if (size == 32 && mirrored_value > 0xFFFFFFFF) {
            fprintf(stderr, "Error: Mirrored value 0x%016" PRIx64 " exceeds 32-bit register size for %s\n",
                mirrored_value, dest_name);
        }
    }
}

// Execute MIN with three parameters
void execute_min_instruction(Emulator* emu, Instruction* inst) {
    uint64_t val1 = 0, val2 = 0, val3 = 0;

    // Get first value (always from destination register)
    if (!inst->dest_reg) {
        fprintf(stderr, "MIN: First operand must be a register\n");
        return;
    }
    val1 = *inst->dest_reg;
    printf("MIN: First value from register: 0x%llX\n", (unsigned long long)val1);

    // Get second value (from register, memory, or immediate)
    if (inst->src_reg) {
        val2 = *inst->src_reg;
        printf("MIN: Second value from register: 0x%llX\n", (unsigned long long)val2);
    }
    else if (inst->src_is_memory) {
        val2 = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
        printf("MIN: Second value from memory: 0x%llX\n", (unsigned long long)val2);
    }
    else if (inst->src_immediate) {
        val2 = inst->immediate;
        printf("MIN: Second value from immediate: 0x%llX\n", (unsigned long long)val2);
    }
    else {
        fprintf(stderr, "MIN: Invalid second operand\n");
        return;
    }

    // Get third value (from register, memory, or immediate)
    if (inst->aux_reg) {
        val3 = *inst->aux_reg;
        printf("MIN: Third value from register: 0x%llX\n", (unsigned long long)val3);
    }
    else if (inst->aux_is_memory) {
        val3 = read_memory(emu, inst->aux_mem_address, sizeof(uint64_t));
        printf("MIN: Third value from memory: 0x%llX\n", (unsigned long long)val3);
    }
    else if (inst->aux_immediate) {
        val3 = inst->aux_immediate;
        printf("MIN: Third value from immediate: 0x%llX\n", (unsigned long long)val3);
    }
    else {
        fprintf(stderr, "MIN: Invalid third operand\n");
        return;
    }

    // Find minimum value
    uint64_t min_val = val1;
    if (val2 < min_val) min_val = val2;
    if (val3 < min_val) min_val = val3;

    // Store result in destination register
    *inst->dest_reg = min_val;
    printf("MIN: Result 0x%llX stored in destination register\n", (unsigned long long)min_val);

    // Update flags
    emu->flags.zero = (min_val == 0);
    emu->flags.sign = (min_val & (1ULL << 63)) ? 1 : 0;
}

void execute_max_instruction(Emulator* emu, Instruction* inst) {
    uint64_t val1 = 0, val2 = 0, val3 = 0;

    // Get first value (always from destination register)
    if (!inst->dest_reg) {
        fprintf(stderr, "MAX: First operand must be a register\n");
        return;
    }
    val1 = *inst->dest_reg;
    printf("MAX: First value from register: 0x%llX\n", (unsigned long long)val1);

    // Get second value (from register, memory, or immediate)
    if (inst->src_reg) {
        val2 = *inst->src_reg;
        printf("MAX: Second value from register: 0x%llX\n", (unsigned long long)val2);
    }
    else if (inst->src_is_memory) {
        val2 = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
        printf("MAX: Second value from memory: 0x%llX\n", (unsigned long long)val2);
    }
    else if (inst->src_immediate) {
        val2 = inst->immediate;
        printf("MAX: Second value from immediate: 0x%llX\n", (unsigned long long)val2);
    }
    else {
        fprintf(stderr, "MAX: Invalid second operand\n");
        return;
    }

    // Get third value (from register, memory, or immediate)
    if (inst->aux_reg) {
        val3 = *inst->aux_reg;
        printf("MAX: Third value from register: 0x%llX\n", (unsigned long long)val3);
    }
    else if (inst->aux_is_memory) {
        val3 = read_memory(emu, inst->aux_mem_address, sizeof(uint64_t));
        printf("MAX: Third value from memory: 0x%llX\n", (unsigned long long)val3);
    }
    else if (inst->aux_immediate) {
        val3 = inst->aux_immediate;
        printf("MAX: Third value from immediate: 0x%llX\n", (unsigned long long)val3);
    }
    else {
        fprintf(stderr, "MAX: Invalid third operand\n");
        return;
    }

    // Find maximum value
    uint64_t max_val = val1;
    if (val2 > max_val) max_val = val2;
    if (val3 > max_val) max_val = val3;

    // Store result in destination register
    *inst->dest_reg = max_val;
    printf("MAX: Result 0x%llX stored in destination register\n", (unsigned long long)max_val);

    // Update flags
    emu->flags.zero = (max_val == 0);
    emu->flags.sign = (max_val & (1ULL << 63)) ? 1 : 0;
}

// Function to print a register in specified format
void print_reg(const char* name, uint64_t value, NumberFormat format, size_t size) {
    if (format == HEX) {
        switch (size) {
        case 32:
            printf("%-6s: 0x%08" PRIx64 "    ", name, value);
            break;
        case 64:
            printf("%-6s: 0x%016" PRIx64 "    ", name, value);
            break;
        default:
            printf("%-6s: 0x%016" PRIx64 "    ", name, value);
            break;
        }
    }
    else {
        switch (size) {
        case 32:
            printf("%-6s: %" PRIu32 "    ", name, (uint32_t)value);
            break;
        case 64:
            printf("%-6s: %" PRIu64 "    ", name, value);
            break;
        default:
            printf("%-6s: %" PRIu64 "    ", name, value);
            break;
        }
    }
}

// Print current emulator state
void print_emulator_state(Emulator* emu, const char* phase) {
    // Allow printing if tracing is enabled or if it's the final state
    if (!tracing_enabled && strcmp(phase, "Final State") != 0) return;

    printf("\n--- Emulator State: %s ---\n", phase);
    printf("Registers:\n");

    NumberFormat format = HEX; // Set format to HEX for all registers

    // Print primary registers
    print_reg("RAX", emu->rax, format, 64);
    print_reg("EAX", emu->eax, format, 32);
    printf("\n");

    print_reg("RBX", emu->rbx, format, 64);
    print_reg("EBX", emu->ebx, format, 32);
    printf("\n");

    print_reg("RCX", emu->rcx, format, 64);
    print_reg("ECX", emu->ecx, format, 32);
    printf("\n");

    print_reg("RDX", emu->rdx, format, 64);
    print_reg("EDX", emu->edx, format, 32);
    printf("\n");

    print_reg("RSI", emu->rsi, format, 64);
    print_reg("ESI", emu->esi, format, 32);
    printf("\n");

    print_reg("RDI", emu->rdi, format, 64);
    print_reg("EDI", emu->edi, format, 32);
    printf("\n");

    print_reg("RSP", emu->rsp, format, 64);
    print_reg("ESP", emu->esp, format, 32);
    printf("\n");

    print_reg("RBP", emu->rbp, format, 64);
    print_reg("EBP", emu->ebp, format, 32);
    printf("\n");

    print_reg("R8", emu->r8, format, 64);
    print_reg("R8D", emu->r8d, format, 32);
    printf("\n");

    print_reg("R9", emu->r9, format, 64);
    print_reg("R9D", emu->r9d, format, 32);
    printf("\n");

    print_reg("R10", emu->r10, format, 64);
    print_reg("R10D", emu->r10d, format, 32);
    printf("\n");

    print_reg("R11", emu->r11, format, 64);
    print_reg("R11D", emu->r11d, format, 32);
    printf("\n");

    print_reg("R12", emu->r12, format, 64);
    print_reg("R12D", emu->r12d, format, 32);
    printf("\n");

    print_reg("R13", emu->r13, format, 64);
    print_reg("R13D", emu->r13d, format, 32);
    printf("\n");

    print_reg("R14", emu->r14, format, 64);
    print_reg("R14D", emu->r14d, format, 32);
    printf("\n");

    print_reg("R15", emu->r15, format, 64);
    print_reg("R15D", emu->r15d, format, 32);
    printf("\n");

    printf("\nFlags:\n");
    printf("Carry: %d\tZero: %d\tSign: %d\tOverflow: %d\tDirection: %d\tInterrupt: %d\tTrap: %d\tAlignment: %d\n",
        emu->flags.carry, emu->flags.zero, emu->flags.sign, emu->flags.overflow,
        emu->flags.direction, emu->flags.interrupt, emu->flags.trap, emu->flags.alignment);

    printf("\nSegment Registers:\n");
    printf("CS: 0x%04X\tDS: 0x%04X\tSS: 0x%04X\tES: 0x%04X\tFS: 0x%04X\tGS: 0x%04X\n",
        emu->cs, emu->ds, emu->ss, emu->es, emu->fs, emu->gs);

    printf("\nInstruction Pointer (RIP): 0x%016" PRIx64 "\n", emu->rip);
    printf("----------------------------------------\n");
}

void push_to_stack(Emulator* emu, uint64_t value) {
    if (emu->rsp < 8) {
        fprintf(stderr, "Stack overflow!\n");
        exit(EXIT_FAILURE);
    }
    emu->rsp -= 8;  // Adjust stack pointer
    write_memory(emu, emu->rsp, value, sizeof(uint64_t));
}

uint64_t pop_from_stack(Emulator* emu) {
    if (emu->rsp >= emu->memory_size) {
        fprintf(stderr, "Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    uint64_t value = read_memory(emu, emu->rsp, sizeof(uint64_t));
    emu->rsp += 8;  // Adjust stack pointer
    return value;
}

// Comprehensive instruction execution
void execute_instruction(Emulator* emu, Instruction* inst, size_t inst_num, Label* labels, size_t label_count) {  // Comprehensive instruction execution
    if (tracing_enabled) {
        // Print the current instruction being executed with actual register names
        printf("\n=== Executing Instruction %zu ===\n", inst_num + 1);
        printf("Instruction: ");

        // Get instruction name
        switch (inst->type) {
            case INST_INT:
                if (inst->function) {
                    printf("INT 0x%02" PRIx64 ", 0x%02" PRIx64, inst->immediate, inst->function);
                }
                else {
                    printf("INT 0x%02" PRIx64, inst->immediate);
                }
            break;
            case INST_MOV:
                if (inst->dest_is_memory) {
                    if (inst->src_is_memory) {
                        printf("MOV [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                    } else if (inst->src_reg) {
                        printf("MOV [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                    } else if (inst->src_is_string) {
                        printf("MOV [0x%llX], \"%s\"", inst->dest_mem_address, inst->src_string);
                    } else {
                        printf("MOV [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                    }
                } else if (inst->dest_reg) {
                    if (inst->src_is_memory) {
                        printf("MOV %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                    } else if (inst->src_reg) {
                        printf("MOV %s, %s",inst->dest_reg_name, inst->src_reg_name);
                    } else {
                        printf("MOV %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                    }
                } else {
                    printf("MOV UNKNOWN");
                }
            break;
        case INST_PUSH:
            printf("PUSH %s", inst->dest_reg_name);
            break;
        case INST_POP:
            printf("POP %s", inst->dest_reg_name);
            break;
        case INST_XCHG:
            printf("XCHG %s, %s", inst->dest_reg_name, inst->src_reg_name);
            break;
        case INST_ADD:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("ADD [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("ADD [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("ADD [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("ADD %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("ADD %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("ADD %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("ADD UNKNOWN");
            }
            break;
        case INST_SUB:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("SUB [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("SUB [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("SUB [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("SUB %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("SUB %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("SUB %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("SUB UNKNOWN");
            }
            break;
        case INST_MUL:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("MUL [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("MUL [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("MUL [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("MUL %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("MUL %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("MUL %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("MUL UNKNOWN");
            }
            break;
        case INST_DIV:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("DIV [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("DIV [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("DIV [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("DIV %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("DIV %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("DIV %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("DIV UNKNOWN");
            }
            break;
        case INST_INC:
            printf("INC %s", inst->dest_reg_name);
            break;
        case INST_DEC:
            printf("DEC %s", inst->dest_reg_name);
            break;
        case INST_NEG:
            printf("NEG %s", inst->dest_reg_name);
            break;
        case INST_CMP:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("CMP [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("CMP [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("CMP [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("CMP %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("CMP %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("CMP %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("CMP UNKNOWN");
            }
            break;
        case INST_AND:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("AND [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("AND [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("AND [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("AND %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("AND %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("AND %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("AND UNKNOWN");
            }
            break;
        case INST_OR:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("OR [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("OR [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("OR [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("OR %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("OR %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("OR %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("OR UNKNOWN");
            }
            break;
        case INST_XOR:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("XOR [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("XOR [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("XOR [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("XOR %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("XOR %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("XOR %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("XOR UNKNOWN");
            }
            break;
        case INST_NOT:
            printf("NOT %s", inst->dest_reg_name);
            break;
        case INST_SHL:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("SHL [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("SHL [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("SHL [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("SHL %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("SHL %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("SHL %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("SHL UNKNOWN");
            }
            break;
        case INST_SHR:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("SHR [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("SHR [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("SHR [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("SHR %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("SHR %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("SHR %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("SHR UNKNOWN");
            }
            break;
        case INST_ROL:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("ROL [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("ROL [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("ROL [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("ROL %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("ROL %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("ROL %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("ROL UNKNOWN");
            }
            break;
        case INST_ROR:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("ROR [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("ROR [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("ROR [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("ROR %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("ROR %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("ROR %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("ROR UNKNOWN");
            }
            break;
        case INST_JMP:
            printf("JMP %s", inst->label);
            break;
        case INST_JE:
            printf("JE %s", inst->label);
            break;
        case INST_JNE:
            printf("JNE %s", inst->label);
            break;
        case INST_JG:
            printf("JG %s", inst->label);
            break;
        case INST_JGE:
            printf("JGE %s", inst->label);
            break;
        case INST_JL:
            printf("JL %s", inst->label);
            break;
        case INST_JLE:
            printf("JLE %s", inst->label);
            break;
        case INST_JA:
            printf("JA %s", inst->label);
            break;
        case INST_JAE:
            printf("JAE %s", inst->label);
            break;
        case INST_JB:
            printf("JB %s", inst->label);
            break;
        case INST_JBE:
            printf("JBE %s", inst->label);
            break;
        case INST_JO:
            printf("JO %s", inst->label);
            break;
        case INST_JNO:
            printf("JNO %s", inst->label);
            break;
        case INST_JS:
            printf("JS %s", inst->label);
            break;
        case INST_JNS:
            printf("JNS %s", inst->label);
            break;
        case INST_JP:
            printf("JP %s", inst->label);
            break;
        case INST_JNP:
            printf("JNP %s", inst->label);
            break;
        case INST_POW:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("POW [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("POW [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("POW [0x%llX], 0x%016" PRIx64 , inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("POW %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("POW %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("POW %s, 0x%016" PRIx64 , inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("MOV UNKNOWN");
            }
            break;
        case INST_ROOT:
    if (inst->dest_is_memory) {
        if (inst->src_is_memory) {
            printf("ROOT [0x%llX], [0x%llX], ",
                inst->dest_mem_address,
                inst->src_mem_address);
        } else if (inst->src_reg) {
            printf("ROOT [0x%llX], %s, ",
                inst->dest_mem_address,
                inst->src_reg_name);
        } else {
            printf("ROOT [0x%llX], 0x%016" PRIx64 ", ",
                inst->dest_mem_address,
                inst->immediate);
        }
    } else if (inst->dest_reg) {
        if (inst->src_is_memory) {
            printf("ROOT %s, [0x%llX], ",
                inst->dest_reg_name,
                inst->src_mem_address);
        } else if (inst->src_reg) {
            printf("ROOT %s, %s, ",
                inst->dest_reg_name,
                inst->src_reg_name);
        } else {
            printf("ROOT %s, 0x%016" PRIx64 ", ",
                inst->dest_reg_name,
                inst->immediate);
        }
    } else {
        printf("ROOT UNKNOWN, ");
    }

    // Handle the third parameter (exponent)
    if (inst->aux_is_memory) {
        printf("[0x%llX]", inst->aux_mem_address);
    } else if (inst->aux_reg) {
        printf("%s", inst->aux_reg_name);
    } else {
        printf("0x%016" PRIx64, inst->aux_immediate);
    }

    printf("\n");
    break;

        case INST_AVG:
    if (inst->dest_is_memory) {
        if (inst->src_is_memory) {
            printf("AVG [0x%llX], [0x%llX], ",
                inst->dest_mem_address,
                inst->src_mem_address);
        } else if (inst->src_reg) {
            printf("AVG [0x%llX], %s, ",
                inst->dest_mem_address,
                inst->src_reg_name);
        } else {
            printf("AVG [0x%llX], 0x%016" PRIx64 ", ",
                inst->dest_mem_address,
                inst->immediate);
        }
    } else if (inst->dest_reg) {
        if (inst->src_is_memory) {
            printf("AVG %s, [0x%llX], ",
                inst->dest_reg_name,
                inst->src_mem_address);
        } else if (inst->src_reg) {
            printf("AVG %s, %s, ",
                inst->dest_reg_name,
                inst->src_reg_name);
        } else {
            printf("AVG %s, 0x%016" PRIx64 ", ",
                inst->dest_reg_name,
                inst->immediate);
        }
    } else {
        printf("AVG UNKNOWN, ");
    }

    // Handle the third parameter (auxiliary value)
    if (inst->aux_is_memory) {
        printf("[0x%llX]", inst->aux_mem_address);
    } else if (inst->aux_reg) {
        printf("%s", inst->aux_reg_name);
    } else {
        printf("0x%016" PRIx64, inst->aux_immediate);
    }

    printf("\n");
    break;
        case INST_MAX:
    if (inst->dest_is_memory) {
        if (inst->src_is_memory) {
            printf("MAX [0x%llX], [0x%llX], ",
                inst->dest_mem_address,
                inst->src_mem_address);
        } else if (inst->src_reg) {
            printf("MAX [0x%llX], %s, ",
                inst->dest_mem_address,
                inst->src_reg_name);
        } else {
            printf("MAX [0x%llX], 0x%016" PRIx64 ", ",
                inst->dest_mem_address,
                inst->immediate);
        }
    } else if (inst->dest_reg) {
        if (inst->src_is_memory) {
            printf("MAX %s, [0x%llX], ",
                inst->dest_reg_name,
                inst->src_mem_address);
        } else if (inst->src_reg) {
            printf("MAX %s, %s, ",
                inst->dest_reg_name,
                inst->src_reg_name);
        } else {
            printf("MAX %s, 0x%016" PRIx64 ", ",
                inst->dest_reg_name,
                inst->immediate);
        }
    } else {
        printf("MAX UNKNOWN, ");
    }

    // Handle the third parameter (auxiliary value)
    if (inst->aux_is_memory) {
        printf("[0x%llX]", inst->aux_mem_address);
    } else if (inst->aux_reg) {
        printf("%s", inst->aux_reg_name);
    } else {
        printf("0x%016" PRIx64, inst->aux_immediate);
    }

    printf("\n");
    break;
        case INST_MIN:
    if (inst->dest_is_memory) {
        if (inst->src_is_memory) {
            printf("MIN [0x%llX], [0x%llX], ",
                inst->dest_mem_address,
                inst->src_mem_address);
        } else if (inst->src_reg) {
            printf("MIN [0x%llX], %s, ",
                inst->dest_mem_address,
                inst->src_reg_name);
        } else {
            printf("MIN [0x%llX], 0x%016" PRIx64 ", ",
                inst->dest_mem_address,
                inst->immediate);
        }
    } else if (inst->dest_reg) {
        if (inst->src_is_memory) {
            printf("MIN %s, [0x%llX], ",
                inst->dest_reg_name,
                inst->src_mem_address);
        } else if (inst->src_reg) {
            printf("MIN %s, %s, ",
                inst->dest_reg_name,
                inst->src_reg_name);
        } else {
            printf("MIN %s, 0x%016" PRIx64 ", ",
                inst->dest_reg_name,
                inst->immediate);
        }
    } else {
        printf("MIN UNKNOWN, ");
    }

    // Handle the third parameter (auxiliary value)
    if (inst->aux_is_memory) {
        printf("[0x%llX]", inst->aux_mem_address);
    } else if (inst->aux_reg) {
        printf("%s", inst->aux_reg_name);
    } else {
        printf("0x%016" PRIx64, inst->aux_immediate);
    }

    printf("\n");
    break;
        case INST_MOD:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("MOD [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("MOD [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("MOD [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("MOD %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("MOD %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("MOD %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("MOD UNKNOWN");
            }
            break;
        case INST_MIRROR:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("MIRROR [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("MIRROR [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("MIRROR [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("MIRROR %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("MIRROR %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("MIRROR %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("MIRROR UNKNOWN");
            }
            break;
        case INST_ISPRIME:
            if (inst->dest_is_memory) {
                if (inst->src_is_memory) {
                    printf("ISPRIME [0x%llX], [0x%llX]", inst->dest_mem_address, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("ISPRIME [0x%llX], %s", inst->dest_mem_address, inst->src_reg_name);
                } else {
                    printf("ISPRIME [0x%llX], 0x%016" PRIx64, inst->dest_mem_address, inst->immediate);
                }
            } else if (inst->dest_reg) {
                if (inst->src_is_memory) {
                    printf("ISPRIME %s, [0x%llX]", inst->dest_reg_name, inst->src_mem_address);
                } else if (inst->src_reg) {
                    printf("ISPRIME %s, %s",inst->dest_reg_name, inst->src_reg_name);
                } else {
                    printf("ISPRIME %s, 0x%016" PRIx64, inst->dest_reg_name, inst->immediate);
                }
            } else {
                printf("ISPRIME UNKNOWN");
            }
            break;
        case INST_LABEL:
            printf("LABEL %s", inst->label);
            break;
        case INST_COMMENT:
            // Comments are ignored in execution
            break;
        case INST_NOP:
            printf("NOP");
            break;
        default:
            printf("UNKNOWN");
            break;
        }
        printf("\n");

        // Print registers before execution
        print_emulator_state(emu, "Before Execution");
    }

    // Execute the instruction based on its type
    switch (inst->type) {
        // Data Movement Instructions
        case INST_INT:
            if (inst->immediate < 256 && interrupt_handlers[inst->immediate]) {
                // Store the function number in the immediate field before calling handler
                uint64_t original_immediate = inst->immediate;
                inst->immediate = inst->function;  // Set the function number (09 in your case)
                interrupt_handlers[original_immediate](emu, inst);
                inst->immediate = original_immediate;  // Restore original immediate if needed
            } else {
                fprintf(stderr, "Error: Unsupported interrupt number 0x%I64X\n", inst->immediate);
            }
        break;
case INST_MOV:
    if (inst->dest_is_memory) {
        // Writing to memory
        uint64_t value = 0;
        if (inst->src_is_string) {
            // Source is a string literal
            const char* string = inst->src_string;
            uint64_t address = inst->dest_mem_address;
            size_t str_len = strlen(string);

            // Write string to memory
            for (size_t i = 0; i < str_len; ++i) {
                write_memory(emu, address + i, string[i], sizeof(uint8_t));
            }

            // Null-terminate the string in memory
            write_memory(emu, address + str_len, '\0', sizeof(uint8_t));

            printf("MOV: Wrote string \"%s\" to memory address 0x%llX\n", string, address);
        }
        else if (inst->src_is_memory) {
            // Source is memory
            uint64_t value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
            write_memory(emu, inst->dest_mem_address, value, sizeof(uint64_t));

            printf("MOV: Copied value 0x%016" PRIx64 " from memory address 0x%llX to 0x%llX\n",
                   value, inst->src_mem_address, inst->dest_mem_address);
        }
        else if (inst->src_reg) {
            // Source is a register
            uint64_t value = *inst->src_reg;
            printf("MOV: Copied value 0x%016" PRIx64 " from source register %s to memory address 0x%016" PRIx64 "\n", value, inst->src_reg_name, inst->dest_mem_address);
        }
        else {
            // Source is an immediate value
            uint64_t value = inst->immediate;
            write_memory(emu, inst->dest_mem_address, value, sizeof(uint64_t));

            printf("MOV: Wrote immediate value 0x%016" PRIx64 " to memory address 0x%llX\n",
                   value, inst->dest_mem_address);
        }
    }
    else if (inst->dest_reg) {
        // Writing to a register
        uint64_t value = 0;

        if (inst->src_is_memory) {
            // Source is memory
            value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));

            printf("MOV: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64
                   " into destination register %s\n",
                   value, inst->src_mem_address, inst->dest_reg_name);
        }
        else if (inst->src_reg) {
            // Source is another register
            uint64_t value = *inst->src_reg;
            printf("MOV: Moving value 0x%016" PRIx64 " from source register %s to destination register %s\n",
                   value, inst->src_reg_name, inst->dest_reg_name);
        }
        else if (inst->src_is_string) {
            // Convert first character of string to its ASCII value
            value = (uint64_t)inst->src_string[0];

            printf("MOV: Moving first character '%c' (ASCII 0x%016" PRIx64 ") from string to register %s\n",
                   inst->src_string[0], value, inst->dest_reg_name);
        }
        else {
            // Source is an immediate value
            value = inst->immediate;

            printf("MOV: Moving immediate value 0x%016" PRIx64 " to destination register %s\n",
                   value, inst->dest_reg_name);
        }

        // Move the value to the destination register
        *inst->dest_reg = value;
    }
    else {
        // Invalid instruction format
        fprintf(stderr, "MOV: Invalid instruction format\n");
        // Consider adding more detailed error logging
        exit(EXIT_FAILURE);
    }
    break;

    case INST_PUSH:
    {
        // Determine the value to push onto the stack
        uint64_t value = 0;

        if (inst->dest_is_memory) {
            // Push the value from memory to the stack
            value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("PUSH: Pushing value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 " onto the stack\n", value, inst->dest_mem_address);
        }
        else if (inst->dest_reg) {
            // Push the value from a register to the stack
            value = *inst->dest_reg;
            printf("PUSH: Pushing value 0x%016" PRIx64 " from register %s onto the stack\n", value, inst->dest_reg_name);
        }
        else {
            fprintf(stderr, "PUSH: Invalid operand (must be a register or memory)\n");
            exit(EXIT_FAILURE);
        }

        // Check for stack overflow
        if (emu->rsp < (uint64_t)(uintptr_t)(emu->stack)) {
            fprintf(stderr, "Stack overflow\n");
            exit(1);
        }

        // Decrement the stack pointer
        emu->rsp -= sizeof(uint64_t);

        // Calculate the stack offset
        size_t stack_offset = emu->rsp - (uint64_t)(uintptr_t)(emu->stack);

        // Ensure stack_offset is within stack_size
        if (stack_offset + sizeof(uint64_t) > emu->stack_size) {
            fprintf(stderr, "Stack overflow (invalid stack offset)\n");
            exit(1);
        }

        // Push the value onto the stack
        memcpy(emu->stack + stack_offset, &value, sizeof(uint64_t));

        printf("Executed PUSH Instruction: Pushed 0x%016" PRIx64 " to stack\n", value);
    }
    break;

    case INST_POP:
    {
        // Check for stack underflow
        if (emu->rsp >= (uint64_t)(uintptr_t)(emu->stack) + emu->stack_size) {
            fprintf(stderr, "Stack underflow\n");
            exit(1);
        }

        // Calculate the stack offset
        size_t stack_offset = emu->rsp - (uint64_t)(uintptr_t)(emu->stack);

        // Ensure stack_offset is within stack_size
        if (stack_offset + sizeof(uint64_t) > emu->stack_size) {
            fprintf(stderr, "Stack underflow (invalid stack offset)\n");
            exit(1);
        }

        // Pop the value from the stack
        uint64_t value;
        memcpy(&value, emu->stack + stack_offset, sizeof(uint64_t));
        emu->rsp += sizeof(uint64_t);

        // Determine where to store the popped value
        if (inst->dest_is_memory) {
            // Pop a value from the stack into memory
            printf("POP: Popping value 0x%016" PRIx64 " from the stack into memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);
            write_memory(emu, inst->dest_mem_address, value, sizeof(uint64_t));
        }
        else if (inst->dest_reg) {
            // Pop a value from the stack into a register
            printf("POP: Popping value 0x%016" PRIx64 " from the stack into register %s\n", value, inst->dest_reg_name);
            *inst->dest_reg = value;

            // Determine register size
            const char* reg_name = inst->dest_reg_name;
            size_t size = get_register_size(reg_name);

            // Check if the popped value fits in the register size
            if (size == 32 && value > 0xFFFFFFFF) {
                fprintf(stderr, "Error: Popped value 0x%016" PRIx64 " exceeds 32-bit register size for %s\n", value, inst->dest_reg_name);
            }
            // 64-bit can hold all values
        }
        else {
            fprintf(stderr, "POP: Invalid operand (must be a register or memory)\n");
            exit(EXIT_FAILURE);
        }

        printf("Executed POP Instruction: Popped 0x%016" PRIx64 " from stack\n", value);
    }
    break;

    case INST_XCHG:
    {
        // Check for invalid memory-to-memory exchange
        if (inst->dest_is_memory && inst->src_is_memory) {
            fprintf(stderr, "XCHG: Invalid instruction format (memory-to-memory exchange is not supported)\n");
            exit(EXIT_FAILURE);
        }

        uint64_t temp_value = 0;

        // If the destination is memory
        if (inst->dest_is_memory) {
            // Read the current value from the destination memory
            uint64_t mem_value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("XCHG: Reading value 0x%016" PRIx64 " from destination memory address 0x%016" PRIx64 "\n", mem_value, inst->dest_mem_address);

            // Determine the source value
            if (inst->src_is_memory) {
                // Source is memory, read value from memory
                temp_value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
                printf("XCHG: Reading value 0x%016" PRIx64 " from source memory address 0x%016" PRIx64 "\n", temp_value, inst->src_mem_address);
            }
            else if (inst->src_reg) {
                // Source is a register, swap with memory
                temp_value = *inst->src_reg;
                printf("XCHG: Reading value 0x%016" PRIx64 " from source register %s and swapping with memory address 0x%016" PRIx64 "\n", temp_value, inst->src_reg_name, inst->dest_mem_address);
            }
            else {
                // Source is an immediate value
                temp_value = inst->immediate;
                printf("XCHG: Swapping immediate value 0x%016" PRIx64 " with memory address 0x%016" PRIx64 "\n", temp_value, inst->dest_mem_address);
            }

            // Write the source value (temp_value) to the destination memory
            write_memory(emu, inst->dest_mem_address, temp_value, sizeof(uint64_t));

            // Write the original memory value to the source memory (or register)
            if (inst->src_is_memory) {
                write_memory(emu, inst->src_mem_address, mem_value, sizeof(uint64_t));
            }
            else if (inst->src_reg) {
                *inst->src_reg = mem_value;
            }
            else {
                // Immediate case, should not happen for memory-based XCHG
                fprintf(stderr, "XCHG: Invalid operand handling\n");
                exit(EXIT_FAILURE);
            }
        }
        // If the destination is a register
        else if (inst->dest_reg) {
            // Determine the source value
            if (inst->src_is_memory) {
                // Source is memory
                temp_value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
                printf("XCHG: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 " into destination register %s\n", temp_value, inst->src_mem_address, inst->dest_reg_name);
            }
            else if (inst->src_reg) {
                // Source is another register
                temp_value = *inst->src_reg;
                printf("XCHG: Reading value 0x%016" PRIx64 " from source register %s and swapping with destination register %s\n", temp_value, inst->src_reg_name, inst->dest_reg_name);
            }
            else {
                // Source is an immediate value
                temp_value = inst->immediate;
                printf("XCHG: Swapping immediate value 0x%016" PRIx64 " with destination register %s\n", temp_value, inst->dest_reg_name);
            }

            // Swap the values between source and destination
            uint64_t temp = *inst->dest_reg;
            *inst->dest_reg = temp_value;

            if (inst->src_is_memory) {
                write_memory(emu, inst->src_mem_address, temp, sizeof(uint64_t));
            }
            else if (inst->src_reg) {
                *inst->src_reg = temp;
            }

            printf("XCHG: Swapped value 0x%016" PRIx64 " with destination register %s\n", temp, inst->dest_reg_name);
        }
        else {
            // Invalid instruction format
            fprintf(stderr, "XCHG: Invalid instruction format\n");
            exit(EXIT_FAILURE);
        }
    }
    break;

        // Arithmetic Instructions
    case INST_ADD:
    {
        // Determine register size
        const char* dest_name = inst->dest_reg_name;
        size_t size = get_register_size(dest_name);
        uint64_t original_value = 0;
        uint64_t result = 0;

        if (inst->dest_is_memory) {
            // Destination is memory
            uint64_t mem_value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("ADD: Reading value 0x%016" PRIx64 " from destination memory address 0x%016" PRIx64 "\n", mem_value, inst->dest_mem_address);

            // Get the value from the source operand
            uint64_t value = 0;
            if (inst->src_is_memory) {
                value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
                printf("ADD: Reading value 0x%016" PRIx64 " from source memory address 0x%016" PRIx64 "\n", value, inst->src_mem_address);
            }
            else if (inst->src_reg) {
                value = *inst->src_reg;
                printf("ADD: Adding value 0x%016" PRIx64 " from source register %s to memory address 0x%016" PRIx64 "\n", value, inst->src_reg_name, inst->dest_mem_address);
            }
            else {
                value = inst->immediate;
                printf("ADD: Adding immediate value 0x%016" PRIx64 " to memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);
            }

            // Perform the addition
            result = mem_value + value;
            printf("ADD: Writing result 0x%016" PRIx64 " to destination memory address 0x%016" PRIx64 "\n", result, inst->dest_mem_address);

            // Write the result to memory
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));

            // Set flags
            emu->flags.zero = (result == 0) ? 1 : 0;  // Zero Flag (ZF)
            emu->flags.sign = (result & (1ULL << 63)) ? 1 : 0;  // Sign Flag (SF)
            emu->flags.carry = (result < mem_value) ? 1 : 0;  // Carry Flag (CF)
            emu->flags.overflow = ((mem_value ^ result) & (value ^ result) & (1ULL << 63)) ? 1 : 0;  // Overflow Flag (OF)
        }
        else if (inst->dest_reg) {
            // Destination is a register
            original_value = *inst->dest_reg;

            // Get the value from the source operand
            uint64_t value = 0;
            if (inst->src_is_memory) {
                value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
                printf("ADD: Reading value 0x%016" PRIx64 " from source memory address 0x%016" PRIx64 "\n", value, inst->src_mem_address);
            }
            else if (inst->src_reg) {
                value = *inst->src_reg;
                printf("ADD: Adding value 0x%016" PRIx64 " from source register %s to destination register %s\n", value, inst->src_reg_name, inst->dest_reg_name);
            }
            else {
                value = inst->immediate;
                printf("ADD: Adding immediate value 0x%016" PRIx64 " to destination register %s\n", value, inst->dest_reg_name);
            }

            // Perform the addition
            result = original_value + value;
            printf("ADD: Writing result 0x%016" PRIx64 " to destination register %s\n", result, inst->dest_reg_name);

            // Write the result to the destination register
            *inst->dest_reg = result;

            // Check for overflow
            if (size == 32 && result > 0xFFFFFFFF) {
                fprintf(stderr, "Error: Addition result 0x%016" PRIx64 " exceeds 32-bit register size for %s\n", result, dest_name);
                return;
            }
            // 64-bit can hold all results

            // Set flags
            emu->flags.zero = (result == 0) ? 1 : 0;  // Zero Flag (ZF)
            emu->flags.sign = (result & (1ULL << (size * 8 - 1))) ? 1 : 0;  // Sign Flag (SF)
            emu->flags.carry = (result < original_value) ? 1 : 0;  // Carry Flag (CF)
            emu->flags.overflow = ((original_value ^ result) & (value ^ result) & (1ULL << (size * 8 - 1))) ? 1 : 0;  // Overflow Flag (OF)
        }
        else {
            fprintf(stderr, "ADD: Invalid instruction format\n");
            exit(EXIT_FAILURE);
        }

        printf("Executed ADD Instruction: %s = 0x%016" PRIx64 "\n", inst->dest_reg_name, result);
    }
    break;

    case INST_SUB:
    {
        // Determine register size
        const char* dest_name = inst->dest_reg_name;
        size_t size = get_register_size(dest_name);
        uint64_t original_value = 0;
        uint64_t result = 0;

        if (inst->dest_is_memory) {
            // Destination is memory
            uint64_t mem_value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("SUB: Reading value 0x%016" PRIx64 " from destination memory address 0x%016" PRIx64 "\n", mem_value, inst->dest_mem_address);

            // Get the value from the source operand
            uint64_t value = 0;
            if (inst->src_is_memory) {
                value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
                printf("SUB: Reading value 0x%016" PRIx64 " from source memory address 0x%016" PRIx64 "\n", value, inst->src_mem_address);
            }
            else if (inst->src_reg) {
                value = *inst->src_reg;
                printf("SUB: Subtracting value 0x%016" PRIx64 " from source register %s from memory address 0x%016" PRIx64 "\n", value, inst->src_reg_name, inst->dest_mem_address);
            }
            else {
                value = inst->immediate;
                printf("SUB: Subtracting immediate value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);
            }

            // Perform the subtraction
            result = mem_value - value;
            printf("SUB: Writing result 0x%016" PRIx64 " to destination memory address 0x%016" PRIx64 "\n", result, inst->dest_mem_address);

            // Write the result to memory
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));

            // Set flags
            emu->flags.zero = (result == 0) ? 1 : 0;  // Zero Flag (ZF)
            emu->flags.sign = (result & (1ULL << 63)) ? 1 : 0;  // Sign Flag (SF)
            emu->flags.carry = (mem_value < value) ? 1 : 0;  // Carry Flag (CF)
            emu->flags.overflow = ((mem_value ^ value) & (mem_value ^ result) & (1ULL << 63)) ? 1 : 0;  // Overflow Flag (OF)
        }
        else if (inst->dest_reg) {
            // Destination is a register
            original_value = *inst->dest_reg;

            // Get the value from the source operand
            uint64_t value = 0;
            if (inst->src_is_memory) {
                value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
                printf("SUB: Reading value 0x%016" PRIx64 " from source memory address 0x%016" PRIx64 "\n", value, inst->src_mem_address);
            }
            else if (inst->src_reg) {
                value = *inst->src_reg;
                printf("SUB: Subtracting value 0x%016" PRIx64 " from source register %s from destination register %s\n", value, inst->src_reg_name, inst->dest_reg_name);
            }
            else {
                value = inst->immediate;
                printf("SUB: Subtracting immediate value 0x%016" PRIx64 " from destination register %s\n", value, inst->dest_reg_name);
            }

            // Perform the subtraction
            result = original_value - value;
            printf("SUB: Writing result 0x%016" PRIx64 " to destination register %s\n", result, inst->dest_reg_name);

            // Write the result to the destination register
            *inst->dest_reg = result;

            // Check for underflow
            if (size == 32 && result > 0xFFFFFFFF) {
                fprintf(stderr, "Error: Subtraction result 0x%016" PRIx64 " exceeds 32-bit register size for %s\n", result, dest_name);
                return;
            }
            // 64-bit can hold all results

            // Set flags
            emu->flags.zero = (result == 0) ? 1 : 0;  // Zero Flag (ZF)
            emu->flags.sign = (result & (1ULL << (size * 8 - 1))) ? 1 : 0;  // Sign Flag (SF)
            emu->flags.carry = (original_value < value) ? 1 : 0;  // Carry Flag (CF)
            emu->flags.overflow = ((original_value ^ value) & (original_value ^ result) & (1ULL << (size * 8 - 1))) ? 1 : 0;  // Overflow Flag (OF)
        }
        else {
            fprintf(stderr, "SUB: Invalid instruction format\n");
            exit(EXIT_FAILURE);
        }

        printf("Executed SUB Instruction: %s = 0x%016" PRIx64 "\n", inst->dest_reg_name, result);
    }
    break;

    case INST_MUL:
    {
        // Determine register size
        const char* dest_name = inst->dest_reg_name;
        size_t size = get_register_size(dest_name);
        uint64_t original_value = 0;
        uint64_t result = 0;

        if (inst->dest_is_memory) {
            // Destination is memory
            uint64_t mem_value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("MUL: Reading value 0x%016" PRIx64 " from destination memory address 0x%016" PRIx64 "\n", mem_value, inst->dest_mem_address);

            // Get the value from the source operand
            uint64_t value = 0;
            if (inst->src_is_memory) {
                value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
                printf("MUL: Reading value 0x%016" PRIx64 " from source memory address 0x%016" PRIx64 "\n", value, inst->src_mem_address);
            }
            else if (inst->src_reg) {
                value = *inst->src_reg;
                printf("MUL: Multiplying value 0x%016" PRIx64 " from source register %s with memory address 0x%016" PRIx64 "\n", value, inst->src_reg_name, inst->dest_mem_address);
            }
            else {
                value = inst->immediate;
                printf("MUL: Multiplying immediate value 0x%016" PRIx64 " with memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);
            }

            // Perform the multiplication
            result = mem_value * value;
            printf("MUL: Writing result 0x%016" PRIx64 " to destination memory address 0x%016" PRIx64 "\n", result, inst->dest_mem_address);

            // Write the result to memory
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));

            // Set flags
            emu->flags.zero = (result == 0) ? 1 : 0;  // Zero Flag (ZF)
            emu->flags.sign = (result & (1ULL << 63)) ? 1 : 0;  // Sign Flag (SF)
            emu->flags.carry = (result < mem_value || result < value) ? 1 : 0;  // Carry Flag (CF)
            emu->flags.overflow = ((mem_value ^ result) & (value ^ result) & (1ULL << 63)) ? 1 : 0;  // Overflow Flag (OF)
        }
        else if (inst->dest_reg) {
            // Destination is a register
            original_value = *inst->dest_reg;

            // Get the value from the source operand
            uint64_t value = 0;
            if (inst->src_is_memory) {
                value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
                printf("MUL: Reading value 0x%016" PRIx64 " from source memory address 0x%016" PRIx64 "\n", value, inst->src_mem_address);
            }
            else if (inst->src_reg) {
                value = *inst->src_reg;
                printf("MUL: Multiplying value 0x%016" PRIx64 " from source register %s with destination register %s\n", value, inst->src_reg_name, inst->dest_reg_name);
            }
            else {
                value = inst->immediate;
                printf("MUL: Multiplying immediate value 0x%016" PRIx64 " with destination register %s\n", value, inst->dest_reg_name);
            }

            // Perform the multiplication
            result = original_value * value;
            printf("MUL: Writing result 0x%016" PRIx64 " to destination register %s\n", result, inst->dest_reg_name);

            // Write the result to the destination register
            *inst->dest_reg = result;

            // Check for overflow
            if (size == 32 && result > 0xFFFFFFFF) {
                fprintf(stderr, "Error: Multiplication result 0x%016" PRIx64 " exceeds 32-bit register size for %s\n", result, dest_name);
                return;
            }
            // 64-bit can hold all results

            // Set flags
            emu->flags.zero = (result == 0) ? 1 : 0;  // Zero Flag (ZF)
            emu->flags.sign = (result & (1ULL << (size * 8 - 1))) ? 1 : 0;  // Sign Flag (SF)
            emu->flags.carry = (result < original_value || result < value) ? 1 : 0;  // Carry Flag (CF)
            emu->flags.overflow = ((original_value ^ result) & (value ^ result) & (1ULL << (size * 8 - 1))) ? 1 : 0;  // Overflow Flag (OF)
        }
        else {
            fprintf(stderr, "MUL: Invalid instruction format\n");
            exit(EXIT_FAILURE);
        }

        printf("Executed MUL Instruction: %s = 0x%016" PRIx64 "\n", inst->dest_reg_name, result);
    }
    break;

    case INST_DIV:
    {
        // Determine register size
        const char* dest_name = inst->dest_reg_name;
        size_t size = get_register_size(dest_name);
        uint64_t original_value = 0;
        uint64_t result = 0;

        if (inst->dest_is_memory) {
            // Destination is memory
            uint64_t mem_value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("DIV: Reading value 0x%016" PRIx64 " from destination memory address 0x%016" PRIx64 "\n", mem_value, inst->dest_mem_address);

            // Get the value from the source operand
            uint64_t value = 0;
            if (inst->src_is_memory) {
                value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
                printf("DIV: Reading value 0x%016" PRIx64 " from source memory address 0x%016" PRIx64 "\n", value, inst->src_mem_address);
            }
            else if (inst->src_reg) {
                value = *inst->src_reg;
                printf("DIV: Dividing value 0x%016" PRIx64 " from source register %s with memory address 0x%016" PRIx64 "\n", value, inst->src_reg_name, inst->dest_mem_address);
            }
            else {
                value = inst->immediate;
                printf("DIV: Dividing immediate value 0x%016" PRIx64 " with memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);
            }

            // Perform the division, ensuring no divide by zero
            if (value == 0) {
                fprintf(stderr, "DIV: Division by zero error\n");
                exit(EXIT_FAILURE);
            }

            // Perform the division
            result = mem_value / value;
            printf("DIV: Writing result 0x%016" PRIx64 " to destination memory address 0x%016" PRIx64 "\n", result, inst->dest_mem_address);

            // Write the result to memory
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));

            // Set flags
            emu->flags.zero = (result == 0) ? 1 : 0;  // Zero Flag (ZF)
            emu->flags.sign = (result & (1ULL << 63)) ? 1 : 0;  // Sign Flag (SF)
            emu->flags.carry = 0;  // Carry Flag (CF) is not applicable for division
            emu->flags.overflow = 0;  // Overflow Flag (OF) is not applicable for division
        }
        else if (inst->dest_reg) {
            // Destination is a register
            original_value = *inst->dest_reg;

            // Get the value from the source operand
            uint64_t value = 0;
            if (inst->src_is_memory) {
                value = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
                printf("DIV: Reading value 0x%016" PRIx64 " from source memory address 0x%016" PRIx64 "\n", value, inst->src_mem_address);
            }
            else if (inst->src_reg) {
                value = *inst->src_reg;
                printf("DIV: Dividing value 0x%016" PRIx64 " from source register %s with destination register %s\n", value, inst->src_reg_name, inst->dest_reg_name);
            }
            else {
                value = inst->immediate;
                printf("DIV: Dividing immediate value 0x%016" PRIx64 " with destination register %s\n", value, inst->dest_reg_name);
            }

            // Perform the division, ensuring no divide by zero
            if (value == 0) {
                fprintf(stderr, "DIV: Division by zero error\n");
                exit(EXIT_FAILURE);
            }

            // Perform the division
            result = original_value / value;
            printf("DIV: Writing result 0x%016" PRIx64 " to destination register %s\n", result, inst->dest_reg_name);

            // Write the result to the destination register
            *inst->dest_reg = result;

            // Check if result fits in the register size
            if (size == 32 && result > 0xFFFFFFFF) {
                fprintf(stderr, "Error: Division result 0x%016" PRIx64 " exceeds 32-bit register size for %s\n", result, dest_name);
            }
            // 64-bit can hold all results

            // Set flags
            emu->flags.zero = (result == 0) ? 1 : 0;  // Zero Flag (ZF)
            emu->flags.sign = (result & (1ULL << (size * 8 - 1))) ? 1 : 0;  // Sign Flag (SF)
            emu->flags.carry = 0;  // Carry Flag (CF) is not applicable for division
            emu->flags.overflow = 0;  // Overflow Flag (OF) is not applicable for division
        }
        else {
            fprintf(stderr, "DIV: Invalid instruction format\n");
            exit(EXIT_FAILURE);
        }

        printf("Executed DIV Instruction: %s = 0x%016" PRIx64 "\n", inst->dest_reg_name, result);
    }
    break;

    case INST_INC:
    {
        // Determine register size
        const char* dest_name = inst->dest_reg_name;
        size_t size = get_register_size(dest_name);
        uint64_t original_value = 0;
        uint64_t result = 0;

        if (inst->dest_is_memory) {
            // Destination is memory
            uint64_t value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("INC: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);

            // Perform the increment
            result = value + 1;
            printf("INC: Writing result 0x%016" PRIx64 " to memory address 0x%016" PRIx64 "\n", result, inst->dest_mem_address);

            // Write the incremented result to memory
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));

            // Set flags
            emu->flags.zero = (result == 0) ? 1 : 0;  // Zero Flag (ZF)
            emu->flags.sign = (result & (1ULL << 63)) ? 1 : 0;  // Sign Flag (SF)
            emu->flags.carry = (result < value) ? 1 : 0;  // Carry Flag (CF)
            emu->flags.overflow = ((value ^ result) & (1ULL << 63)) ? 1 : 0;  // Overflow Flag (OF)
        }
        else if (inst->dest_reg) {
            // Destination is a register
            original_value = *inst->dest_reg;

            // Perform the increment
            result = original_value + 1;
            printf("INC: Writing result 0x%016" PRIx64 " to register %s\n", result, inst->dest_reg_name);

            // Write the incremented result to the register
            *inst->dest_reg = result;

            // Check for overflow
            if (size == 32 && result > 0xFFFFFFFF) {
                fprintf(stderr, "Error: Increment result 0x%016" PRIx64 " exceeds 32-bit register size for %s\n", result, dest_name);
                return;
            }
            // 64-bit can hold all results

            // Set flags
            emu->flags.zero = (result == 0) ? 1 : 0;  // Zero Flag (ZF)
            emu->flags.sign = (result & (1ULL << (size * 8 - 1))) ? 1 : 0;  // Sign Flag (SF)
            emu->flags.carry = (result < original_value) ? 1 : 0;  // Carry Flag (CF)
            emu->flags.overflow = ((original_value ^ result) & (1ULL << (size * 8 - 1))) ? 1 : 0;  // Overflow Flag (OF)
        }
        else {
            fprintf(stderr, "INC: Invalid instruction format\n");
            exit(EXIT_FAILURE);
        }

        printf("Executed INC Instruction: %s = 0x%016" PRIx64 "\n", inst->dest_reg_name, result);
    }
    break;

    case INST_DEC:
    {
        // Determine if the destination is a register or memory
        if (inst->dest_is_memory) {
            // Read the current value from memory
            uint64_t value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("DEC: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);

            // Perform the decrement
            uint64_t result = value - 1;
            printf("DEC: Writing result 0x%016" PRIx64 " to memory address 0x%016" PRIx64 "\n", result, inst->dest_mem_address);

            // Write the decremented result to memory
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));

            // Set flags
            emu->flags.zero = (result == 0) ? 1 : 0;  // Zero Flag (ZF)
            emu->flags.sign = (result & (1ULL << 63)) ? 1 : 0;  // Sign Flag (SF)
            emu->flags.carry = (value == 0) ? 1 : 0;  // Carry Flag (CF)
            emu->flags.overflow = ((value ^ result) & (1ULL << 63)) ? 1 : 0;  // Overflow Flag (OF)
        }
        else if (inst->dest_reg) {
            // Determine register size
            const char* dest_name = inst->dest_reg_name;
            size_t size = get_register_size(dest_name);
            uint64_t original_value = *inst->dest_reg;

            // Perform the decrement
            (*inst->dest_reg)--;

            // Check for underflow (since unsigned, it wraps around)
            // For simplicity, we'll allow it but notify
            if (size == 32 && *inst->dest_reg > 0xFFFFFFFF) {
                fprintf(stderr, "Warning: Decrement result 0x%016" PRIx64 " wrapped around for 32-bit register %s\n", *inst->dest_reg, dest_name);
            }
            // 64-bit can hold all results without wrapping in most practical scenarios

            // Update zero flag
            emu->flags.zero = (*inst->dest_reg == 0);

            // Update sign flag
            emu->flags.sign = (*inst->dest_reg & (1ULL << (size * 8 - 1))) != 0;

            // Update overflow flag
            emu->flags.overflow = ((original_value ^ *inst->dest_reg) & (1ULL << (size * 8 - 1))) != 0;

            printf("Executed DEC Instruction: %s = 0x%016" PRIx64 "\n", inst->dest_reg_name, *inst->dest_reg);
        }
        else {
            fprintf(stderr, "DEC: Invalid instruction format\n");
            exit(EXIT_FAILURE);
        }
    }
    break;

    case INST_NEG:
    {
        // Determine if the destination is a register or memory
        if (inst->dest_is_memory) {
            // Read the current value from memory
            uint64_t value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("NEG: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);

            // Perform the negation
            uint64_t result = -value;
            printf("NEG: Writing result 0x%016" PRIx64 " to memory address 0x%016" PRIx64 "\n", result, inst->dest_mem_address);

            // Write the negated result to memory
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));

            // Set flags
            emu->flags.zero = (result == 0) ? 1 : 0;  // Zero Flag (ZF)
            emu->flags.sign = (result & (1ULL << 63)) ? 1 : 0;  // Sign Flag (SF)
            emu->flags.carry = (value != 0) ? 1 : 0;  // Carry Flag (CF)
            emu->flags.overflow = (value == (1ULL << 63)) ? 1 : 0;  // Overflow Flag (OF)
        }
        else if (inst->dest_reg) {
            // Determine register size
            const char* dest_name = inst->dest_reg_name;
            size_t size = get_register_size(dest_name);
            uint64_t original_value = *inst->dest_reg;

            // Perform the negation
            *inst->dest_reg = -(*inst->dest_reg);

            // Check if result fits in the register size
            if (size == 32 && *inst->dest_reg > 0xFFFFFFFF) {
                fprintf(stderr, "Error: Negation result 0x%016" PRIx64 " exceeds 32-bit register size for %s\n", *inst->dest_reg, dest_name);
                return;
            }
            // 64-bit can hold all results

            // Update zero flag
            emu->flags.zero = (*inst->dest_reg == 0);

            // Update sign flag
            emu->flags.sign = (*inst->dest_reg & (1ULL << (size * 8 - 1))) != 0;

            // Update overflow flag
            emu->flags.overflow = (original_value == (1ULL << (size * 8 - 1)));

            // Update carry flag
            emu->flags.carry = (original_value != 0);

            printf("Executed NEG Instruction: %s = 0x%016" PRIx64 "\n", inst->dest_reg_name, *inst->dest_reg);
        }
        else {
            fprintf(stderr, "NEG: Invalid instruction format\n");
            exit(EXIT_FAILURE);
        }
    }
    break;

    case INST_CMP:
        // Handle CMP instruction
    {
        // Determine register size
        const char* dest_name = inst->dest_reg_name;
        size_t size = get_register_size(dest_name);

        uint64_t result;
        if (inst->src_reg)
            result = *inst->dest_reg - *inst->src_reg;
        else
            result = *inst->dest_reg - inst->immediate;


        // Update zero flag
        emu->flags.zero = (result == 0);

        // Update sign flag
        emu->flags.sign = (result & (1ULL << (size * 8 - 1))) != 0;

        uint64_t operand_value = inst->src_reg ? *inst->src_reg : inst->immediate;
        // Update carry flag
        emu->flags.carry = (*inst->dest_reg < operand_value);

        // Update overflow flag
        emu->flags.overflow = ((*inst->dest_reg ^ operand_value) & (*inst->dest_reg ^ result) & (1ULL << (size * 8 - 1))) != 0;

        printf("Executed CMP Instruction: Zero Flag = %d, Sign Flag = %d, Carry Flag = %d, Overflow Flag = %d\n",
            emu->flags.zero, emu->flags.sign, emu->flags.carry, emu->flags.overflow);
    }
    break;
    // Logical Instructions
    case INST_AND:
    {
        uint64_t value1 = 0;
        uint64_t value2 = 0;

        // Get the destination operand
        if (inst->dest_is_memory) {
            value1 = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("AND: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value1, inst->dest_mem_address);
        }
        else if (inst->dest_reg) {
            value1 = *inst->dest_reg;
            printf("AND: Reading value 0x%016" PRIx64 " from register %s\n", value1, inst->dest_reg_name);
        }

        // Get the source operand
        if (inst->src_is_memory) {
            value2 = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
            printf("AND: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value2, inst->src_mem_address);
        }
        else if (inst->src_reg) {
            value2 = *inst->src_reg;
            printf("AND: Reading value 0x%016" PRIx64 " from register %s\n", value2, inst->src_reg_name);
        }
        else {
            value2 = inst->immediate;
            printf("AND: Using immediate value 0x%016" PRIx64 " for AND operation\n", value2);
        }

        // Perform the bitwise AND
        uint64_t result = value1 & value2;
        printf("AND: Result of 0x%016" PRIx64 " AND 0x%016" PRIx64 " is 0x%016" PRIx64 "\n", value1, value2, result);

        // Store the result in the destination (register or memory)
        if (inst->dest_is_memory) {
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));
        }
        else if (inst->dest_reg) {
            *inst->dest_reg = result;
        }

        // Determine register size
        const char* dest_name = inst->dest_reg_name;
        size_t size = get_register_size(dest_name);

        // Ensure the result fits in the register size
        if (size == 32 && result > 0xFFFFFFFF) {
            fprintf(stderr, "Error: AND result 0x%016" PRIx64 " exceeds 32-bit register size for %s\n", result, dest_name);
        }
        // 64-bit can hold all results
    }
    break;

    case INST_OR:
    {
        uint64_t value1 = 0;
        uint64_t value2 = 0;

        // Get the destination operand
        if (inst->dest_is_memory) {
            value1 = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("OR: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value1, inst->dest_mem_address);
        }
        else if (inst->dest_reg) {
            value1 = *inst->dest_reg;
            printf("OR: Reading value 0x%016" PRIx64 " from register %s\n", value1, inst->dest_reg_name);
        }

        // Get the source operand
        if (inst->src_is_memory) {
            value2 = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
            printf("OR: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value2, inst->src_mem_address);
        }
        else if (inst->src_reg) {
            value2 = *inst->src_reg;
            printf("OR: Reading value 0x%016" PRIx64 " from register %s\n", value2, inst->src_reg_name);
        }
        else {
            value2 = inst->immediate;
            printf("OR: Using immediate value 0x%016" PRIx64 " for OR operation\n", value2);
        }

        // Perform the bitwise OR
        uint64_t result = value1 | value2;
        printf("OR: Result of 0x%016" PRIx64 " OR 0x%016" PRIx64 " is 0x%016" PRIx64 "\n", value1, value2, result);

        // Store the result in the destination (register or memory)
        if (inst->dest_is_memory) {
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));
        }
        else if (inst->dest_reg) {
            *inst->dest_reg = result;
        }

        // Determine register size
        const char* dest_name = inst->dest_reg_name;
        size_t size = get_register_size(dest_name);

        // Ensure the result fits in the register size
        if (size == 32 && result > 0xFFFFFFFF) {
            fprintf(stderr, "Error: OR result 0x%016" PRIx64 " exceeds 32-bit register size for %s\n", result, dest_name);
        }
        // 64-bit can hold all results

        // Update zero flag
        emu->flags.zero = (result == 0);

        // Update sign flag
        emu->flags.sign = (result & (1ULL << (size * 8 - 1))) != 0;
    }
    break;

    case INST_XOR:
    {
        uint64_t value1 = 0;
        uint64_t value2 = 0;

        // Get the destination operand
        if (inst->dest_is_memory) {
            value1 = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("XOR: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value1, inst->dest_mem_address);
        }
        else if (inst->dest_reg) {
            value1 = *inst->dest_reg;
            printf("XOR: Reading value 0x%016" PRIx64 " from register %s\n", value1, inst->dest_reg_name);
        }

        // Get the source operand
        if (inst->src_is_memory) {
            value2 = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
            printf("XOR: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value2, inst->src_mem_address);
        }
        else if (inst->src_reg) {
            value2 = *inst->src_reg;
            printf("XOR: Reading value 0x%016" PRIx64 " from register %s\n", value2, inst->src_reg_name);
        }
        else {
            value2 = inst->immediate;
            printf("XOR: Using immediate value 0x%016" PRIx64 " for XOR operation\n", value2);
        }

        // Perform the bitwise XOR
        uint64_t result = value1 ^ value2;
        printf("XOR: Result of 0x%016" PRIx64 " XOR 0x%016" PRIx64 " is 0x%016" PRIx64 "\n", value1, value2, result);

        // Store the result in the destination (register or memory)
        if (inst->dest_is_memory) {
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));
        }
        else if (inst->dest_reg) {
            *inst->dest_reg = result;
        }

        // Determine register size
        const char* dest_name = inst->dest_reg_name;
        size_t size = get_register_size(dest_name);

        // Ensure the result fits in the register size
        if (size == 32 && result > 0xFFFFFFFF) {
            fprintf(stderr, "Error: XOR result 0x%016" PRIx64 " exceeds 32-bit register size for %s\n", result, dest_name);
        }
        // 64-bit can hold all results
    }
    break;

    case INST_NOT:
    {
        uint64_t value = 0;

        // Get the operand (only one operand for NOT instruction)
        if (inst->dest_is_memory) {
            value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("NOT: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);
        }
        else if (inst->dest_reg) {
            value = *inst->dest_reg;
            printf("NOT: Reading value 0x%016" PRIx64 " from register %s\n", value, inst->dest_reg_name);
        }

        // Perform the bitwise NOT (invert all bits)
        uint64_t result = ~value;
        printf("NOT: Inverted value 0x%016" PRIx64 " to 0x%016" PRIx64 "\n", value, result);

        // Store the result in the destination (register or memory)
        if (inst->dest_is_memory) {
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));
        }
        else if (inst->dest_reg) {
            *inst->dest_reg = result;
        }

        // Determine register size
        const char* dest_name = inst->dest_reg_name;
        size_t size = get_register_size(dest_name);

        // Ensure the result fits in the register size
        if (size == 32 && result > 0xFFFFFFFF) {
            fprintf(stderr, "Error: NOT result 0x%016" PRIx64 " exceeds 32-bit register size for %s\n", result, dest_name);
        }
        // 64-bit can hold all results
    }
    break;

    // Shift and Rotate Instructions
    case INST_SHL:
    {
        uint64_t value = 0;
        uint64_t shift_count = 0;

        // Get the destination operand
        if (inst->dest_is_memory) {
            value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("SHL: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);
        }
        else if (inst->dest_reg) {
            value = *inst->dest_reg;
            printf("SHL: Reading value 0x%016" PRIx64 " from register %s\n", value, inst->dest_reg_name);
        }

        // Get the shift count (immediate or register value)
        if (inst->src_is_memory) {
            shift_count = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
            printf("SHL: Reading shift count 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", shift_count, inst->src_mem_address);
        }
        else if (inst->src_reg) {
            shift_count = *inst->src_reg;
            printf("SHL: Reading shift count 0x%016" PRIx64 " from register %s\n", shift_count, inst->src_reg_name);
        }
        else {
            shift_count = inst->immediate;
            printf("SHL: Using immediate shift count 0x%016" PRIx64 "\n", shift_count);
        }

        // Perform the left shift
        uint64_t result = value << shift_count;
        printf("SHL: Shifted value 0x%016" PRIx64 " left by 0x%016" PRIx64 " positions, result is 0x%016" PRIx64 "\n", value, shift_count, result);

        // Store the result in the destination (register or memory)
        if (inst->dest_is_memory) {
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));
        }
        else if (inst->dest_reg) {
            *inst->dest_reg = result;
        }

        // Determine register size for overflow check
        if (inst->dest_reg) {
            const char* dest_name = inst->dest_reg_name;
            size_t size = get_register_size(dest_name);

            // Check for overflow by ensuring the value fits in the register size
            if (size == 32 && result > 0xFFFFFFFF) {
                fprintf(stderr, "Error: SHL result 0x%016" PRIx64 " exceeds 32-bit register size for %s\n", result, dest_name);
            }
        }
    }
    break;

    case INST_SHR:
    {
        uint64_t value = 0;
        uint64_t shift_count = 0;

        // Get the destination operand
        if (inst->dest_is_memory) {
            value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("SHR: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);
        }
        else if (inst->dest_reg) {
            value = *inst->dest_reg;
            printf("SHR: Reading value 0x%016" PRIx64 " from register %s\n", value, inst->dest_reg_name);
        }

        // Get the shift count (immediate or register value)
        if (inst->src_is_memory) {
            shift_count = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
            printf("SHR: Reading shift count 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", shift_count, inst->src_mem_address);
        }
        else if (inst->src_reg) {
            shift_count = *inst->src_reg;
            printf("SHR: Reading shift count 0x%016" PRIx64 " from register %s\n", shift_count, inst->src_reg_name);
        }
        else {
            shift_count = inst->immediate;
            printf("SHR: Using immediate shift count 0x%016" PRIx64 "\n", shift_count);
        }

        // Perform the right shift
        uint64_t result = value >> shift_count;
        printf("SHR: Shifted value 0x%016" PRIx64 " right by 0x%016" PRIx64 " positions, result is 0x%016" PRIx64 "\n", value, shift_count, result);

        // Store the result in the destination (register or memory)
        if (inst->dest_is_memory) {
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));
        }
        else if (inst->dest_reg) {
            *inst->dest_reg = result;
        }
    }
    break;

    case INST_ROL:
    {
        uint64_t value = 0;
        uint64_t rotate_count = 0;

        // Get the destination operand
        if (inst->dest_is_memory) {
            value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("ROL: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);
        }
        else if (inst->dest_reg) {
            value = *inst->dest_reg;
            printf("ROL: Reading value 0x%016" PRIx64 " from register %s\n", value, inst->dest_reg_name);
        }

        // Get the rotate count (immediate or register value)
        if (inst->src_is_memory) {
            rotate_count = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
            printf("ROL: Reading rotate count 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", rotate_count, inst->src_mem_address);
        }
        else if (inst->src_reg) {
            rotate_count = *inst->src_reg;
            printf("ROL: Reading rotate count 0x%016" PRIx64 " from register %s\n", rotate_count, inst->src_reg_name);
        }
        else {
            rotate_count = inst->immediate;
            printf("ROL: Using immediate rotate count 0x%016" PRIx64 "\n", rotate_count);
        }

        // Perform the left rotate
        uint64_t result = (value << rotate_count) | (value >> (64 - rotate_count));
        printf("ROL: Rotated value 0x%016" PRIx64 " left by 0x%016" PRIx64 " positions, result is 0x%016" PRIx64 "\n", value, rotate_count, result);

        // Store the result in the destination (register or memory)
        if (inst->dest_is_memory) {
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));
        }
        else if (inst->dest_reg) {
            *inst->dest_reg = result;
        }
    }
    break;

    case INST_ROR:
    {
        uint64_t value = 0;
        uint64_t rotate_count = 0;

        // Get the destination operand
        if (inst->dest_is_memory) {
            value = read_memory(emu, inst->dest_mem_address, sizeof(uint64_t));
            printf("ROR: Reading value 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", value, inst->dest_mem_address);
        }
        else if (inst->dest_reg) {
            value = *inst->dest_reg;
            printf("ROR: Reading value 0x%016" PRIx64 " from register %s\n", value, inst->dest_reg_name);
        }

        // Get the rotate count (immediate or register value)
        if (inst->src_is_memory) {
            rotate_count = read_memory(emu, inst->src_mem_address, sizeof(uint64_t));
            printf("ROR: Reading rotate count 0x%016" PRIx64 " from memory address 0x%016" PRIx64 "\n", rotate_count, inst->src_mem_address);
        }
        else if (inst->src_reg) {
            rotate_count = *inst->src_reg;
            printf("ROR: Reading rotate count 0x%016" PRIx64 " from register %s\n", rotate_count, inst->src_reg_name);
        }
        else {
            rotate_count = inst->immediate;
            printf("ROR: Using immediate rotate count 0x%016" PRIx64 "\n", rotate_count);
        }

        // Perform the right rotate
        uint64_t result = (value >> rotate_count) | (value << (64 - rotate_count));
        printf("ROR: Rotated value 0x%016" PRIx64 " right by 0x%016" PRIx64 " positions, result is 0x%016" PRIx64 "\n", value, rotate_count, result);

        // Store the result in the destination (register or memory)
        if (inst->dest_is_memory) {
            write_memory(emu, inst->dest_mem_address, result, sizeof(uint64_t));
        }
        else if (inst->dest_reg) {
            *inst->dest_reg = result;
        }
    }
    break;

    // Control Flow Instructions
    case INST_JMP:
        // Handle unconditional jump
        printf("JMP to label: %s\n", inst->label);
        // Find the label and update rip
        for (size_t i = 0; i < label_count; i++) {
            if (strcmp(inst->label, labels[i].label) == 0) {
                emu->rip = labels[i].index;
                return;
            }
        }
        fprintf(stderr, "Error: Label '%s' not found for JMP instruction at rip=%zu\n", inst->label, inst_num);
        break;

    case INST_JE:
        if (emu->flags.zero == 1) { // Jump if Zero Flag is set
            printf("JE condition met, jumping to label: %s\n", inst->label);
            // Loop over all labels to find the target label
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    // Jump to the label by setting rip to the label's index
                    emu->rip = labels[i].index;
                    return; // Exit the function after jumping (skips remaining code)
                }
            }
            // If label is not found
            fprintf(stderr, "Error: Label '%s' not found for JE instruction at rip=%zu\n", inst_num);
        }
        else {
            // If JE condition is not met, simply return to move to the next instruction
            printf("JE condition not met, continuing execution\n");
            return; // Return early, effectively skipping the current instruction
        }
        break;

    case INST_JNE:
        if (emu->flags.zero == 0) { // Jump if Zero Flag is not set
            printf("JNE condition met, jumping to label: %s\n", inst->label);
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return; // Exit the function after jumping
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JNE instruction at rip=%zu\n", inst->label, inst_num);
        }
        else {
            // If the condition is not met, continue to the next instruction
            printf("JNE condition not met, continuing execution\n");
            return;
        }
        break;

    case INST_JG:
        // Handle jump if greater
        if (!emu->flags.zero && !emu->flags.sign) {
            printf("JG to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JG instruction at rip=%zu\n", inst->label, inst_num);
        }
        else {
            // If the condition is not met, continue to the next instruction
            printf("JG condition not met, continuing execution\n");
            return;
        }
        break;
    case INST_JL:
        // Handle jump if less
        if (emu->flags.sign) {
            printf("JL to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JL instruction at rip=%zu\n", inst->label, inst_num);
        }
        else {
            // If the condition is not met, continue to the next instruction
            printf("JL condition not met, continuing execution\n");
            return;
        }
        break;
    case INST_JGE:
        // Handle jump if greater or equal
        if (!emu->flags.sign || emu->flags.zero) {
            printf("JGE to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JGE instruction at rip=%zu\n", inst->label, inst_num);
        }
        break;
    case INST_JLE:
        // Handle jump if less or equal
        if (emu->flags.sign || emu->flags.zero) {
            printf("JLE to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JLE instruction at rip=%zu\n", inst->label, inst_num);
        }
        break;
    case INST_JA:
        // Handle jump if above (unsigned greater)
        if (!emu->flags.carry && !emu->flags.zero) {
            printf("JA to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JA instruction at rip=%zu\n", inst->label, inst_num);
        }
        break;
    case INST_JAE:
        // Handle jump if above or equal (unsigned greater or equal)
        if (!emu->flags.carry) {
            printf("JAE to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JAE instruction at rip=%zu\n", inst->label, inst_num);
        }
        break;
    case INST_JB:
        // Handle jump if below (unsigned less)
        if (emu->flags.carry) {
            printf("JB to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JB instruction at rip=%zu\n", inst->label, inst_num);
        }
        break;
    case INST_JBE:
        // Handle jump if below or equal (unsigned less or equal)
        if (emu->flags.carry || emu->flags.zero) {
            printf("JBE to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JBE instruction at rip=%zu\n", inst->label, inst_num);
        }
        break;
    case INST_JO:
        // Handle jump if overflow
        if (emu->flags.overflow) {
            printf("JO to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JO instruction at rip=%zu\n", inst->label, inst_num);
        }
        break;
    case INST_JNO:
        // Handle jump if no overflow
        if (!emu->flags.overflow) {
            printf("JNO to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JNO instruction at rip=%zu\n", inst->label, inst_num);
        }
        break;
    case INST_JS:
        // Handle jump if sign (negative)
        if (emu->flags.sign) {
            printf("JS to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JS instruction at rip=%zu\n", inst->label, inst_num);
        }
        break;
    case INST_JNS:
        // Handle jump if no sign (non-negative)
        if (!emu->flags.sign) {
            printf("JNS to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JNS instruction at rip=%zu\n", inst->label, inst_num);
        }
        break;
    case INST_JP:
        // Handle jump if parity even
        if (emu->flags.parity) {
            printf("JP to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JP instruction at rip=%zu\n", inst->label, inst_num);
        }
        break;
    case INST_JNP:
        // Handle jump if no parity (odd)
        if (!emu->flags.parity) {
            printf("JNP to label: %s\n", inst->label);
            // Find the label and update rip
            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(inst->label, labels[i].label) == 0) {
                    emu->rip = labels[i].index;
                    return;
                }
            }
            fprintf(stderr, "Error: Label '%s' not found for JNP instruction at rip=%zu\n", inst->label, inst_num);
        }
        break;
        // Custom Instructions
    case INST_POW:
        execute_pow_instruction(emu, inst);
        break;

    case INST_ROOT:
        execute_root_instruction(emu, inst);
        break;

    case INST_AVG:
        execute_avg_instruction(emu, inst);
        break;

    case INST_MAX:
        execute_max_instruction(emu, inst);
        break;

    case INST_MIN:
        execute_min_instruction(emu, inst);
        break;

    case INST_MOD:
        execute_mod_instruction(emu, inst);
        break;

    case INST_ISPRIME:
        execute_isprime_instruction(emu, inst);
        break;

    case INST_MIRROR:
        execute_mirror_instruction(emu, inst);
        break;

    case INST_NOP:
        printf("Executed NOP Instruction: No operation performed\n");
        break;

    case INST_LABEL:
        // Labels are handled during parsing; no action needed during execution
        break;

    case INST_COMMENT:
        // Comments are ignored in execution
        break;

    default:
        fprintf(stderr, "Unknown instruction type\n");
    }

    if (tracing_enabled) {
        // Print registers after execution
        print_emulator_state(emu, "After Execution");
    }
}


// Function to execute instructions from a file
void execute_file_instructions(Emulator* emu, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
        exit(1);
    }

    // Dynamic allocation for instructions and labels
    size_t instruction_capacity = INITIAL_CAPACITY;
    size_t instruction_count = 0;
    Instruction* instructions = malloc(instruction_capacity * sizeof(Instruction));
    if (!instructions) {
        fprintf(stderr, "Error: Memory allocation failed for instructions\n");
        exit(1);
    }

    size_t label_capacity = INITIAL_CAPACITY;
    size_t label_count = 0;
    Label* labels = malloc(label_capacity * sizeof(Label));
    if (!labels) {
        fprintf(stderr, "Error: Memory allocation failed for labels\n");
        exit(1);
    }

    char line[256];
    size_t line_num = 0;
    while (fgets(line, sizeof(line), file)) {
        line_num++;

        // Remove newline character
        line[strcspn(line, "\r\n")] = 0;

        // Skip empty lines
        if (strlen(line) == 0) continue;

        // Handle comments
        if (line[0] == ';') continue; // Skip entire line if it starts with ';'

        // Tokenize the line
        char* token = strtok(line, " \t,");
        if (!token) continue;

        // Check if the line is a label (ends with ':')
        size_t tok_len = strlen(token);
        if (token[tok_len - 1] == ':') {
            token[tok_len - 1] = '\0'; // Remove ':'
            if (label_count >= 1000) {
                fprintf(stderr, "Error: Maximum label count exceeded\n");
                exit(1);
            }
            strcpy(labels[label_count].label, token);
            labels[label_count].index = instruction_count;
            (label_count)++;
            continue; // Labels are not actual instructions
        }
        // Get instruction type
        InstructionType type = get_instruction_type(token);
        if (type == INST_NOP && strcasecmp(token, "NOP") != 0) {
            fprintf(stderr, "Error: Unknown instruction '%s' at line %zu\n", token, line_num);
            continue;
        }

        // Initialize Instruction struct
        Instruction inst;
        memset(&inst, 0, sizeof(Instruction));
        inst.type = type;
        inst.immediate = 0;
        inst.format = HEX; // Default to HEX as per user request

        // Parse operands based on instruction type
        switch (type) {

        case INST_ADD:
        case INST_SUB:
        case INST_MUL:
        case INST_DIV:
        case INST_AND:
        case INST_OR:
        case INST_XOR:
        case INST_MOD:
        {
            // Expect two operands: dest, src or immediate
            char* operands[3] = { NULL, NULL, NULL };
            int operand_count = 0;
            // Collect up to two operands
            while ((token = strtok(NULL, " \t,")) != NULL && operand_count < 2) {
                operands[operand_count++] = token;
            }
            // Assign destination register or memory
            if (operand_count >= 1) {
                inst.dest_reg = get_register_pointer(emu, operands[0]);
                if (!inst.dest_reg) {
                    // Check if it's a memory address (e.g., "[0x100]")
                    if (strchr(operands[0], '[') != NULL && strchr(operands[0], ']') != NULL) {
                        // Extract memory address (remove "[" and "]")
                        char addr_str[20];  // Buffer to hold the address part
                        char* start = strchr(operands[0], '[') + 1;  // Start after '['
                        char* end = strchr(operands[0], ']');       // Find the closing ']'
                        if (end <= start) {
                            fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operands[0], line_num);
                            break;
                        }
                        strncpy(addr_str, start, end - start);  // Copy the address part
                        addr_str[end - start] = '\0';           // Null-terminate the address string
                        inst.dest_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
                        inst.dest_is_memory = 1;  // Mark destination as memory
                        strcpy(inst.dest_reg_name, operands[0]);  // Store original memory address notation
                    }
                    else {
                        fprintf(stderr, "Error: Invalid destination operand '%s' at line %zu\n", operands[0], line_num);
                        break;
                    }
                }
                else {
                    inst.dest_is_memory = 0;  // Mark destination as register
                    strcpy(inst.dest_reg_name, operands[0]); // Store original register name
                }
            }
            else {
                fprintf(stderr, "Error: Missing destination operand for '%s' at line %zu\n", (type == INST_MOV ? "MOV" :
                    (type == INST_ADD ? "ADD" :
                        (type == INST_SUB ? "SUB" :
                            (type == INST_MUL ? "MUL" :
                                (type == INST_DIV ? "DIV" :
                                    (type == INST_AND ? "AND" :
                                        (type == INST_OR ? "OR" :
                                            (type == INST_XOR ? "XOR" : "MOD"))))))))), line_num;
                                            break;
            }
            // Assign source register or immediate or memory
            if (operand_count >= 2) {
                uint64_t* src_ptr = get_register_pointer(emu, operands[1]);
                if (src_ptr) {
                    inst.src_reg = src_ptr;
                    inst.src_is_memory = 0;  // Source is a register
                    strcpy(inst.src_reg_name, operands[1]); // Store original register name
                }
                else if (strchr(operands[1], '[') != NULL && strchr(operands[1], ']') != NULL) {
                    // Handle memory operand (e.g., "[0x100]")
                    char addr_str[20];  // Buffer to hold the address part
                    char* start = strchr(operands[1], '[') + 1;  // Start after '['
                    char* end = strchr(operands[1], ']');       // Find the closing ']'
                    if (end <= start) {
                        fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operands[1], line_num);
                        break;
                    }
                    strncpy(addr_str, start, end - start);  // Copy the address part
                    addr_str[end - start] = '\0';           // Null-terminate the address string
                    inst.src_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
                    inst.src_is_memory = 1;  // Source is memory
                    strcpy(inst.src_reg_name, operands[1]);  // Store original memory address notation
                }
                else {
                    // Assume immediate value
                    if (strncmp(operands[1], "0x", 2) == 0 || strncmp(operands[1], "0X", 2) == 0) {
                        inst.immediate = strtoull(operands[1], NULL, 16);  // Hexadecimal
                    }
                    else {
                        inst.immediate = strtoull(operands[1], NULL, 10);  // Decimal
                    }
                    inst.src_is_memory = 0;  // Source is immediate, not memory
                    strcpy(inst.src_reg_name, operands[1]); // Store immediate value as name
                }
            }
            else {
                // Fill remaining operands with NULL or 0 if less than 2 operands
                inst.src_reg = NULL;
                inst.immediate = 0;
                inst.src_is_memory = 0;  // No source memory in this case
            }
        }
        break;

case INST_MOV:
    // Expect two operands: dest, src or immediate
    char* operands[3] = { NULL, NULL, NULL };
    int operand_count = 0;
    while ((token = strtok(NULL, " \t,")) != NULL && operand_count < 2) {
        operands[operand_count++] = token;
    }

    // Assign destination register or memory
    if (operand_count >= 1) {
        if (strchr(operands[0], '[') != NULL && strchr(operands[0], ']') != NULL) {
            // Memory address
            char addr_str[20];
            char* start = strchr(operands[0], '[') + 1;
            char* end = strchr(operands[0], ']');
            strncpy(addr_str, start, end - start);
            addr_str[end - start] = '\0';
            inst.dest_mem_address = strtoull(addr_str, NULL, 0);
            inst.dest_is_memory = 1;
            strcpy(inst.dest_reg_name, operands[0]);  // Store original memory address notation
        } else {
            // Register
            inst.dest_reg = get_register_pointer(emu, operands[0]);
            if (!inst.dest_reg) {
                fprintf(stderr, "Error: Invalid destination operand '%s' at line %zu\n", operands[0], line_num);
                break;
            }
            inst.dest_is_memory = 0;
            strcpy(inst.dest_reg_name, operands[0]);
        }
    } else {
        fprintf(stderr, "Error: Missing destination operand for 'MOV' at line %zu\n", line_num);
        break;
    }

    // Assign source register, immediate, or string
    if (operand_count >= 2) {
        if (operands[1][0] == '"') {
            // String literal
            inst.src_is_string = 1;
            // Remove quotes and copy the entire string
            size_t len = strlen(operands[1]);
            if (len >= 2) {
                strncpy(inst.src_string, operands[1] + 1, len - 2);
                inst.src_string[len - 2] = '\0'; // Null-terminate
            }
        } else {
            uint64_t* src_ptr = get_register_pointer(emu, operands[1]);
            if (src_ptr) {
                inst.src_reg = src_ptr;
                inst.src_is_memory = 0;  // Source is a register
                strcpy(inst.src_reg_name, operands[1]); // Store original register name
            } else if (strchr(operands[1], '[') != NULL && strchr(operands[1], ']') != NULL) {
                // Handle memory operand (e.g., "[0x100]")
                char addr_str[20];  // Buffer to hold the address part
                char* start = strchr(operands[1], '[') + 1;  // Start after '['
                char* end = strchr(operands[1], ']');       // Find the closing ']'
                if (end <= start) {
                    fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operands[1], line_num);
                    break;
                }
                strncpy(addr_str, start, end - start);  // Copy the address part
                addr_str[end - start] = '\0';           // Null-terminate the address string
                inst.src_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
                inst.src_is_memory = 1;  // Source is memory
                strcpy(inst.src_reg_name, operands[1]);  // Store original memory address notation
            } else {
                // Assume immediate value
                if (strncmp(operands[1], "0x", 2) == 0 || strncmp(operands[1], "0X", 2) == 0) {
                    inst.immediate = strtoull(operands[1], NULL, 16);  // Hexadecimal
                } else {
                    inst.immediate = strtoull(operands[1], NULL, 10);  // Decimal
                }
                inst.src_is_memory = 0;  // Source is immediate, not memory
                strcpy(inst.src_reg_name, operands[1]); // Store immediate value as name
            }
        }
    } else {
        // Fill remaining operands with NULL or 0 if less than 2 operands
        inst.src_reg = NULL;
        inst.immediate = 0;
        inst.src_is_memory = 0;  // No source memory in this case
    }
    break;

            case INST_INT:
            {
                char* operands[2] = { NULL, NULL };
                int operand_count = 0;

                // Collect operands
                while ((token = strtok(NULL, " \t,")) != NULL && operand_count < 2) {
                    operands[operand_count++] = token;
                }

                // Parse the interrupt number
                if (operand_count >= 1) {
                    // Get the interrupt number
                    if (strncmp(operands[0], "0x", 2) == 0) {
                        inst.immediate = strtoull(operands[0], NULL, 16);  // Hexadecimal
                    } else {
                        inst.immediate = strtoull(operands[0], NULL, 10);  // Decimal
                    }

                    // If there's a second operand, it's the interrupt function number
                    if (operand_count == 2) {
                        if (strncmp(operands[1], "0x", 2) == 0) {
                            inst.function = strtoull(operands[1], NULL, 16);  // Hexadecimal
                        } else {
                            inst.function = strtoull(operands[1], NULL, 10);  // Decimal
                        }
                    }
                }
            }
            break;

        case INST_PUSH:
        case INST_POP:
        case INST_NEG:
        case INST_INC:
        case INST_DEC:
        case INST_NOT:
        {
            // Expect one operand: either a register or memory
            char* operand = strtok(NULL, " \t,");
            if (operand) {
                inst.dest_reg = get_register_pointer(emu, operand);
                if (!inst.dest_reg) {
                    // Check if it's a memory address (e.g., "[0x100]")
                    if (strchr(operand, '[') != NULL && strchr(operand, ']') != NULL) {
                        // Extract memory address (remove "[" and "]")
                        char addr_str[20];  // Buffer to hold the address part
                        char* start = strchr(operand, '[') + 1;  // Start after '['
                        char* end = strchr(operand, ']');       // Find the closing ']'
                        if (end <= start) {
                            fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operand, line_num);
                            break;
                        }
                        strncpy(addr_str, start, end - start);  // Copy the address part
                        addr_str[end - start] = '\0';           // Null-terminate the address string
                        inst.dest_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
                        inst.dest_is_memory = 1;  // Mark destination as memory
                        strcpy(inst.dest_reg_name, operand); // Store original memory address notation
                    }
                    else {
                        fprintf(stderr, "Error: Invalid operand '%s' at line %zu\n", operand, line_num);
                        break;
                    }
                }
                else {
                    inst.dest_is_memory = 0;  // Mark destination as register
                    strcpy(inst.dest_reg_name, operand); // Store original register name
                }
            }
            else {
                fprintf(stderr, "Error: Missing operand for '%s' at line %zu\n", (type == INST_PUSH ? "PUSH" :
                    (type == INST_POP ? "POP" :
                        (type == INST_NEG ? "NEG" :
                            (type == INST_INC ? "INC" :
                                (type == INST_DEC ? "DEC" : "NOT"))))), line_num);
                break;
            }

            // Ensure source-related fields are unset for these instructions
            inst.src_reg = NULL;
            inst.immediate = 0;
            inst.src_is_memory = 0;
        }
        break;

        case INST_CMP:
        {
            // Expect two operands: dest, src or immediate
            char* operands[3] = { NULL, NULL, NULL };
            int operand_count = 0;
            // Collect up to two operands
            while ((token = strtok(NULL, " \t,")) != NULL && operand_count < 2) {
                operands[operand_count++] = token;
            }
            // Assign destination register or memory
            if (operand_count >= 1) {
                inst.dest_reg = get_register_pointer(emu, operands[0]);
                if (!inst.dest_reg) {
                    // Check if it's a memory address (e.g., "[0x100]")
                    if (strchr(operands[0], '[') != NULL && strchr(operands[0], ']') != NULL) {
                        // Extract memory address (remove "[" and "]")
                        char addr_str[20];  // Buffer to hold the address part
                        char* start = strchr(operands[0], '[') + 1;  // Start after '['
                        char* end = strchr(operands[0], ']');       // Find the closing ']'
                        if (end <= start) {
                            fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operands[0], line_num);
                            break;
                        }
                        strncpy(addr_str, start, end - start);  // Copy the address part
                        addr_str[end - start] = '\0';           // Null-terminate the address string
                        inst.dest_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
                        inst.dest_is_memory = 1;  // Mark destination as memory
                        strcpy(inst.dest_reg_name, operands[0]); // Store original memory address notation
                    }
                    else {
                        fprintf(stderr, "Error: Invalid destination operand '%s' at line %zu\n", operands[0], line_num);
                        break;
                    }
                }
                else {
                    inst.dest_is_memory = 0;  // Mark destination as register
                    strcpy(inst.dest_reg_name, operands[0]); // Store original register name
                }
            }
            else {
                fprintf(stderr, "Error: Missing destination operand for 'CMP' at line %zu\n", line_num);
                break;
            }
            // Assign source register or immediate or memory
            if (operand_count >= 2) {
                uint64_t* src_ptr = get_register_pointer(emu, operands[1]);
                if (src_ptr) {
                    inst.src_reg = src_ptr;
                    inst.src_is_memory = 0;  // Source is a register
                    strcpy(inst.src_reg_name, operands[1]); // Store original register name
                }
                else if (strchr(operands[1], '[') != NULL && strchr(operands[1], ']') != NULL) {
                    // Handle memory operand (e.g., "[0x100]")
                    char addr_str[20];  // Buffer to hold the address part
                    char* start = strchr(operands[1], '[') + 1;  // Start after '['
                    char* end = strchr(operands[1], ']');       // Find the closing ']'
                    if (end <= start) {
                        fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operands[1], line_num);
                        break;
                    }
                    strncpy(addr_str, start, end - start);  // Copy the address part
                    addr_str[end - start] = '\0';           // Null-terminate the address string
                    inst.src_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
                    inst.src_is_memory = 1;  // Source is memory
                    strcpy(inst.src_reg_name, operands[1]);  // Store original memory address notation
                }
                else {
                    // Assume immediate value
                    if (strncmp(operands[1], "0x", 2) == 0 || strncmp(operands[1], "0X", 2) == 0) {
                        inst.immediate = strtoull(operands[1], NULL, 16);  // Hexadecimal
                    }
                    else {
                        inst.immediate = strtoull(operands[1], NULL, 10);  // Decimal
                    }
                    inst.src_is_memory = 0;  // Source is immediate, not memory
                    strcpy(inst.src_reg_name, operands[1]); // Store immediate value as name
                }
            }
            else {
                fprintf(stderr, "Error: Missing source operand for 'CMP' at line %zu\n", line_num);
                break;
            }
        }
        break;

        case INST_XCHG:
        {
            // Expect two operands: src, dest
            char* operands[3] = { NULL, NULL, NULL };
            int operand_count = 0;

            // Collect up to two operands
            while ((token = strtok(NULL, " \t,")) != NULL && operand_count < 2) {
                operands[operand_count++] = token;
            }

            // Assign destination operand (this will be the first operand)
            if (operand_count >= 1) {
                inst.dest_reg = get_register_pointer(emu, operands[0]);
                if (!inst.dest_reg) {
                    // Check if it's a memory address (e.g., "[0x100]")
                    if (strchr(operands[0], '[') != NULL && strchr(operands[0], ']') != NULL) {
                        // Extract memory address (remove "[" and "]")
                        char addr_str[20];  // Buffer to hold the address part
                        char* start = strchr(operands[0], '[') + 1;  // Start after '['
                        char* end = strchr(operands[0], ']');       // Find the closing ']'
                        if (end <= start) {
                            fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operands[0], line_num);
                            break;
                        }
                        strncpy(addr_str, start, end - start);  // Copy the address part
                        addr_str[end - start] = '\0';           // Null-terminate the address string
                        inst.dest_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
                        inst.dest_is_memory = 1;  // Mark destination as memory
                    }
                    else {
                        fprintf(stderr, "Error: Invalid destination operand '%s' at line %zu\n", operands[0], line_num);
                        break;
                    }
                }
                else {
                    inst.dest_is_memory = 0;  // Mark destination as register
                    // Store original register name (added from second code)
                    strcpy(inst.dest_reg_name, operands[0]);
                }
            }
            else {
                fprintf(stderr, "Error: Missing destination operand for instruction at line %zu\n", line_num);
                break;
            }

            // Assign source operand (this will be the second operand)
            if (operand_count >= 2) {
                inst.src_reg = get_register_pointer(emu, operands[1]);
                if (!inst.src_reg) {
                    // Check if it's a memory address (e.g., "[0x100]")
                    if (strchr(operands[1], '[') != NULL && strchr(operands[1], ']') != NULL) {
                        // Extract memory address (remove "[" and "]")
                        char addr_str[20];  // Buffer to hold the address part
                        char* start = strchr(operands[1], '[') + 1;  // Start after '['
                        char* end = strchr(operands[1], ']');       // Find the closing ']'
                        if (end <= start) {
                            fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operands[1], line_num);
                            break;
                        }
                        strncpy(addr_str, start, end - start);  // Copy the address part
                        addr_str[end - start] = '\0';           // Null-terminate the address string
                        inst.src_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
                        inst.src_is_memory = 1;  // Source is memory
                    }
                    else {
                        fprintf(stderr, "Error: Invalid source operand '%s' at line %zu\n", operands[1], line_num);
                        break;
                    }
                }
                else {
                    inst.src_is_memory = 0;  // Source is a register
                    // Store original register name (added from second code)
                    strcpy(inst.src_reg_name, operands[1]);
                }
            }
            else {
                fprintf(stderr, "Error: Missing source operand for instruction at line %zu\n", line_num);
                break;
            }

            // Now perform the exchange (swap the values)
            if (inst.dest_is_memory && inst.src_is_memory) {
                // Swap values between two memory locations
                uint64_t temp = read_memory(emu, inst.dest_mem_address,sizeof(temp));
                uint64_t src_val = read_memory(emu, inst.src_mem_address,sizeof(src_val));
                write_memory(emu, inst.dest_mem_address, src_val,sizeof(src_val));
                write_memory(emu, inst.src_mem_address, temp,sizeof(temp));
            }
            else if (inst.dest_is_memory && !inst.src_is_memory) {
                // Swap value between memory and register
                uint64_t temp = read_memory(emu, inst.dest_mem_address,sizeof(temp));
                uint64_t src_val = *inst.src_reg;
                write_memory(emu, inst.dest_mem_address, src_val,sizeof(src_val));
                *inst.src_reg = temp;
            }
            else if (!inst.dest_is_memory && inst.src_is_memory) {
                // Swap value between register and memory
                uint64_t temp = *inst.dest_reg;
                uint64_t src_val = read_memory(emu, inst.src_mem_address,sizeof(src_val));
                *inst.dest_reg = src_val;
                write_memory(emu, inst.src_mem_address, temp,sizeof(temp));
            }
            else if (!inst.dest_is_memory && !inst.src_is_memory) {
                // Swap values between two registers
                uint64_t temp = *inst.dest_reg;
                *inst.dest_reg = *inst.src_reg;
                *inst.src_reg = temp;
            }

            // No flags need to be set for XCHG since it's a simple swap operation
        }
        break;

case INST_ROL:
case INST_ROR:
case INST_SHL:
case INST_SHR:
{
    // Expect two operands: dest, src or immediate
    char* operands[3] = { NULL, NULL, NULL };
    int operand_count = 0;
    // Collect up to two operands
    while ((token = strtok(NULL, " \t,")) != NULL && operand_count < 2) {
        operands[operand_count++] = token;
    }

    // Assign destination operand (this will be the first operand)
    if (operand_count >= 1) {
        inst.dest_reg = get_register_pointer(emu, operands[0]);
        if (!inst.dest_reg) {
            // Check if it's a memory address (e.g., "[0x100]")
            if (strchr(operands[0], '[') != NULL && strchr(operands[0], ']') != NULL) {
                // Extract memory address (remove "[" and "]")
                char addr_str[20];  // Buffer to hold the address part
                char* start = strchr(operands[0], '[') + 1;  // Start after '['
                char* end = strchr(operands[0], ']');       // Find the closing ']'
                if (end <= start) {
                    fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operands[0], line_num);
                    break;
                }
                strncpy(addr_str, start, end - start);  // Copy the address part
                addr_str[end - start] = '\0';           // Null-terminate the address string
                inst.dest_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
                inst.dest_is_memory = 1;  // Mark destination as memory
            }
            else {
                fprintf(stderr, "Error: Invalid destination operand '%s' at line %zu\n", operands[0], line_num);
                break;
            }
        }
        else {
            inst.dest_is_memory = 0;  // Mark destination as register
            strcpy(inst.dest_reg_name, operands[0]); // Store original register name
        }
    }
    else {
        fprintf(stderr, "Error: Missing destination operand for '%s' at line %zu\n",
            (type == INST_ROL ? "ROL" :
                (type == INST_ROR ? "ROR" :
                    (type == INST_SHL ? "SHL" : "SHR"))), line_num);
        break;
    }

    // Assign source (shift amount) operand
    uint64_t shift_amount = 0;
    if (operand_count >= 2) {
        uint64_t* src_ptr = get_register_pointer(emu, operands[1]);
        if (src_ptr) {
            // If it's a register, get its value
            inst.src_reg = src_ptr;
            strcpy(inst.src_reg_name, operands[1]); // Store original register name
            shift_amount = *src_ptr;
        }
        else {
            // Assume immediate value
            if (strncmp(operands[1], "0x", 2) == 0 || strncmp(operands[1], "0X", 2) == 0) {
                shift_amount = strtoull(operands[1], NULL, 16);
            }
            else {
                shift_amount = strtoull(operands[1], NULL, 10);
            }
            inst.immediate = shift_amount;
        }
    }
    else {
        // If no second operand, set shift amount to 0
        shift_amount = 0;
        inst.src_reg = NULL;
        inst.immediate = 0;
    }

    // Perform the operation based on the instruction type
    if (inst.dest_is_memory) {
        uint64_t value = read_memory(emu, inst.dest_mem_address,sizeof(value));
        switch (type) {
        case INST_ROL:
            value = (value << shift_amount) | (value >> (64 - shift_amount));
            break;
        case INST_ROR:
            value = (value >> shift_amount) | (value << (64 - shift_amount));
            break;
        case INST_SHL:
            value <<= shift_amount;
            break;
        case INST_SHR:
            value >>= shift_amount;
            break;
        }
        write_memory(emu, inst.dest_mem_address, value,sizeof(value));
    }
    else {
        uint64_t* reg_value = inst.dest_reg;
        switch (type) {
        case INST_ROL:
            *reg_value = (*reg_value << shift_amount) | (*reg_value >> (64 - shift_amount));
            break;
        case INST_ROR:
            *reg_value = (*reg_value >> shift_amount) | (*reg_value << (64 - shift_amount));
            break;
        case INST_SHL:
            *reg_value <<= shift_amount;
            break;
        case INST_SHR:
            *reg_value >>= shift_amount;
            break;
        }
    }
    // No flags need to be set for these operations as it's purely bit manipulation
}
break;

case INST_POW:
{
    // Expect two operands: base (register or memory), and exponent (register, memory, or immediate)
    char* operands[3] = { NULL, NULL, NULL };
    int operand_count = 0;

    // Collect up to two operands
    while ((token = strtok(NULL, " \t,")) != NULL && operand_count < 2) {
        operands[operand_count++] = token;
    }

    // Assign the base operand (this will be the first operand)
    if (operand_count >= 1) {
        inst.dest_reg = get_register_pointer(emu, operands[0]);
        if (!inst.dest_reg) {
            // Check if it's a memory address (e.g., "[0x100]")
            if (strchr(operands[0], '[') != NULL && strchr(operands[0], ']') != NULL) {
                // Extract memory address (remove "[" and "]")
                char addr_str[20];  // Buffer to hold the address part
                char* start = strchr(operands[0], '[') + 1;  // Start after '['
                char* end = strchr(operands[0], ']');       // Find the closing ']'
                if (end <= start) {
                    fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operands[0], line_num);
                    break;
                }
                strncpy(addr_str, start, end - start);  // Copy the address part
                addr_str[end - start] = '\0';           // Null-terminate the address string
                inst.dest_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
                inst.dest_is_memory = 1;  // Mark destination as memory
            }
            else {
                fprintf(stderr, "Error: Invalid destination operand '%s' at line %zu\n", operands[0], line_num);
                break;
            }
        }
        else {
            inst.dest_is_memory = 0;  // Mark destination as register
            strcpy(inst.dest_reg_name, operands[0]); // Store original register name
        }
    }
    else {
        fprintf(stderr, "Error: Missing destination operand for 'POW' at line %zu\n", line_num);
        break;
    }

    // Assign the exponent operand (this will be the second operand)
    if (operand_count >= 2) {
        uint64_t* src_ptr = get_register_pointer(emu, operands[1]);
        if (src_ptr) {
            // If it's a register
            inst.src_reg = src_ptr;
            inst.src_is_memory = 0;  // Source is a register
            strcpy(inst.src_reg_name, operands[1]); // Store original register name
        }
        else if (strchr(operands[1], '[') != NULL && strchr(operands[1], ']') != NULL) {
            // Handle memory operand (e.g., "[0x100]")
            char addr_str[20];  // Buffer to hold the address part
            char* start = strchr(operands[1], '[') + 1;  // Start after '['
            char* end = strchr(operands[1], ']');       // Find the closing ']'
            if (end <= start) {
                fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operands[1], line_num);
                break;
            }
            strncpy(addr_str, start, end - start);  // Copy the address part
            addr_str[end - start] = '\0';           // Null-terminate the address string
            inst.src_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
            inst.src_is_memory = 1;  // Source is memory
        }
        else {
            // Assume immediate value
            if (strncmp(operands[1], "0x", 2) == 0 || strncmp(operands[1], "0X", 2) == 0) {
                inst.immediate = strtoull(operands[1], NULL, 16);  // Hexadecimal
            }
            else {
                inst.immediate = strtoull(operands[1], NULL, 10);  // Decimal
            }
            inst.src_is_memory = 0;  // Source is immediate, not memory
        }
    }
    else {
        fprintf(stderr, "Error: Missing exponent operand for 'POW' at line %zu\n", line_num);
        break;
    }
}
break;

case INST_ROOT:
{
    // Expect three operands: dest, src, aux
    char* operands[3] = { NULL, NULL, NULL };
    int operand_count = 0;
    // Collect up to three operands
    while ((token = strtok(NULL, " \t,")) != NULL && operand_count < 3) {
        operands[operand_count++] = token;
    }

    // Validate operand count
    if (operand_count != 3) {
        fprintf(stderr, "Error: 'ROOT' requires exactly three operands at line %zu\n", line_num);
        break;
    }

    // Destination operand handling
    inst.dest_reg = get_register_pointer(emu, operands[0]);
    if (!inst.dest_reg) {
        // Check if it's a memory address
        if (operands[0][0] == '[' && operands[0][strlen(operands[0]) - 1] == ']') {
            char addr_str[32];
            strncpy(addr_str, operands[0] + 1, strlen(operands[0]) - 2);
            addr_str[strlen(operands[0]) - 2] = '\0';
            inst.dest_mem_address = strtoull(addr_str, NULL, 0);
            inst.dest_is_memory = 1;

            // Clear register name for memory address
            memset(inst.dest_reg_name, 0, sizeof(inst.dest_reg_name));
        }
        else {
            fprintf(stderr, "Error: Invalid destination operand '%s' at line %zu\n", operands[0], line_num);
            break;
        }
    }
    else {
        // Store original register name for registers
        strcpy(inst.dest_reg_name, operands[0]);
    }

    // Source (base) operand handling
    inst.src_reg = get_register_pointer(emu, operands[1]);
    if (!inst.src_reg) {
        // Check if it's a memory address
        if (operands[1][0] == '[' && operands[1][strlen(operands[1]) - 1] == ']') {
            char addr_str[32];
            strncpy(addr_str, operands[1] + 1, strlen(operands[1]) - 2);
            addr_str[strlen(operands[1]) - 2] = '\0';
            inst.src_mem_address = strtoull(addr_str, NULL, 0);
            inst.src_is_memory = 1;

            // Clear register name for memory address
            memset(inst.src_reg_name, 0, sizeof(inst.src_reg_name));
        }
        else {
            // Try parsing as immediate
            char* endptr;
            inst.immediate = strtoull(operands[1], &endptr, 0);
            if (*endptr != '\0') {
                fprintf(stderr, "Error: Invalid base operand '%s' at line %zu\n", operands[1], line_num);
                break;
            }

            // Clear register name for immediate value
            memset(inst.src_reg_name, 0, sizeof(inst.src_reg_name));
        }
    }
    else {
        // Store original register name for registers
        strcpy(inst.src_reg_name, operands[1]);
    }

    // Auxiliary (exponent) operand handling
    inst.aux_reg = get_register_pointer(emu, operands[2]);
    if (!inst.aux_reg) {
        // Check if it's a memory address
        if (operands[2][0] == '[' && operands[2][strlen(operands[2]) - 1] == ']') {
            char addr_str[32];
            strncpy(addr_str, operands[2] + 1, strlen(operands[2]) - 2);
            addr_str[strlen(operands[2]) - 2] = '\0';
            inst.aux_mem_address = strtoull(addr_str, NULL, 0);
            inst.aux_is_memory = 1;

            // Clear register name for memory address
            memset(inst.aux_reg_name, 0, sizeof(inst.aux_reg_name));
        }
        else {
            // Try parsing as immediate
            char* endptr;
            inst.aux_immediate = strtoull(operands[2], &endptr, 0);
            if (*endptr != '\0') {
                fprintf(stderr, "Error: Invalid exponent operand '%s' at line %zu\n", operands[2], line_num);
                break;
            }

            // Clear register name for immediate value
            memset(inst.aux_reg_name, 0, sizeof(inst.aux_reg_name));
        }
    }
    else {
        // Store original register name for registers
        strcpy(inst.aux_reg_name, operands[2]);
    }
}
break;


case INST_AVG:
{
    // Expect three operands: dest, src, aux
    char* operands[3] = { NULL, NULL, NULL };
    int operand_count = 0;
    // Collect up to three operands
    while ((token = strtok(NULL, " \t,")) != NULL && operand_count < 3) {
        operands[operand_count++] = token;
    }

    // Validate operand count
    if (operand_count != 3) {
        fprintf(stderr, "Error: 'AVG' requires exactly three operands at line %zu\n", line_num);
        break;
    }

    // Destination operand handling
    inst.dest_reg = get_register_pointer(emu, operands[0]);
    if (!inst.dest_reg) {
        fprintf(stderr, "Error: Invalid destination register '%s' at line %zu\n", operands[0], line_num);
        break;
    }
    strcpy(inst.dest_reg_name, operands[0]); // Store original register name

    // Source operand handling
    inst.src_reg = get_register_pointer(emu, operands[1]);
    if (inst.src_reg) {
        // It's a register
        inst.src_is_memory = 0;
        inst.src_immediate = 0;
        strcpy(inst.src_reg_name, operands[1]);
    }
    else if (operands[1][0] == '[' && operands[1][strlen(operands[1]) - 1] == ']') {
        // It's a memory reference
        char addr_str[32];
        strncpy(addr_str, operands[1] + 1, strlen(operands[1]) - 2);
        addr_str[strlen(operands[1]) - 2] = '\0';
        inst.src_mem_address = strtoull(addr_str, NULL, 0);
        inst.src_is_memory = 1;
        inst.src_immediate = 0;
        memset(inst.src_reg_name, 0, sizeof(inst.src_reg_name));
    }
    else {
        // Try parsing as immediate
        char* endptr;
        inst.immediate = strtoull(operands[1], &endptr, 0);
        if (*endptr != '\0') {
            fprintf(stderr, "Error: Invalid source operand '%s' at line %zu\n", operands[1], line_num);
            break;
        }
        inst.src_immediate = 1;
        inst.src_is_memory = 0;
        memset(inst.src_reg_name, 0, sizeof(inst.src_reg_name));
    }

    // Auxiliary operand handling
    inst.aux_reg = get_register_pointer(emu, operands[2]);
    if (inst.aux_reg) {
        // It's a register
        inst.aux_is_memory = 0;
        inst.aux_immediate = 0;
        strcpy(inst.aux_reg_name, operands[2]);
    }
    else if (operands[2][0] == '[' && operands[2][strlen(operands[2]) - 1] == ']') {
        // It's a memory reference
        char addr_str[32];
        strncpy(addr_str, operands[2] + 1, strlen(operands[2]) - 2);
        addr_str[strlen(operands[2]) - 2] = '\0';
        inst.aux_mem_address = strtoull(addr_str, NULL, 0);
        inst.aux_is_memory = 1;
        inst.aux_immediate = 0;
        memset(inst.aux_reg_name, 0, sizeof(inst.aux_reg_name));
    }
    else {
        // Try parsing as immediate
        char* endptr;
        inst.aux_immediate = strtoull(operands[2], &endptr, 0);
        if (*endptr != '\0') {
            fprintf(stderr, "Error: Invalid auxiliary operand '%s' at line %zu\n", operands[2], line_num);
            break;
        }
        inst.aux_immediate = 1;
        inst.aux_is_memory = 0;
        memset(inst.aux_reg_name, 0, sizeof(inst.aux_reg_name));
    }
}
break;

case INST_MIN:
case INST_MAX:
{
    // Expect three operands: dest, src, aux
    char* operands[3] = { NULL, NULL, NULL };
    int operand_count = 0;

    // Collect up to three operands
    while ((token = strtok(NULL, " \t,")) != NULL && operand_count < 3) {
        operands[operand_count++] = token;
    }

    // Check if exactly three operands are provided
    if (operand_count != 3) {
        fprintf(stderr, "Error: %s instruction requires exactly three operands at line %zu\n",
            (type == INST_MIN ? "MIN" : "MAX"), line_num);
        break;
    }

    // First operand must be a register (destination)
    inst.dest_reg = get_register_pointer(emu, operands[0]);
    if (!inst.dest_reg) {
        fprintf(stderr, "Error: First operand must be a register at line %zu\n", line_num);
        break;
    }
    strcpy(inst.dest_reg_name, operands[0]); // Store original register name

    // Parse second operand (src): register, memory, or immediate
    if ((inst.src_reg = get_register_pointer(emu, operands[1]))) {
        inst.src_is_memory = 0; // Source is a register
        inst.src_immediate = 0;
        strcpy(inst.src_reg_name, operands[1]); // Store original register name
    }
    else if (operands[1][0] == '[') {
        // Handle memory operand (e.g., "[0x100]")
        char* end_bracket = strchr(operands[1], ']');
        if (!end_bracket) {
            fprintf(stderr, "Error: Invalid memory syntax at line %zu\n", line_num);
            break;
        }
        *end_bracket = '\0'; // Null-terminate the address string
        inst.src_mem_address = strtoull(operands[1] + 1, NULL, 0); // Parse memory address
        inst.src_is_memory = 1; // Source is memory
        inst.src_immediate = 0;
    }
    else {
        // Handle immediate value
        char* endptr;
        inst.immediate = strtoull(operands[1], &endptr, 0); // Parse immediate value
        if (*endptr != '\0') {
            fprintf(stderr, "Error: Invalid second operand at line %zu\n", line_num);
            break;
        }
        inst.src_immediate = 1; // Source is immediate
        inst.src_is_memory = 0;
    }

    // Parse third operand (aux): register, memory, or immediate
    if ((inst.aux_reg = get_register_pointer(emu, operands[2]))) {
        inst.aux_is_memory = 0; // Auxiliary is a register
        inst.aux_immediate = 0;
        strcpy(inst.aux_reg_name, operands[2]); // Store original register name
    }
    else if (operands[2][0] == '[') {
        // Handle memory operand (e.g., "[0x100]")
        char* end_bracket = strchr(operands[2], ']');
        if (!end_bracket) {
            fprintf(stderr, "Error: Invalid memory syntax at line %zu\n", line_num);
            break;
        }
        *end_bracket = '\0'; // Null-terminate the address string
        inst.aux_mem_address = strtoull(operands[2] + 1, NULL, 0); // Parse memory address
        inst.aux_is_memory = 1; // Auxiliary is memory
        inst.aux_immediate = 0;
    }
    else {
        // Handle immediate value
        char* endptr;
        inst.aux_immediate = strtoull(operands[2], &endptr, 0); // Parse immediate value
        if (*endptr != '\0') {
            fprintf(stderr, "Error: Invalid third operand at line %zu\n", line_num);
            break;
        }
        inst.aux_immediate = 1; // Auxiliary is immediate
        inst.aux_is_memory = 0;
    }
}
break;

case INST_MIRROR:
case INST_ISPRIME:
{
    // Expect two operands: dest, src
    char* operands[2] = { NULL, NULL };
    int operand_count = 0;

    // Collect up to two operands
    while ((token = strtok(NULL, " \t,")) != NULL && operand_count < 2) {
        operands[operand_count++] = token;
    }

    // Assign the destination operand (first operand)
    if (operand_count >= 1) {
        inst.dest_reg = get_register_pointer(emu, operands[0]);
        if (!inst.dest_reg) {
            // Check if it's a memory address (e.g., "[0x100]")
            if (strchr(operands[0], '[') != NULL && strchr(operands[0], ']') != NULL) {
                // Extract memory address (remove "[" and "]")
                char addr_str[20];  // Buffer to hold the address part
                char* start = strchr(operands[0], '[') + 1;  // Start after '['
                char* end = strchr(operands[0], ']');       // Find the closing ']'
                if (end <= start) {
                    fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operands[0], line_num);
                    break;
                }
                strncpy(addr_str, start, end - start);  // Copy the address part
                addr_str[end - start] = '\0';           // Null-terminate the address string
                inst.dest_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
                inst.dest_is_memory = 1;  // Mark destination as memory
            }
            else {
                fprintf(stderr, "Error: Invalid destination operand '%s' at line %zu\n", operands[0], line_num);
                break;
            }
        }
        else {
            inst.dest_is_memory = 0;  // Mark destination as register
            strcpy(inst.dest_reg_name, operands[0]); // Store original register name
        }
    }
    else {
        fprintf(stderr, "Error: Missing destination operand for '%s' at line %zu\n", (type == INST_MIRROR ? "MIRROR" : "ISPRIME"), line_num);
        break;
    }

    // Assign the source operand (second operand)
    if (operand_count >= 2) {
        if (strncmp(operands[1], "0x", 2) == 0 || strncmp(operands[1], "0X", 2) == 0) {
            // Handle immediate value (hexadecimal)
            inst.immediate = strtoull(operands[1], NULL, 16);
            inst.src_is_memory = 0;  // Source is an immediate
        }
        else {
            uint64_t* src_ptr = get_register_pointer(emu, operands[1]);
            if (src_ptr) {
                // Handle register source
                inst.src_reg = src_ptr;
                inst.src_is_memory = 0;  // Source is a register
                strcpy(inst.src_reg_name, operands[1]); // Store original register name
            }
            else if (strchr(operands[1], '[') != NULL && strchr(operands[1], ']') != NULL) {
                // Handle memory operand (e.g., "[0x100]")
                char addr_str[20];  // Buffer to hold the address part
                char* start = strchr(operands[1], '[') + 1;  // Start after '['
                char* end = strchr(operands[1], ']');       // Find the closing ']'
                if (end <= start) {
                    fprintf(stderr, "Error: Invalid memory address format '%s' at line %zu\n", operands[1], line_num);
                    break;
                }
                strncpy(addr_str, start, end - start);  // Copy the address part
                addr_str[end - start] = '\0';           // Null-terminate the address string
                inst.src_mem_address = strtoull(addr_str, NULL, 0);  // Use base 0 for automatic base detection
                inst.src_is_memory = 1;  // Source is memory
            }
            else {
                // Handle immediate value (decimal)
                inst.immediate = strtoull(operands[1], NULL, 10);
                inst.src_is_memory = 0;  // Source is an immediate
            }
        }
    }
    else {
        fprintf(stderr, "Error: Missing source operand for '%s' at line %zu\n", (type == INST_MIRROR ? "MIRROR" : "ISPRIME"), line_num);
        break;
    }

    // Perform the MIRROR or ISPRIME operation
    if (type == INST_MIRROR) {
        // Perform the MIRROR operation
        uint64_t src_value = 0;
        if (inst.src_reg) {
            src_value = *inst.src_reg;
        }
        else if (inst.src_is_memory) {
            // Read from memory if source is memory
            src_value = emu->memory[inst.src_mem_address];
        }
        else {
            src_value = inst.immediate;
        }

        // Reverse the bits of the value
        uint64_t mirrored_value = 0;
        for (int i = 0; i < 64; i++) {
            mirrored_value |= ((src_value >> i) & 1) << (63 - i);  // Reverse bit by bit
        }

        // Store the mirrored value
        if (inst.dest_reg) {
            *inst.dest_reg = mirrored_value;
        }
        else if (inst.dest_is_memory) {
            // Write to memory if destination is memory
            emu->memory[inst.dest_mem_address] = mirrored_value;
        }

        printf("Executed MIRROR Instruction: Mirror of 0x%llX = 0x%llX\n", src_value, mirrored_value);
    }
    else if (type == INST_ISPRIME) {
        // Perform the ISPRIME operation
        execute_isprime_instruction(emu, &inst);
    }
}
break;

        case INST_JMP:
        case INST_JE:
        case INST_JNE:
        case INST_JG:
        case INST_JL:
        case INST_JGE:
        case INST_JLE:
        case INST_JA:
        case INST_JAE:
        case INST_JB:
        case INST_JBE:
        case INST_JO:
        case INST_JNO:
        case INST_JS:
        case INST_JNS:
        case INST_JP:
        case INST_JNP:
        {
            // Expect one operand: label
            char* operand = strtok(NULL, " \t,");
            if (operand) {
                strcpy(inst.label, operand);
            }
            else {
                fprintf(stderr, "Error: Missing label operand for '%s' at line %zu\n",
                    (type == INST_JMP ? "JMP" :
                        type == INST_JE ? "JE" :
                        type == INST_JNE ? "JNE" :
                        type == INST_JG ? "JG" :
                        type == INST_JL ? "JL" :
                        type == INST_JGE ? "JGE" :
                        type == INST_JLE ? "JLE" :
                        type == INST_JA ? "JA" :
                        type == INST_JAE ? "JAE" :
                        type == INST_JB ? "JB" :
                        type == INST_JBE ? "JBE" :
                        type == INST_JO ? "JO" :
                        type == INST_JNO ? "JNO" :
                        type == INST_JS ? "JS" :
                        type == INST_JNS ? "JNS" :
                        type == INST_JP ? "JP" :
                        type == INST_JNP ? "JNP" : "UNKNOWN"), line_num);
                break;
            }
        }
        break;

        case INST_LABEL:
            // Labels are handled in the first pass; no action needed here
            break;

        case INST_NOP:
            // No operands
            break;

        case INST_COMMENT:
            // Comments are ignored in execution
            break;

        default:
            fprintf(stderr, "Error: Unsupported instruction '%s' at line %zu\n", token, line_num);
            break;
        }

        // Add instruction to the list if it's not a label or comment
        if (type != INST_LABEL && type != INST_COMMENT) {
            if (instruction_count >= instruction_capacity) {
                resize_instructions(&instructions, &instruction_capacity);
            }
            instructions[instruction_count++] = inst;
        }
    }

    fclose(file);

    // Second pass: execute instructions using rip
    emu->rip = 0;
    while (emu->rip < instruction_count) {
        Instruction* current_inst = &instructions[emu->rip];
        execute_instruction(emu, current_inst, emu->rip, labels, label_count);

        // Handle jump instructions by updating rip accordingly
        bool should_jump = false;

        if (current_inst->type == INST_JMP) {
            should_jump = true;  // Unconditional jump
        }
        else if (current_inst->type == INST_JE && emu->flags.zero) {
            should_jump = true;  // Jump if Zero Flag (ZF) is set
        }
        else if (current_inst->type == INST_JNE && !emu->flags.zero) {
            should_jump = true;  // Jump if Zero Flag (ZF) is NOT set
        }
        else if (current_inst->type == INST_JG && !emu->flags.sign && !emu->flags.zero) {
            should_jump = true;  // Jump if Greater (ZF is clear and SF is clear)
        }
        else if (current_inst->type == INST_JGE && !emu->flags.sign) {
            should_jump = true;  // Jump if Greater or Equal (SF is clear)
        }
        else if (current_inst->type == INST_JL && emu->flags.sign != emu->flags.overflow) {
            should_jump = true;  // Jump if Less (SF != OF)
        }
        else if (current_inst->type == INST_JLE && (emu->flags.sign != emu->flags.overflow || emu->flags.zero)) {
            should_jump = true;  // Jump if Less or Equal (SF != OF or ZF is set)
        }
        else if (current_inst->type == INST_JA && !emu->flags.carry && !emu->flags.zero) {
            should_jump = true;  // Jump if Above (CF and ZF are clear)
        }
        else if (current_inst->type == INST_JAE && !emu->flags.carry) {
            should_jump = true;  // Jump if Above or Equal (CF is clear)
        }
        else if (current_inst->type == INST_JB && emu->flags.carry) {
            should_jump = true;  // Jump if Below (CF is set)
        }
        else if (current_inst->type == INST_JBE && (emu->flags.carry || emu->flags.zero)) {
            should_jump = true;  // Jump if Below or Equal (CF is set or ZF is set)
        }
        else if (current_inst->type == INST_JS && emu->flags.sign) {
            should_jump = true;  // Jump if Signed (SF is set)
        }
        else if (current_inst->type == INST_JNS && !emu->flags.sign) {
            should_jump = true;  // Jump if Not Signed (SF is clear)
        }
        else if (current_inst->type == INST_JP && emu->flags.overflow) {
            should_jump = true;  // Jump if Parity (OF is set)
        }
        else if (current_inst->type == INST_JNP && !emu->flags.overflow) {
            should_jump = true;  // Jump if Not Parity (OF is clear)
        }
        if (should_jump) {
            // Find the label
            size_t target_index = 0;
            bool found = false;

            for (size_t i = 0; i < label_count; i++) {
                if (strcmp(current_inst->label, labels[i].label) == 0) {
                    target_index = labels[i].index;
                    found = true;
                    break;
                }
            }

            if (found) {
                emu->rip = target_index;  // Jump to the target index (label)
                continue;  // Skip the normal increment of rip and jump
            }
            else {
                fprintf(stderr, "Error: Label '%s' not found for jump instruction at rip=%zu\n", current_inst->label, emu->rip);
                break;  // Exit if label is not found
            }
        }

        // Increment rip only if no jump instruction is executed
        emu->rip++;  // Increment rip after executing non-jump instructions or if no jump condition met
    }
    free(instructions);
    free(labels);
}

// Advanced memory operation demonstration
void demonstrate_memory_operations(Emulator* emu) {
    // Write to memory
    uint64_t value = 0xDEADBEEFCAFEBABE;
    memcpy(emu->memory, &value, sizeof(value));
    printf("Memory Operation: Written 0x%016" PRIx64 " to memory address 0x0\n", value);

    // Simulate stack operations
    Instruction stack_instructions[] = {
        {INST_PUSH, "", &emu->rax, NULL, NULL, 0, HEX},  // Push RAX to stack (Hex)
        {INST_POP, "", &emu->rbx, NULL, NULL, 0, HEX}    // Pop top of stack to RBX (Hex)
    };

    size_t stack_instruction_count = sizeof(stack_instructions) / sizeof(Instruction);
    for (size_t i = 0; i < stack_instruction_count; i++) {
        execute_instruction(emu, &stack_instructions[i], i + 1, NULL, 0);
    }
}

void run_comprehensive_example(Emulator* emu) {
    // Function implementation
    // Example:
    // Define labels for jumps
    Label labels[10];
    size_t label_count = 0;

    // Initialize labels (if any)
    // For this example, we'll manually add labels and map them
    // In a real scenario, labels would be part of the instruction list

    // Define a list of instructions
    Instruction instructions[] = {
        // Data Movement
        {INST_MOV, "", &emu->rax, NULL, NULL, 0xA, HEX},          // rax = 0xA (10 in hex)
        {INST_MOV, "", &emu->rbx, NULL, NULL, 0x5, HEX},          // rbx = 0x5
        {INST_MOV, "", &emu->rcx, NULL, NULL, 0x3, HEX},          // rcx = 0x3

        // Arithmetic
        {INST_ADD, "", &emu->rax, &emu->rbx, NULL, 0, HEX},       // rax = rax + rbx
        {INST_SUB, "", &emu->rax, NULL, NULL, 0x2, HEX},          // rax = rax - 0x2

        // Continuing the example program
        {INST_MUL, "", &emu->rax, &emu->rcx, NULL, 0, HEX},       // rax = rax * rcx

        // Custom Instructions

        // MIRROR Instruction
        {INST_MIRROR, "", &emu->rdx, &emu->rax, NULL, 0, HEX},    // rdx = mirror of rax

        // MOD Instruction
        {INST_MOD, "", &emu->rax, NULL, NULL, 0x4, HEX},          // rax = rax % 0x4

        // POW Instruction
        {INST_POW, "", &emu->rax, NULL, NULL, 0x2, HEX},          // rax = rax ^ 0x2

        // ROOT instruction (cube root of rax)
        {INST_ROOT, "", &emu->rdx, &emu->rax, &emu->rcx, 0, HEX}, // rdx = cube root of rax

        // AVG instruction
        {INST_AVG, "", &emu->rcx, &emu->rax, &emu->rbx, 0, HEX},  // rcx = average of rax, rbx, rcx

        // MAX instruction
        {INST_MAX, "", &emu->rcx, &emu->rax, &emu->rbx, 0, HEX},  // rcx = max of rax, rbx, rcx

        // MIN instruction
        {INST_MIN, "", &emu->rcx, &emu->rax, &emu->rbx, 0, HEX},  // rcx = min of rax, rbx, rcx

        // ISPRIME Instruction
        {INST_ISPRIME, "", &emu->rdi, &emu->rax, NULL, 0, HEX},  // rdi = 0 as rax = 0xA (10 in hex)

        // Logical Operations
        {INST_AND, "", &emu->rax, &emu->rbx, NULL, 0, HEX},      // Bitwise AND

        // Comparison and Conditional Jump
        {INST_CMP, "", &emu->rbx, &emu->rcx, NULL, 0, HEX},      // Compare rbx and rcx
        {INST_JE, "END", NULL, NULL, NULL, 0, HEX},               // Jump to END if equal
        {INST_ADD, "", &emu->rcx, &emu->rbx, NULL, 0, HEX},       // rcx = rcx + rbx
        {INST_LABEL, "END", NULL, NULL, NULL, 0, HEX},            // Label: END
        {INST_NOP, "", NULL, NULL, NULL, 0, HEX}                  // NOP
    };

    size_t instruction_count = sizeof(instructions) / sizeof(Instruction);

    // Add labels to the label list
    Label label_list[10];
    size_t label_list_count = 0;
    for (size_t i = 0; i < instruction_count; i++) {
        if (instructions[i].type == INST_LABEL) {
            strcpy(label_list[label_list_count].label, instructions[i].label);
            label_list[label_list_count].index = i;
            label_list_count++;
        }
    }

    // Execute instructions using rip
    emu->rip = 0;
    while (emu->rip < instruction_count) {
        Instruction* current_inst = &instructions[emu->rip];
        execute_instruction(emu, current_inst, emu->rip, label_list, label_list_count);

        // Handle jump instructions by updating rip accordingly
        if (current_inst->type == INST_JMP ||
            current_inst->type == INST_JE ||
            current_inst->type == INST_JNE ||
            current_inst->type == INST_JG ||
            current_inst->type == INST_JL ||
            current_inst->type == INST_JGE ||
            current_inst->type == INST_JLE ||
            current_inst->type == INST_JA ||
            current_inst->type == INST_JAE ||
            current_inst->type == INST_JB ||
            current_inst->type == INST_JBE ||
            current_inst->type == INST_JO ||
            current_inst->type == INST_JNO ||
            current_inst->type == INST_JS ||
            current_inst->type == INST_JNS ||
            current_inst->type == INST_JP ||
            current_inst->type == INST_JNP) {
            // Find the label
            size_t target_index = 0;
            bool found = false;
            for (size_t i = 0; i < label_list_count; i++) {
                if (strcmp(current_inst->label, label_list[i].label) == 0) {
                    target_index = label_list[i].index;
                    found = true;
                    break;
                }
            }
            if (found) {
                emu->rip = target_index;
                continue; // Skip the rip increment
            }
            else {
                fprintf(stderr, "Error: Label '%s' not found for jump instruction at rip=%zu\n", current_inst->label, emu->rip);
                break;
            }
        }

        emu->rip++; // Move to the next instruction
    }

    // Note: Final emulator state will be printed by main function based on mode
}

// Main function to demonstrate emulator capabilities
int main(int argc, char* argv[]) {

    // Create emulator with 1MB memory and 64KB stack
    Emulator* emu = create_emulator(100000*100000, 10000 * 10000);

    // Prepare The INTs
    initialize_interrupt_handlers();

    // User interaction for tracing and file input
    char mode;
    char filename[256] = "";

    printf("Choose mode:\n");
    printf("T - Trace execution (show states before and after each instruction)\n");
    printf("R - Run without tracing\n");
    printf("Enter mode (T/R): ");

    // Check return value of scanf
    if (scanf(" %c", &mode) != 1) {
        fprintf(stderr, "Error: Failed to read mode. Defaulting to Run without tracing.\n");
        tracing_enabled = false;
    }
    else {
        if (mode == 'T' || mode == 't') {
            tracing_enabled = true;
        }
        else if (mode == 'R' || mode == 'r') {
            tracing_enabled = false;
        }
        else {
            fprintf(stderr, "Invalid mode selected. Defaulting to Run without tracing.\n");
            tracing_enabled = false;
        }
    }

    // Clear input buffer to handle next input correctly
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Check for filename argument
    if (argc >= 2) {
        strncpy(filename, argv[1], sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
    }
    else {
        printf("Enter the path to the .asm file (or press Enter to skip): ");
        if (fgets(filename, sizeof(filename), stdin) != NULL) {
            // Remove newline character
            filename[strcspn(filename, "\r\n")] = 0;
        }
    }

    // Prevent executing the emulator executable as an instruction file
    if (strlen(filename) > 0) {
        // Get the executable's filename
        const char* exec_name = argv[0];
        // Extract the basename
        const char* base_exec = strrchr(exec_name, '\\');
        if (!base_exec) base_exec = strrchr(exec_name, '/');
        if (base_exec) base_exec++; else base_exec = exec_name;

        // Extract the basename from the user-provided filename
        const char* user_base = strrchr(filename, '\\');
        if (!user_base) user_base = strrchr(filename, '/');
        if (user_base) user_base++; else user_base = filename;

        // Compare case-insensitively
        if (strcasecmp(base_exec, user_base) == 0) {
            fprintf(stderr, "Error: The instruction file cannot be the emulator executable.\n");
            destroy_emulator(emu);
            exit(1);
        }
    }

    if (strlen(filename) > 0) {
        printf("\n=== Executing Instructions from File: %s ===\n", filename);
        execute_file_instructions(emu, filename);
    }
    else {
        printf("\n=== Running Comprehensive Emulator Example ===\n");
        run_comprehensive_example(emu);
    }

    // Demonstrate memory and stack operations
    // Uncomment the following line to demonstrate memory operations
    // demonstrate_memory_operations(emu);

    // If not tracing, print the final state
    if (!tracing_enabled) {
        printf("\n=== Final Emulator State ===\n");
        print_emulator_state(emu, "Final State");
    }

    // Clean up
    destroy_emulator(emu);
#endif
    return 0;

}
