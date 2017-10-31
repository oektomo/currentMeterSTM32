# Current Meter  
 
This project are created as a current meter in ZXCT1009   
we activate the UART and ADC  
- [x] Enable the UART  
- [x] Enable the ADC free running  
- [x] Trying single conversion
- [ ] When using DMA don't forget to make a circular buffer and check if the circular buffer ever overflow
- [ ] tidying the ADC free running code 
- [ ] Enable the Timer to trigger the ADC  
- [ ] do ADC scan conversion mode  
- [ ] update the platform_config.h  

Note:
Since we use newlib-nano please becarefull when using printf to print from float data type, it takes so much computation power and storage.  
    
PC software:  
write to *.txt file  

