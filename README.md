# circuitz

circuitz is a program that analyses electrical circuits and determines whether or not they satisfy the laws of physics. Two types of constraints must be fulfilled for a circuit to be valid:

## Element Constraints
This type of constraint is focused on each element in the circuit (batteries, lights, etc.). Each element will have three numbers associated with it:

 - Voltage
 - Current
 - Resistance
 
 For each element these numbers must satisfy this equation:

> Voltage = Current * Resistance

The law that outlines this equation is called **Ohm's Law**.

## Connection Constraints
This constraint focuses entirely on how the elements are connected together. There are two laws here that must be satisfied:
