#include "Instruction_list.h"
Instruction_list::Instruction_list()
{
    this->first_instruction = nullptr;
    this->current_instruction = nullptr;
    this->last_instruction = nullptr;
}
Instruction_list::Instruction_list(Instruction_node first_instruction)
{
    this->append(first_instruction);
}
Instruction_list::Instruction_list(const Instruction_list &target_list)
{
    this->copy(target_list);
}
void Instruction_list::operator=(const Instruction_list &target_list)
{
    this->copy(target_list);
}
Instruction_list::~Instruction_list()
{
    this->clear_list();
}
void Instruction_list::clear_list()
{
    Instruction_node *aux_pointer;
    aux_pointer = this->first_instruction;
    while (aux_pointer != nullptr)
    {
        this->first_instruction = this->first_instruction->get_next();
        delete aux_pointer;
        aux_pointer = this->first_instruction;
    }
}
void Instruction_list::reset()
{
    this->current_instruction = this->first_instruction;
}
Instruction_node *Instruction_list::get_current_instruction()
{
    return this->current_instruction;
}
Instruction_node *Instruction_list::next_instruction()
{
    this->current_instruction = this->current_instruction->get_next();
    return this->current_instruction;
}
void Instruction_list::append(const Instruction_node last_instruction)
{
    if (this->first_instruction == nullptr)
    {
        this->last_instruction = new Instruction_node;
        *this->last_instruction = last_instruction;
        this->first_instruction = this->last_instruction;
        this->current_instruction = this->last_instruction;
    }
    else
    {
        this->last_instruction->link_next(new Instruction_node);
        *this->last_instruction->get_next() = last_instruction;
        this->last_instruction = this->last_instruction->get_next();
    }
}
void Instruction_list::copy(const Instruction_list &target_list)
{ // RESETEA CURRENT_POINTER
    this->clear_list();
    Instruction_node *aux_pointer_target = target_list.first_instruction;
    while (aux_pointer_target != nullptr)
    {

        this->append(*aux_pointer_target);
        aux_pointer_target = aux_pointer_target->get_next();
    }
    this->reset();
}
void Instruction_list::print()
{
    Instruction_node *aux_pointer = this->first_instruction;
    while (aux_pointer != nullptr)
    {
        aux_pointer = aux_pointer->get_next();
    }
}
// Instruction_node Instruction_list::next_instruction();