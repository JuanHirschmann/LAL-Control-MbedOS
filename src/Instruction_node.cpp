#include "Instruction_node.h"
Instruction_node::Instruction_node()
{
    this->instruction_text = nullptr;
    this->instruction_length = 0;
}
Instruction_node::Instruction_node(char *new_text, int text_length)
{

    this->instruction_text = new char *;
    char *aux_string = new char[text_length];
    strncpy(aux_string, new_text, text_length);
    *this->instruction_text = aux_string;
    this->instruction_length = text_length;
}
Instruction_node::Instruction_node(Instruction_node &target_node)
{
    this->copy(target_node);
}
void Instruction_node::operator=(const Instruction_node &target_node)
{

    this->copy(target_node);
}
void Instruction_node::copy(const Instruction_node &target_node)
{
    if (this->instruction_length != 0)
    {
        this->clear_node();
    }
    this->instruction_text = new char *;
    char *aux_string = new char[target_node.instruction_length];
    strncpy(aux_string, *(target_node.instruction_text), target_node.instruction_length);
    *this->instruction_text = aux_string;
    this->instruction_length = target_node.instruction_length;
}
Instruction_node::~Instruction_node()
{
    if (this->instruction_length != 0)
    {
        this->clear_node();
    }
}
void Instruction_node::clear_node()
{
    delete[] * this->instruction_text;
    delete this->instruction_text;
    this->instruction_length = 0;
}
void Instruction_node::set_text(const char *new_text, int text_length)
{
    if (this->instruction_length != 0)
    {
        this->clear_node();
    }
    this->instruction_text = new char *;
    char *aux_string = new char[text_length];
    strncpy(aux_string, new_text, text_length);
    *this->instruction_text = aux_string;
    this->instruction_length = text_length;
}
void Instruction_node::link_next(Instruction_node *next_step)
{
    this->next = next_step;
}
Instruction_node *Instruction_node::get_next()
{
    return this->next;
}
char *Instruction_node::get_text()
{
    return *this->instruction_text;
}