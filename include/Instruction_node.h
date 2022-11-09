#ifndef INSTRUCTION_NODE_H
#define INSTRUCTION_NODE_H
#include "stdio.h"
#include <string.h>
class Instruction_node
{
public:
    Instruction_node();
    Instruction_node(char *new_text, int text_length);
    Instruction_node(Instruction_node &target_node);
    ~Instruction_node();
    void operator=(const Instruction_node &target_node);
    Instruction_node *get_next();
    char *get_text();
    void link_next(Instruction_node *next_step);
    void set_text(const char *new_text, int text_length);

private:
    char **instruction_text = nullptr;
    Instruction_node *next = nullptr;
    void clear_node();
    int instruction_length = 0;
    void copy(const Instruction_node &target_node);
};
#endif