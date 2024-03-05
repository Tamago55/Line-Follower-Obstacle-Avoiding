# Line Follower and Obstacle Avoiding Tank

## 1. Introduction
In this project, we have created a line-following tank that is capable of avoiding obstacles, using an Arduino-based platform (RoMeo BLE v1.0). This tank utilizes infrared sensors to detect a black line on the ground (not magnetic tape) and follows it. Additionally, it employs ultrasonic sensors to identify obstacles and navigate around them. The robot can operate in complete darkness and is able to rejoin the main dark line even if there are other misleading lines present after avoiding an obstacle. Furthermore, if the line is broken while moving forward, it can also find its way back to the path.

Click to see the demonstration video below!!

<a href="https://www.youtube.com/shorts/7qLS-UVV_zI" target="_blank" rel="noopener noreferrer"><img src="http://img.youtube.com/vi/7qLS-UVV_zI/hqdefault.jpg" alt="Watch the video" style="max-width:100%;"></a>


## 2. Hardware Components
<img src="https://raw.githubusercontent.com/Tamago55/Line-Follower-Obstacle-Avoiding/main/pic/tank.JPG" width="30%" alt="Tank Image">

- [RoMeo BLE v1.0](https://wiki.dfrobot.com/RoMeo_BLE__SKU_DFR0305_)

- Devastator Tank Mobile Platform
  
- Ultrasonic Sensor
  
- Mini Servo Motor
  
- 3 Channel IR Sensor

## 3. Software 
- PlatformIO with Visual Studio Code

## 4. Logic
### Obstacle Avoidance
<img src="https://raw.githubusercontent.com/Tamago55/Line-Follower-Obstacle-Avoiding/main/pic/step1.png" width="50%" alt="Obstacle Avoidance Logic Image">

### Line Detection
<img src="https://raw.githubusercontent.com/Tamago55/Line-Follower-Obstacle-Avoiding/main/pic/step2.png" width="50%" alt="Line Detection Logic Image">

### Combine Object Avoidance and Line Detection
<img src="https://raw.githubusercontent.com/Tamago55/Line-Follower-Obstacle-Avoiding/main/pic/step3.png" width="20%" alt="Combined Logic Image">

