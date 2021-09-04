# Remote-Agriculture-Solution
## Design For A Cause 2021 

[Blog Link](https://www.element14.com/community/community/design-challenges/design-for-a-cause-2021/blog/2021/05/26/blog-1-remote-agriculture-solution)

[Project Video](https://www.element14.com/community/community/design-challenges/design-for-a-cause-2021/blog/2021/05/28/remote-agriculture-solution-09-time-to-see-the-work-in-action)

[Featured Post](https://www.element14.com/community/docs/DOC-96784/l/meet-the-winners-of-design-for-a-cause-2021?ICID=design-aCause2021-topban#:~:text=We%20loved%20the%20listed,to%20receive%20their%20prizes.)

# Introduction

Agriculture has been increasingly getting expensive, time consuming and labour intensive. Through this project, I aim to help farmers manage their crops more easily and remotely. This will allow farmers to increase production by using automated means and in turn reduce expenses.

Agricultural expenses are increasing at a tremendous rate. So are the risks posed by farmers handling hazardous pesticides. By the use of IOT, we can allow farmers to regularly spray pesticides in the farms even in adverse weather and keep them safe from serious health hazards.

## Problems that this project aims to solve:

- Automatic spraying of pesticides on plants according to the requirement.
- Automatic irrigation of crops/plants based on humidity and temperature of the soil.
- Automatically cover the whole field
- Detect when pesticide/water level is insufficient in the container and alert the farmer so that crops are taken care of properly.
- Monitor the plant surroundings like sunlight, temperature, humidity etc. to help the farmer collect information and improve cropping patterns.



## Project Plan:

<!-- ![image](https://user-images.githubusercontent.com/22559451/132092452-80d38936-d058-404c-8861-5864f0bde46b.png) -->
<img src="https://user-images.githubusercontent.com/22559451/132092452-80d38936-d058-404c-8861-5864f0bde46b.png" alt="flowchart" width="500"/>

The project comprises of three parts:

- Pest control system

- Irrigation system

- Monitoring system

### Pest control system:

I have planned to make a pesticide spraying mechanism buying/creating a peristaltic motor to pump the pesticide from the container and spray it onto the crops. This process will be initiated using Arduino Nano 33 IOT microcontroller. This will also alert the farmer about the level of pesticide in the container and send a notification when it falls below a prescribed level. This will be done using an ultrasonic sensor.

 

### Irrigation system:

I have planned to use a similar mechanism as described above for the irrigation system. Additionally, to make this process fully automatic, I will use a soil sensor to detect the moisture and temperature of the soil. Whenever, the humidity of the soil falls below a threshold, the water pump will start watering the crop.

 

### Monitoring system:

Using the Arduino Nano 33 IOT, I will be able to send real time farm data to the farmer. So, I plan to send the data of the soil sensor, temperature sensor and humidity sensor (for the surrounding). Additionally, I will use an LDR to measure the luminescence of sunlight and share the same using IOT to the farmer. This will allow the farmer to keep track of the crops remotely and evaluate data over seasons to understand the effect of changes applied by the farmer in cropping pattern and their impact. This will allow the farmer to adopt strategies that will enable him/her to increase crop yield with minimum input requirements.


<!-- ![image](https://user-images.githubusercontent.com/22559451/132092578-d763d195-4e97-4f02-aa57-2eafac8cb1f1.png) -->
<img src="https://user-images.githubusercontent.com/22559451/132092578-d763d195-4e97-4f02-aa57-2eafac8cb1f1.png" alt="circuitdiagram" width="600"/>

<!-- ![image](https://user-images.githubusercontent.com/22559451/132092484-857309fa-40f0-46ee-a997-28e761678c6e.png)
![image](https://user-images.githubusercontent.com/22559451/132092570-4b49adfe-6be8-4ba4-bbc0-145b6cc62040.png) -->

<img src="https://user-images.githubusercontent.com/22559451/132092570-4b49adfe-6be8-4ba4-bbc0-145b6cc62040.png" alt="projectpicture" width="400"/>
<img src="https://user-images.githubusercontent.com/22559451/132092484-857309fa-40f0-46ee-a997-28e761678c6e.png" alt="screenshot" width="200" height="400"/>



## Further Improvements

- For irrigation, drip irrigation method can be employed. This will help reduce water consumption drastically. Drip irrigation pipes can be installed in the farm and the watering can be done using IOT and soil sensor.

- Adding more soil sensors to irrigate the farm will make it much more efficient and appropriate for a large farm. 

- I had to remove my servo motor for Ultrasonic Sensor due to lack of space in my chassis. This can be added quite easily with a bigger chassis and make the bot more efficient.

- The accuracy of LDR is not too great for measuring intensity. It could be replaced with a more reliable photo diode which would improve efficiency and make the results more accurate.

- Other than that using the data collected over a season or so, further changes can be made to pesticide spraying techniques to make it even more efficient. 



