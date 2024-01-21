// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(CHECKKBD)
	@SCREEN
	D=A
	@adrs
	M=D
	@KBD
	D=M
	@BLACK
	D;JNE
	
(WHITE)
	@colour
	M=0
	@MAKESCREEN
	0;JMP

(BLACK)
	@colour
	M=-1
	
(MAKESCREEN)
	@colour
	D=M
	@adrs
	A=M
	M=D
	D=A
	@24575
	D=A-D
	@CHECKKBD
	D;JEQ
	@adrs
	M=M+1
	@MAKESCREEN
	0;JMP