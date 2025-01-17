# C project for a 1st year engineering school C class

Simple solar system, with a physic simulation and Raylib as the graphical library.

The displayed planets are generated from the file "Calcul_Projet.csv" which can be edited to change the simulated system.

Camera controls (moving and zooming across the system) are fully implemented as follows : 
  - Arrows to move
  - Numpad +/- to zoom
  - Shift and Enter to reset zoom and movement
  - 1-8 keyboard key to zoom on a planet (in order)
  - N / T to toggle names and traces of the planets
 
The planets are displayed and their positions are calculated in a linked list, which allows for dynamic displaying, planets can be toggled via key 1-8 of the Numpad
