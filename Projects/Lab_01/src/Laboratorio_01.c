//Universidade Tecnológica Federal do Paraná
//Sistemas Embracados
//AUTOR: Matheus Victor Barbato - 1862308
//Data de criação: 24/06/2021
//Ultima modificação: 24/06/2021
//Laboratório 01

#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void main(void){
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilitação
    
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0); // LEDs D4 como saída
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0); // LEDs D4 apagados
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  bool status = 0;
  uint32_t count = 0;
  while(1){
    
    /*
    *   É afetado ao otimizar o código, quanto maior a otimização, mais rápido
    *   o led pisca
    */
    
    do{
      count++;
    }while(count != 2400000);
    count = 0;
    
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, status);
    status = !status;
    
    //while(count != 2400000){
    //  count++;
    //}
    //count = 0;
    
    /*
    *   Frequência de 24Mhz:
    *   T = 1/24MHz = 41,67ns
    *   41,67 * 3 instruções = 125 ns
    *   125 ns * 8*10^6 = 1 s 
    *   Não é afetado ao otimizar o código
    */
    //SysCtlDelay(8000000);
    
  } // while
} // main