This device controls a solenoid valve.
It has been built for a very specific application, but one can easily change it or make it a part of a project where a solenoid valve needs to be controlled.
I used Arduino uno as I had it avaiable, but it is not the best choice as it takes up a lot of space.

This device has three buttons:
1.	Reset. 
2.	Set timer. Changes time interval.
3.	Cycle On/Off. Turns cycling on and off.

The solenoid stays on for 3 seconds. You may consider using an encoder if you want to be able to adjust the duration.
Because my project required an airtight container, I added a temperature sensor TMP36 and a thermal fuse. The formula in the code calculates the temperature in Celsius.
If the temperature is 50 degrees or over a red LED will turn on.  
The screen displays current temperature, On/Off time interval in minutes and Shows whether cycling is On or Off.

![image](https://user-images.githubusercontent.com/86169204/181358164-69243fe1-f8c3-4ed5-b8df-6ba9a8855349.png)


![image](https://user-images.githubusercontent.com/86169204/181357887-b378ddd8-1c05-4222-ac55-8f99898fbcfd.png)

You can find a hoock up diagram in the Diagram folder. The pdf version of the diagram has notations that show which part of the circuit does what.
