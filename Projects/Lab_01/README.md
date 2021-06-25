# ELF74 - Sistemas Embarcados

Repositório destinado ao laboratório 01 da unidade curricular ELF74 - Sistemas Embarcados, ministrada na Universidade Tecnológica Federal do Paraná (UTFPR). 

## Professor

Hugo Vieira Neto

## KIT de Desenvolvimento

[ARM® Cortex®-M4F-Based MCU TM4C1294 Connected LaunchPad™ Evaluation Kit](https://www.ti.com/tool/EK-TM4C1294XL)

## Análise e Discussão
Alterando a otimização do compilador C, percebe-se que há uma alteração na frequência em que o LED pisca. Foi utilizado o seguinte laço de repetição para gerar o delay.

do{
	count++;
}while(count != 2400000);
count = 0;

Se observarmos a janela do IAR (Disassembly) são utilizados dois comandos em assembly para executar o laço. A configuração de otimização foi selecionada em "LOW".

- ADDS
- LDR. N
 
Quando alteramos a configuração de otimização de "LOW" para "HIGH", observamos uma mudança dos comandos assembly.

- ADDS
- CMP

A velocidade que o LED pisca muda pois o comando LDR. N utiliza dois ciclos de clock. Já o CMP utiliza 1 ciclo de clock. Seria necessário ajustar a condicional de saída do while para que o delay permanecesse em 1 segundo.

Além do laço de repetição foi utilizada a função SysCtlDelay.

//  SysCtlDelay(8000000);

Esta função utiliza 3 ciclos de clock e é mais adequada para ser usada na necessidade de um delay pois não sofre interferência referente otimização do compilador. Basta apenas realizar um cálculo do período conforme a frequência selecionada.
 
## Referências
- The Definitive Guide to ARM® Cortex®-M3 and Cortex®-M4 Processors, Third Edition by Joseph Yiu