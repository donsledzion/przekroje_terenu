# przekroje_terenu
One of my very first projects as a programmer.
In this project acctually I made my first steps in c++ just to make simple console application which helped me to speed up creation of my thesis.
To complete my water engineering project I had to make multiple river bed's cross-sections.
I decided to speed up this laborious part of drawing dozens of cross-sections.

This console program can transform input numerical data into ready AutoCAD drawing script.
Script is just sequence of AutoCAD commands that gives us ready drawing.

Input methods: reload last drawing, keybord, *.txt or *.csv formatted files

Output: AutoCAD script file that can be easly dragged and dropped int to AutoCAD. After dropping script file the final drawing is shown.

User can setup:
 - vertical and horizontal scale (separately)
 - font size (program sugests max size of font that depends on scale and density of points - in case of keeping clarity of drawing)
 - drawing title
 - trrain reference level
