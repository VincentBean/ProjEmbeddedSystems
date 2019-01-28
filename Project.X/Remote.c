#include "Remote.h"

// a=(1/fosc)�192
// 1a = (1/455000) * 192 = 421,978us  +/- 422
// 2a = 844us
// 3a = 1266us
// 4a = 1688us
// 60a = 25,31868ms
// 80a = 33,758ms
// 128a = 54,013ms 

void start_receive(void)
{    
    ir_input = 0;
    
    // Wacht 3a __delay_us(633);
    __delay_us(844);
    for (int i = 0; i < 12; i++) {
        ir_input = (ir_input << 1) | !PORTBbits.RB0;
        // Wacht 4a
        __delay_us(844);
    }

    handle_remote();
}


void handle_remote()
{
    char found = 0;
    
    unsigned int mask = 0b0000000111111111; // First 3 = code, last 9 = data;
    
    unsigned int data = ir_input & mask;
        
    switch (data) {
        case 72: // INPUT1 (358)
            _selectedInput = 0;
            _inputUpdateRequired = 1;
            found = 1;
            break;
        case 264: // INPUT2 (370)
            _selectedInput = 1;
            _inputUpdateRequired = 1;
            found = 1;
            break;
        case 160: // INPUT3 (359)
            _selectedInput = 2;
            _inputUpdateRequired = 1;
            found = 1;
            break;
        case 136: // INPUT4 (358)
            _selectedInput = 3;
            _inputUpdateRequired = 1;
            found = 1;
            break;
        case 288: // VOL+ (371)
            volume++;
            found = 1;
            break;
        case 272: // VOL- (370)
            volume--;
            found = 1;
            break;
    }

    ir_input = 0;    
    
}