# ATtinyx4A_IO_Example

Example program for using I/O on Atmel ATtiny24A/44A/84A

Created: 02/09/2016
Author: Will Sakran
Metre Ideas and Design

This program uses an external interrupt (INT0 on pin PB2) to step through turning various
output pins on and off. Triggering the interrupt will turn on the next output in sequence
from PA0 through PA7. Outputs are configured as active high.

This example also includes code for putting the chip into a low power idle state. When
sleeping, the chip is woken up by the external interrupt.

Developed for use with Atmel ATtiny24A / ATtiny44A / ATtiny84A
For ATtiny24A/44A/84A Prototyping boards go to
www.metreideas.com
 
