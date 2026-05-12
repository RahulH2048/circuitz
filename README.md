# circuitz

circuitz is a program that analyses electrical circuits and determines whether or not they are valid circuits. To do this it checks two categories of constraints:

## Terminology

- A **node** is a section of wire between elements
- An **element** is a device connected between at least two nodes they can be things like batteries, resistors, diodes etc.

![Node: Colored Segments](https://cdn.sparkfun.com/assets/8/8/0/c/0/51b9edffce395f3630000002.png)

**Node**: Colored segments
**Element**: Red labelled objects

## Element Constraints

Each element is defined by these three values:

- Voltage
- Current
- Resistance

In every element these three values must respect this equation:

> Voltage = Current \* Resistance

This law is called **Ohm's Law**.

## Connection Constraints

Analysing connection constraints requires the consideration of these two concepts:

There are two constraints that must be checked here:

- **Kirchoff's Current Law**: The amount of current entering into a node must be equal to the amount of current leaving

- **Kitchoff's Voltage Law**: The net voltage of each loop contained within the circuit must be zero.

![](https://www.electronicspecifier.com/wp-content/uploads/2025/11/AdobeStock_498668731.jpeg)
