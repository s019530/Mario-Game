v1. Base game.


v1.1 Fixed Memory leak, redid how inputs are handeled, added jumping.


v1.2 Added some collision support for the ground, addded free falling and stuff like that


v1.3 cleaned up some code, added file stuff, now reads levels from files

v1.4 added side collision support. Main problem with this is that you won't go up completely against the wall a lot of the time before getting blocked due to the fact that if I allowed that it would cause clipped because of issues with how the detection for if you're standing on the ground or not works. it would need to be changed somehow to let you stand on part of a block, writing this now I think what I could do is cut the character in half and if half of the character is on a block then allow them to stand there... Maybe in another version when I have the motivation to fix this kind of issue