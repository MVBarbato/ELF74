//Universidade Tecnológica Federal do Paraná
//Sistemas Embracados
//AUTOR: Matheus Victor Barbato - 1862308
//Data de criação: 24/06/2021
//Ultima modificação: 24/06/2021
//Laboratório 01

//1. Diferentes níveis de otimização do compilador C
//2. Frequência de clock (PLL) de 120MHz
//Há variações na temporização por software para os casos acima? Quantifique-as.
//R:

//Os seguintes trechos de código são equivalentes:
//– GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
//– GPIOPinWrite (0x40025000, 0x00000010, 0x00000010);
//Qual dos trechos de código acima é mais legível e fácil de se compreender?
//R: GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);

//Os seguintes trechos de código são equivalentes:
//– GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
//– GPIOPinTypeGPIOOutput (0x40025000, 0x00000011);
//Qual dos trechos de código acima é mais legível e fácil de se compreender?
//Obs : GPIO_PIN_0=0x01; GPIO_PIN_4=0x10
//R: GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void main(void){
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);          // Habilita GPIO F (LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));   // Aguarda final da habilitação
    
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);   // LEDs D4 como saída
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);         // LEDs D4 apagados
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  bool status = 0;
  uint32_t count = 0;
  while(1){
    
    //  Usando Laço de repetição
    //  É alterado com a otimização do código. O LED pisca mais rápido se a otimização crescer.
    do{
      count++;
    }while(count != 2400000);
    count = 0;
  
    //  Usando SysCtlDelay(x);
    //  Frequência setada em 24MHz, temos um periodo igual 41,667ns (0,000000041667 segundos).
    //  Como o SysCtlDelay utiliza 3 instruções, temos: 41,67ns * 3 = 125ns
    //  Queremos 1 segundo, então: 1s/125 ns = 8000000 
    //  Assim podemos usar SysCtlDelay(8000000)
    //  Não é alterado ao otimizar o código.
    //  SysCtlDelay(8000000);
    
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, status);  //Acende LED se Status "verdadeiro", Apaga LED se Status "falso"
    status = !status;                                   //Inverte a status da variável booleana 

  } // while
} // main