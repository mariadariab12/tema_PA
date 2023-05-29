build:
	gcc -g main.c library.c queue_stack.c -lm -o lanParty
clean:
	rm -f lanParty
