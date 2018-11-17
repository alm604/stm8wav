void cpu_init(void){
  /*
  000 — fCPU=fMASTER
  001 — fCPU=fMASTER/2
  010 — fCPU=fMASTER/4
  011 — fCPU=fMASTER/8
  100 — fCPU=fMASTER/16
  101 — fCPU=fMASTER/32
  110 — fCPU=fMASTER/64
  111 — fCPU=fMASTER/128
  /
  CLK_CKDIVR_CPUDIV = 0;
  /
  00 — fCPU=fHSI
  01 — fCPU=fHSI/2
  10 — fCPU=fHSI/4
  11 — fCPU=fHSI/8
  */
  CLK_CKDIVR_HSIDIV = 0;
  PC_DDR_bit.DDR6 = 1;
  PC_CR1_bit.C16 = 1;
  PC_DDR_bit.DDR5 = 1;
  PC_CR1_bit.C15 = 1;
  PC_DDR_bit.DDR4 = 1;
  PC_CR1_bit.C14 = 1;
  PC_DDR_bit.DDR3 = 1;
  PC_CR1_bit.C13 = 1;
  PC_DDR_bit.DDR7 = 0;
  // Need 11025 Hz reload
  // 8 bit mode sound
  // 16M/128/11025 = 11.3
  TIM4_CR1 = 0x80;// ARPE=1
  TIM4_IER = MASK_TIM4_IER_UIE; // Update interrupt enable
  TIM4_PSCR = 7; //128
  TIM4_ARR = 10;
  TIM4_CR1_bit.CEN = 1;
  TIM1_CR1_bit.ARPE = 1;
  TIM1_CR1_bit.DIR = 1;
  TIM1_PSCRH = 0x00;
  TIM1_PSCRL = 0x00;
  TIM1_ARRH = 0x00;
  TIM1_ARRL = 0xFF;
  TIM1_BKR = 0x80; // OC and OCN outputs are enabled if their respective enable bits are set (CC/E in Tim1_CCERi)
  TIM1_CCMR4 = 0x68; // PWM mode 1 CH4 active while CNT<CCR4
  TIM1_CCER2 = 0x10; //CH4 compare Enable ??????
  TIM1_CCR4H = 0x00;
  TIM1_CCR4L = 0x01;
  TIM1_CR1_bit.CEN = 1;
}
