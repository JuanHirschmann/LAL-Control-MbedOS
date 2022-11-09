#include "main.h"
PC_serial_interface pc_com(USBTX, USBRX, 115200);
int main()
{
  while (1)
  {
    pc_com.print("HOLA");
  }
}