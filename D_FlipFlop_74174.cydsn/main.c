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

int main(void)
{
    CyGlobalIntEnable;

    UART_Start(); 
    UART_UartPutString("Testing 74174\r\n");
    
    for(;;)
    {
        /*
        Test_Write(0);
        int not_clr = 1;
        
        CLK_Write(0);
        NOT_CLR_Write(not_clr);
        D_1_Write(0);
        
        CyDelay(100);
        CLK_Write(1);
        CyDelay(100);
        CLK_Write(0);
        
        sprintf(TEXT_BUF, "Written 0 to D_1 with NOT_CLR=%d. Q now is %d\r\n", not_clr, Q_1_Read());
        UART_UartPutString(TEXT_BUF);
        
        
        
        CyDelay(500);
        D_1_Write(1);
        
        CyDelay(100);
        CLK_Write(1);
        CyDelay(100);
        CLK_Write(0);
        
        sprintf(TEXT_BUF, "Written 1 to D_1 with NOT_CLR=%d. Q now is %d\r\n", not_clr, Q_1_Read());
        UART_UartPutString(TEXT_BUF);
        
        
        
        CyDelay(500);
        D_1_Write(0);
        
        CyDelay(100);
        CLK_Write(1);
        CyDelay(100);
        CLK_Write(0);
        
        sprintf(TEXT_BUF, "Written 0 to D_1 with NOT_CLR=%d. Q now is %d\r\n", not_clr, Q_1_Read());
        UART_UartPutString(TEXT_BUF);
        */
        
        int isWrong = 0;
        
        // Initialize - All D=0 & Q=0; CLK=0
        CLK_Write(0);
        NOT_CLR_Write(1);
        D_1_Write(0);
        D_2_Write(0);
        D_3_Write(0);
        D_4_Write(0);
        D_5_Write(0);
        D_6_Write(0);
        
        CyDelay(1);
        CLK_Write(1);
        CyDelay(1);
        CLK_Write(0);
        
        int d_prev = 0;
        
        for (int clear = 0; clear <= 1; clear++) {
            NOT_CLR_Write(clear);
            for (int d = 0; d <= 1; d++) {
                int q1 = Q_1_Read();
                int q2 = Q_2_Read();
                int q3 = Q_3_Read();
                int q4 = Q_4_Read();
                int q5 = Q_5_Read();
                int q6 = Q_6_Read();
                
                if (q1 != clear*d_prev){
                    isWrong = 1;
                    sprintf(TEXT_BUF, "Wrong for clear=%d -- q1=%d, d_prev=%d (d=%d)\r\n", clear, q1, d_prev, d);
                    UART_UartPutString(TEXT_BUF);
                }
                if (q2 != clear*d_prev ){
                    isWrong = 1;
                    sprintf(TEXT_BUF, "Wrong for clear=%d -- q2=%d, d_prev=%d (d=%d)\r\n", clear, q2, d_prev, d);
                    UART_UartPutString(TEXT_BUF);
                }
                if (q3 != clear*d_prev ){
                    isWrong = 1;
                    sprintf(TEXT_BUF, "Wrong for clear=%d -- q3=%d, d_prev=%d (d=%d)\r\n", clear, q3, d_prev, d);
                    UART_UartPutString(TEXT_BUF);
                }
                if (q4 != clear*d_prev ){
                    isWrong = 1;
                    sprintf(TEXT_BUF, "Wrong for clear=%d -- q4=%d, d_prev=%d (d=%d)\r\n", clear, q4, d_prev, d);
                    UART_UartPutString(TEXT_BUF);
                }
                if (q5 != clear*d_prev ){
                    isWrong = 1;
                    sprintf(TEXT_BUF, "Wrong for clear=%d -- q5=%d, d_prev=%d (d=%d)\r\n", clear, q5, d_prev, d);
                    UART_UartPutString(TEXT_BUF);
                }
                if (q6 != clear*d_prev ){
                    isWrong = 1;
                    sprintf(TEXT_BUF, "Wrong for clear=%d -- q6=%d, d_prev=%d (d=%d)\r\n", clear, q6, d_prev, d);
                    UART_UartPutString(TEXT_BUF);
                }
                D_1_Write(clear*d_prev);
                D_2_Write(clear*d_prev);
                D_3_Write(clear*d_prev);
                D_4_Write(clear*d_prev);
                D_5_Write(clear*d_prev);
                D_6_Write(clear*d_prev);
                
                CyDelay(1);
                CLK_Write(1);
                CyDelay(1);
                CLK_Write(0);
                
                d_prev = clear*d_prev;
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
