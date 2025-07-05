build: terminal.c
	clang terminal.c -o terminal -lncurses

clean: terminal
	rm terminal
