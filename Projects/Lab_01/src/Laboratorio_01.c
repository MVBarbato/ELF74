//Universidade Tecnol�gica Federal do Paran�
//Sistemas Embracados
//AUTOR: Matheus Victor Barbato - 1862308
//Data de cria��o: 24/06/2021
//Ultima modifica��o: 24/06/2021
//Laborat�rio 01


//H� varia��es na temporiza��o por software para os casos acima? Quantifique-as.
//R:

//Os seguintes trechos de c�digo s�o equivalentes:
//� GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
//� GPIOPinWrite (0x40025000, 0x00000010, 0x00000010);
//Qual dos trechos de c�digo acima � mais leg�vel e f�cil de se compreender?
//R: 

//Os seguintes trechos de c�digo s�o equivalentes:
//� GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
//� GPIOPinTypeGPIOOutput (0x40025000, 0x00000011);
//Qual dos trechos de c�digo acima � mais leg�vel e f�cil de se compreender?
//Obs : GPIO_PIN_0=0x01; GPIO_PIN_4=0x10
//R:

#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void main(void){
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);          // Habilita GPIO F (LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));   // Aguarda final da habilita��o
    
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);   // LEDs D4 como sa�da
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);         // LEDs D4 apagados
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  bool status = 0;
  uint32_t count = 0;
  while(1){
    
    //Usando La�o de repeti��o
    do{
      count++;
    }while(count != 2400000);
    count = 0;
  
    //  Usando SysCtlDelay(x);
    //  Frequ�ncia setada em 24Mhz, temos um periodo igual 41,667ns (0,000000041667 segundos).
    //  Como o SysCtlDelay utiliza 3 instru��es, temos: 41,67ns * 3 = 125ns
    //  Queremos 1 segundo, ent�o: 1s/125 ns = 8000000 
    //  Assim podemos usar SysCtlDelay(8000000)
    //  N�o � afetado ao otimizar o c�digo
    
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, status);  //Acende LED se Status "verdadeiro", Apaga LED se Status "falso"
    status = !status;                                   //Inverte a status da vari�vel booleana 

  } // while
} // main