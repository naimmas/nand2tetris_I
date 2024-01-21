// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/Or8Way.tst

load Or16Way.hdl,
output-file Or16Way.out,
output-list in%B2.16.2 out%B2.1.2;

set in %B0000000000000000,
eval,
output;

set in %B11111111,
eval,
output;

set in %B0001000000010000,
eval,
output;
