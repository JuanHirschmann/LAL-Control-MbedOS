#include "main.h"
PC_serial_interface pc_com(USBTX, USBRX, 115200);
int main()
{
  char buffer[100];
  while (1)
  {
    pc_com.read(buffer, 100);
    pc_com.print(buffer);
  }
}