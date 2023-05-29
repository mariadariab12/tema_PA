build:
	gcc -g main.c library.c queue_stack.c task1.c task2.c task3.c task4.c task5.c -lm -o lanParty
clean:
	rm -f lanParty
