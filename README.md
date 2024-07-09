# Flappy-Bird-Clone-Prototype-
This is a Flappy Bird Clone that I have made in C++ using the SDL2 development library. I made this project in my first year of university as an attempt to learn C++ and Game Development in C++. 

Files like the RenderWindow files and Entity files is not completely my own as these files are from my attempts at learning how to use the SDL2 library from
CodeGopher's tutorial video on how to create a 2D physics based platformer using SDL2:
https://www.youtube.com/watch?v=KsG6dJlLBDw&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS

Gameplay loop and other logistical elements of the game were inspired from PolyMars' video on making a DS Game in 2020:
https://www.youtube.com/watch?v=h7pq9hUMnog

All textures were made by me using paint

This was my first attempt at creating a somewhat professional game using an entirely new language and development library, with my only prior experience with C++ was learning different
elements of object-oriented programming in my course that was taught using C and my computer science class in my senior year of highschool using Java (which is relatively similar to C++ in my opinion)

**IMPORTANT**
If you want to download these files to run on your computer, put the files/folders listed into a new created folder named "src":
include (folder)
lib (folder)
entity.cpp (file)
main.cpp (file)
math.cpp (file)
renderwindow.cpp (file)

And to run the game, make sure your Makefile is in the folder, and to run it all you need to do it make sure your terminal directory is to the game folder, 
and just put "make" as the compiling word in the terminal

Without these steps the code will not run as intended due to the Makefile containing code with the previously mentioned files being in an 'src' folder.
