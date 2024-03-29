# This device controls a solenoid valve.

### Overview 
This device was used to upgrade analog equipment thus It has been built for a very specific application, but one can easily change it or make it a 
part of a project where a solenoid valve needs to be controlled.
I used Arduino uno as I had it avaiable, but it is not the best choice as it takes up a lot of space.

### Operation
This device has three buttons:
1.	Reset. 
2.	Set timer. Changes time interval.
3.	Cycle On/Off. Turns cycling on and off.

The solenoid stays on for 3 seconds. You may consider using an encoder if you want to be able to adjust the duration.
Because my project required an airtight container, I added a temperature sensor TMP36 (I did not need a calibrated sensor) and a thermal fuse. 
The formula in the code calculates the temperature in Celsius.

If the temperature is 45 degrees Celsius or over a red LED will turn on.  
The screen displays current temperature, On/Off time interval in minutes and shows whether cycling is On or Off. I used a mosfet IRF530, feel free to pick another one.

I used one power supply for the solenoid and the board, that is why I had to use a separate circuit to lower the voltge for the board. 

I used step bit to drill holes in the enclouser for the buttons and external usb. Must have easy usb access in case you need to change code.

### Consideration
I let 'int i' to be default initialized inside of a function since it does not really affect the application, but it is not the right way, you should initialize it to any value othe then 0 or 1. I went a little bit heavy on a button debouncing because of the environment in which that device is used, you may want to change it if you have to.

### Please feel free to use and modify the code but keep the first row where it says who built this.

### [Visit my instagram](www.instagram.com/dennis_r2018)

### Screenshots
![5543A692-270B-4858-969C-36EAFAFA1407](https://user-images.githubusercontent.com/86169204/181370868-7294cdc6-5df6-4b01-b90c-5644bd8b1f71.JPEG)

![9068D447-CB72-421D-ACD3-FD3A24DCE705](https://user-images.githubusercontent.com/86169204/181370910-16333c5f-62bc-442c-a540-c89820bbfd2e.JPEG)

![image](https://user-images.githubusercontent.com/86169204/181358164-69243fe1-f8c3-4ed5-b8df-6ba9a8855349.png)



