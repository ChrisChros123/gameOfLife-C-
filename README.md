# gameOfLife(C) - glider motif

The makefile can be used to compile and link (call: make) and to erase the created files (call: make clean). 
Then, the program can be started from the command line by calling: 

    $ ./gameOfLife sizeOfField numberOfGen delay
where 
sizeOfField: quadratic size of the field which the glider moves through before it comes out on the other side
numberOfGen: number of conformation changes of the glider until the program ends
delay: in ms between the conformation changes
(e.g. ./gameOfLife 20 100 70)

## Background
"*" represents a "living cell, "_" (space) represents a dead cell.
Evolution rules:
- iff 3 of its neighbors are alive, a dead cell becomes alive
- if < 2 or > 3 of its neighbors are alive, a iving cell dies
- else, a cell remains unchanged



