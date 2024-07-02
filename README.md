file convention: TYPE, TOP, BOTTOM, RIGHT, LEFT

PATCHES

v1. Base game.


v1.1 Fixed Memory leak, redid how inputs are handeled, added jumping.


v1.2 Added some collision support for the ground, addded free falling and stuff like that


v1.3 cleaned up some code, added file stuff, now reads levels from files

v1.4 added side collision support. Main problem with this is that you won't go up completely against the wall a lot of the time before getting blocked due to the fact that if I allowed that it would cause clipped because of issues with how the detection for if you're standing on the ground or not works. it would need to be changed somehow to let you stand on part of a block, writing this now I think what I could do is cut the character in half and if half of the character is on a block then allow them to stand there... Maybe in another version when I have the motivation to fix this kind of issue. I also changed the hight of the character to 50 units

v1.5 added new kind of objects - brown blocks. combined paint functions to eliminate redundency.

v1.6 fixed jump bug, still working on other blocks not working, need to redesign side collisions entirely i think, if brown blocks work then the ground doesn't, if the ground works then the blocks doesn't. 

v1.7 fixed the bug where you can't interact with other kind of blocks.

v2.0 Redid the structure of the project, created a main menu and starting work on creating an ingame menu

v2.1 Finished the escape menu.

v2.2 Started work on level creation. 

BUGS

can't walk fully up to blocks / ground - v1.4

can't interact with brown blocks - v1.5 | maybe another block is getting detected first or some shit? | v1.7

if you hold the jump button you keep jumping, basically bad detection on when the jump ends - v1.5 | before ending the jump check if in the air or some shit | fixed v1.6

for headache reasons, the code for mouse movements is being commented out because it's causing the program to crash on startup sometimes and not others, something i'll investigate later.
