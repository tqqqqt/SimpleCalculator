# Simple Calculator

This project is a final qualifying work at the institute.

The goal of this project is to implement a multifunctional calculator for computers using the Qt framework in the C++ language. The main feature of this calculator is that the calculator uses a string representation of numbers in all calculations, rather than numeric data types. This feature allows you to implement a change in the accuracy of various mathematical operations up to a huge number of decimal places. In total, the calculator should have 4 modes: basic, unit conversion, programmer mode and graphics.

To implement string mathematics, a custom library of functions was implemented, which turned out to be written quite optimally. To implement the calculation of expression values, the Polish notation algorithm was used, which made it possible to create greater optimization for the graph mode.

The basis for the interface was taken from the calculator application on Android. Basically, the color and location of some buttons were taken. Everything else was done in-house.

## Technical specifications:

**QT version** - 5.12.4 \
**QT Creator version** - 4.9.1 \
**System** - Windows 10 x86_64

## Future plans:

- [x] Make a basic interface
- [x] Make addition and subtraction
- [x] Make multiplication
- [x] Make division
- [x] Improve the interface
- [x] Add a floating point to nums

## Future big plans:

- [x] Value mode
- [x] Programmist mode
- [x] Graphics mode
