#include "project.h"
#include <stdio.h>

char TEXT_BUF[80];

int
main (void)
{
  CyGlobalIntEnable;

  UART_Start(); 
  UART_UartPutString("Starting test for Counter 74193..\r\n");

  for(;;)
    {
      int isWrong = 0;

      Load_Write(1);
      Up_Write(1);
      Down_Write(1);

      CLR_Write(1);
      CLR_Write(0);
      
      for (int a = 0; a <= 1; a++)
        {
          for (int b = 0; b <= 1; b++)
            {
              for (int c = 0; c <= 1; c++)
                {
                  for (int d = 0; d <=1; d++)
                    {
                      CLR_Write(1);
                      CyDelay(1);
                      CLR_Write(0);

                      int res = Qa_Read() + 2*Qb_Read() + 4*Qc_Read() + 8*Qd_Read();
                      if (res != 0)
                        {
                          sprintf(TEXT_BUF, "Wrong value after CLR  (abcd=%d%d%d%d, QaQbQcQd=%d%d%d%d)\r\n",
                                                        a, b, c, d, Qa_Read(), Qb_Read(), Qc_Read(), Qd_Read());
                          UART_UartPutString(TEXT_BUF);
                          isWrong = 1;
                        }

                      if (BO_Read() == 0)
                        {
                          sprintf(TEXT_BUF, "Wrong value for not BO (expected 1, got 0)\r\n");
                          UART_UartPutString(TEXT_BUF);
                          isWrong = 1;
                        }
                      
                      if (CO_Read() == 0)
                        {
                          sprintf(TEXT_BUF, "Wrong value for not CO (expected 1, got 0)\r\n");
                          UART_UartPutString(TEXT_BUF);
                          isWrong = 1;
                        }
                      
                      Load_Write(0);
                      CyDelay(1);

                      A_Write(a);
                      B_Write(b);
                      C_Write(c);
                      D_Write(d);
                      
                      CyDelay(1);
                      Load_Write(1);
                      
                      res = Qa_Read() + 2*Qb_Read() + 4*Qc_Read() + 8*Qd_Read();
                      int expected = a + 2*b + 4*c + 8*d;
                      int expected_init = expected;
                      
                      if (res != expected)
                        {
                          sprintf(TEXT_BUF, "Wrong value after LOAD (abcd=%d%d%d%d, QaQbQcQd=%d%d%d%d, Clear=%d)\r\n",
                                                    a, b, c, d, Qa_Read(), Qb_Read(), Qc_Read(), Qd_Read(), CLR_Read());
                          UART_UartPutString(TEXT_BUF);
                          isWrong = 1;
                        }

                      // Decrement
                      Down_Write(0);
                      CyDelay(1);
                      if (expected_init == 0 && BO_Read() == 1)
                        {
                          sprintf(TEXT_BUF, "Wrong value for not BO (expected 0, got 1; Count=0, Down=0)\r\n");
                          UART_UartPutString(TEXT_BUF);
                          isWrong = 1;
                        }
                      Down_Write(1);

                      res = Qa_Read() + 2*Qb_Read() + 4*Qc_Read() + 8*Qd_Read();
                      expected = a + 2*b + 4*c + 8*d - 1;
                      expected = expected == -1 ? 15 : expected;
                      if (res != expected)
                        {
                          sprintf(TEXT_BUF, "Wrong value after DOWN (abcd=%d%d%d%d, QaQbQcQd=%d%d%d%d; res=%d, expected=%d)\r\n",
                                           a, b, c, d, Qa_Read(), Qb_Read(), Qc_Read(), Qd_Read(), res, expected);
                          UART_UartPutString(TEXT_BUF);
                          isWrong = 1;
                        }

                      // Return to the initial state
                      Up_Write(0);
                      CyDelay(1);
                      Up_Write(1);
                      CyDelay(1);                        

                      // Increment
                      Up_Write(0);
                      CyDelay(1);
                      if (expected_init == 15 && CO_Read() == 1)
                        {
                          sprintf(TEXT_BUF, "Wrong value for not CO (expected 0, got 1; Count=15, Up=0)\r\n");
                          UART_UartPutString(TEXT_BUF);
                          isWrong = 1;
                        }
                      Up_Write(1);
                      
                      
                      res = Qa_Read() + 2*Qb_Read() + 4*Qc_Read() + 8*Qd_Read();
                      expected = (a + 2*b + 4*c + 8*d + 1)%16;
                      if (res != expected)
                        {
                          sprintf(TEXT_BUF, "Wrong value after UP   (abcd=%d%d%d%d, QaQbQcQd=%d%d%d%d; res=%d, expected=%d)\r\n",
                                              a, b, c, d, Qa_Read(), Qb_Read(), Qc_Read(), Qd_Read(), res, expected);
                          UART_UartPutString(TEXT_BUF);
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
  return 0;
}

/* [] END OF FILE */
