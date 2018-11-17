#include "iostm8s003f3.h"
unsigned char buffer[256];
volatile unsigned char r_pointer;
unsigned char w_pointer;
#include "cpu.c"
#include "spi.c"

// Interrupt service TIMER4
#pragma vector = TIM4_OVR_UIF_vector
__interrupt void TIM4_OVR_UIF_handler(void){
  // Check the source of interrupt
  if (TIM4_SR_UIF==1){
    TIM4_SR_UIF = 0; // Reset interrupt flag
    TIM1_CCR4H = 0x00;
    TIM1_CCR4L = buffer[r_pointer]; // Set new sample
    r_pointer++;
  }
}

void play(unsigned long addr, unsigned long len){
  unsigned long playtime = 0;
  unsigned char filled = 0;
  extern unsigned char buffer[256];
  // First fill a buffer by sound data
  _spi_start();
  _spi_sendbyte(0x03);
  _spi_sendbyte(addr & 0xFF);
  _spi_sendbyte((addr>>8) & 0xFF);
  _spi_sendbyte((addr>>16) & 0xFF);
  _spi_sendbyte(0x00); //dummy
  w_pointer = 1;
  r_pointer = 0;
  while(playtime<len){
    if(r_pointer != w_pointer){
      buffer[w_pointer] = _spi_readbyte();;
      w_pointer++;
      playtime++;
    }else{
      if(!filled){
        // Now start playback
        TIM1_CR1_bit.CEN = 1;
        TIM4_CR1_bit.CEN = 1;
        filled = 1;
      }
    }
  }
  _spi_stop();
  // We fill buffer, but playback is more slowly than reading flash, so wait until pointers are equal
  while(r_pointer != w_pointer){}
  // Then stop timers
  TIM1_CR1_bit.CEN = 0;
  TIM4_CR1_bit.CEN = 0;
}

int main(void){
  cpu_init();
  asm("rim");
  play(0, 857677); // Size and start position in bytes!!!
  while(1){
    play(857677, 70508);
  }
}
