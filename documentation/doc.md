Documentation for cat.c

At row 79 the program calls the "setlocale()" function that sets the
entire local to be the enviroment`s deffault one.

At row 81 it uses "getopt()" to identify the flags that are used.

At row 112 there is an "if" statemend that checks if there is any flags and:

	-if  there are flags the program calls "cook_arg()" that starts do{}while cycle 
	which tryes to open the arguments that  don`t start with '-'. If they don`t
	open the cycle continues, but if they do the file descriptor "fd" is passed 
	to the function "cook_buf" that reads the file with "getch()" and print it edited 
	dependatnly of the flags. Then it checks for errors.
	
	-if there aren`t any flags it calls "raw_args()" that does almost the same thing  as 
	"cook_args". The diffrence is that it calls "raw_cat()" , which 
	reads the opened file, char by char with "read()" and writes it on stdout 
	with "write"  , instead "cook_buf()".

After the statement the program closs stdout and exits.
