#define MOSI    PC_ODR_bit.ODR6
#define MISO    PC_IDR_bit.IDR7
#define NCS     PC_ODR_bit.ODR3
#define SCK     PC_ODR_bit.ODR5


// Sending 1 byte
void _spi_sendbyte(unsigned char d){
  unsigned char i;
  // Send 1 byte
  for(i=0; i<8; i++){
    // Check if MSB = 1
    if(d & 0x80){
      MOSI = 1; // Send 1
    }else{
      MOSI = 0; // Send 0
    }
    SCK = 1; // Clock
    d <<= 1;     // Shift byte
    //NOP();
    //NOP();
    SCK = 0; // Clock
  }
}

// Read byte
unsigned char _spi_readbyte(void){
  unsigned char i, spiReadData=0;
  for(i=0; i<8; i++){
    spiReadData <<= 1; // Shift word
    SCK = 1; // Clock
    asm("nop");
    if (MISO == 1) { spiReadData |= 0x01; } // Read bit
    //NOP();
    //NOP();
    SCK = 0; // Clock
  }
  return spiReadData;
}

// Start condition
void _spi_start(void){
   SCK = 0; // SPI_MODE = 0
   NCS  = 0; // Chip Select - Enable
}
 
 
// Stop condition
void _spi_stop(void){
   NCS  = 1; // Chip Select - Disable
   SCK = 0; // SPI_MODE = 0
}
