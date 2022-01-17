# Testers for non-elementary IC
> Testers for CS @ UCU POC course exam

Code should be uploaded to *PSoC 4* and IC to be tested should be connected (by jump wires) to corresponding pins of PSoC board. Indicator diode (`Test`) will blink once for *100 ms* before indicating result -- if it is HIGH *IC is not working as expected*. If it is `LOW` it *works normally*. More specific details, e.g. what is not working, can be viewed via **UART** (baud rate: 9600).

- [X] **74283** 4-Bit Binary Adder
- [X] **74174** Hex D-Type Flip-Flops with Clear
- [X] **74193** Synchronous 4-Bit Up/Down Counters
