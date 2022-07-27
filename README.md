This device controls a solenoid valve.
It has been built for a very specific application, but one can easily adapt it and change to another application where a solenoid valve needs to be controlled.
I used Arduino uno as I had it avaiable, but it is not the best choice as it takes up a lot of space.

This device has three buttons:
1.	Reset. 
2.	Set timer. Changes time interval.
3.	Cycle On/Off. Turns cycling on and off.

The solenoid stays on for 3 seconds. You may consider using an encoder if you want to be able to adjust the duration.
Because my project required an airtight container, I added a temperature sensor TMP36 and a thermal fuse. The formula in the code calculates the temperature in Celsius.
If the temperature is 50 degrees or over a red LED will turn on.  
The screen displays current temperature, On/Off time interval in minutes and Shows whether cycling is On or Off.