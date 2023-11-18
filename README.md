# nand2tetris-project6-C

Implementation of the project 6 compiler task from nand2tetris written in pure C.

This was my first time writing C, and there's probably a lot to refactor but I'd rather keep moving on in the course.
In retrospect I wouldn't recommend anyone doing this project in C, and if I was to do it again would have gone with C++ or another language with a bit more built in functionality.

It was still a great experience and I learned a lot about both compilers and the C language and am now way more grateful for higher level languages.

### How to use

[Nand2Tetris Course](https://www.nand2tetris.org/course)

[Project 6 overview](https://drive.google.com/file/d/1CITliwTJzq19ibBF5EeuNBZ3MJ01dKoI/view)

To recompile the code I added a nice MAKEFILE, you can call both:

`make all`

`make clean`

If you make any changes to the src code.

To retest, I have a hello.asm test assembly file that you can convert to the machine binary by running:

`./shinoasm hello.asm`
