/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>

char TEXT_BUF[40];

/*
 * Tester for 74283 (4-Bit Binary Adder)
 *
 *
 */
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
  
    UART_Start(); 
    
    for(;;)
    {
        int isWrong = 0;
        for (int c = 0; c <= 1; c++) {
            for (int a1 = 0; a1 <=1; a1++) {
                for (int a2 = 0; a2 <=1; a2++) {
                    for (int a3 = 0; a3 <=1; a3++) {
                        for (int a4 = 0; a4 <=1; a4++) {
                            for (int b1 = 0; b1 <=1; b1++) {
                                for (int b2 = 0; b2 <=1; b2++) {
                                    for (int b3 = 0; b3 <=1; b3++) {
                                        for (int b4 = 0; b4 <=1; b4++) {
                                            A1_Write(a1);
                                            B1_Write(b1);
                                            A2_Write(a2);
                                            B2_Write(b2);
                                            A3_Write(a3);
                                            B3_Write(b3);
                                            A4_Write(a4);
                                            B4_Write(b4);
                                            
                                            Cin_Write(c);
                                            
                                            int correct_res = (a1+2*a2+4*a3+8*a4)+(b1+2*b2+4*b3+8*b4) + c;
                                            
                                            CyDelay(1);
                                            int s1 = Sum1_Read();
                                            int s2 = Sum2_Read();
                                            int s3 = Sum3_Read();
                                            int s4 = Sum4_Read();
                                            int Cout = Cout_Read();
                                            int obtained_res = Cout*16+s4*8+s3*4+s2*2+s1;
                                            
                                            sprintf(TEXT_BUF, "%d%d%d%d + %d%d%d%d = %d (obtained %d)\r\n", a1, a2, a3, a4, b1, b2, b3, b4, correct_res, obtained_res);
                                            UART_UartPutString(TEXT_BUF);
                                            
                                            if (correct_res != obtained_res) {
                                                UART_UartPutString("!!!!^^^^^!!!!\r\n");
                                                isWrong = 1;
                                            }
                                            CyDelay(1);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        // Tester diode blinks for 100 ms before indicating result to attract attention
        Test_Write(1);
        CyDelay(100);
        Test_Write(0);
        CyDelay(100);
        
        Test_Write(isWrong);
        
        if (isWrong)
            UART_UartPutString("Broken\r\n");
        else
            UART_UartPutString("Works Normally\r\n");
            
        CyDelay(1000);
    }       
}

/* [] END OF FILE */
