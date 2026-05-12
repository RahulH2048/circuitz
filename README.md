# circuitz

circuitz is a program that analyses electrical circuits and determines whether or not they are valid circuits. To do this it checks two categories of constraints:

## Element Constraints

Circuit elements refer to things like batteries, resistors, diodes etc. Each element can be defined by these three values:

- Voltage
- Current
- Resistance

In every element these three values must respect this equation:

> Voltage = Current \* Resistance

This law is called **Ohm's Law**.

## Connection Constraints

Analysing connection constraints requires the consideration these two concepts:

- A **node** is a section of wire between **elements** (colored segments in image)
- **elements** are the devices between these **nodes** (black objects in image)

![](https://upload.wikimedia.org/wikipedia/commons/thumb/9/95/Nodes2.svg/3840px-Nodes2.svg.png)

There are two constraints that must be checked here:

- **Kirchoff's Current Law**: The amount of current entering into a node must be equal to the amount of current leaving

- **Kitchoff's Voltage Law**: The net voltage of each loop contained within the circuit must be zero.

![](https://www.electronicspecifier.com/wp-content/uploads/2025/11/AdobeStock_498668731.jpeg)
