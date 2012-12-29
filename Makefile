all:
	gcc autosarcophagy.c -ggdb -o autosarcophagy

run: all
	./autosarcophagy

clean:
	rm -f autosarcophagy test.c test
