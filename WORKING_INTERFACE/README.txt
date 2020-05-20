The interface controls the specific parameters of how to step the motors
NO DISTINCTION BETWEEN TWO AXIS, STEPS THE SAME WAY

The interface works by control via 4 buttons, labeled "sel", "inc", "dec", "cfm"

"sel" = select
"inc" = increase
"dec" = decrease
"cfm" = confirm

The interface controls the length of gel, stretch amount in either direction, and time of stretch operation.

The interface functions similar to a monitor options menu.
The select button cycles through the parameters
The increase/decrease buttons increase/decrease the selected variable by a fixed increment.
Size of the increment is in the program, easily modifiable.
The confirm button will confirm the settings and prompt for final confirmation
Once final confirmation is confirmed, the experiment will start after a 10 second count down
	during the countdown (or at any point of the program), the program can be terminted by cutting off the power or pressing the reset button on the arduino.

More on button debouncing and wiring schematics
https://www.arduino.cc/en/Tutorial/StateChangeDetection




For the LCD display,
https://www.amazon.com/gp/product/B071FGZX8G/ref=ox_sc_act_title_2?smid=AF7ERVVKLDA4G&psc=1
This specific lcd display comes with a i2c driver, which simplifies the inputs to 4 pins for arduino
SCL pin goes to pin 21 (SCL)
SDA pin goes to pin 20 (SDA)
Power is 5V and GND

Note: The lcd display displays characters like a 20x4 array, 
  there are no new line commands
  must use setCursor