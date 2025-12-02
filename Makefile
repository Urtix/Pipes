make:
	gcc pipes.c -o pipes

clean:
	rm -f pipes

run:
	./pipes

.PHONY: make clean run