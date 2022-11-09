#ifndef INSTRUCTION_LIST_H
#define INSTRUCTION_LIST_H
#include "stdio.h"
#include "Instruction_node.h"
#include <string.h>
class Instruction_list
{
public:
    Instruction_list();
    Instruction_list(Instruction_node first_instruction);
    Instruction_list(const Instruction_list &target_list);
    void operator=(const Instruction_list &target_list);
    ~Instruction_list();
    void append(const Instruction_node last_instruction);
    Instruction_node *next_instruction();
    Instruction_node *get_current_instruction();
    void reset();
    void print();

private:
    Instruction_node *first_instruction = nullptr;
    Instruction_node *current_instruction = nullptr;
    Instruction_node *last_instruction = nullptr;
    void clear_list();
    void copy(const Instruction_list &target_list);
};
#endif