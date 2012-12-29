all:
	gcc autosarcophagy.c -o autosarcophagy

run: all
	./autosarcophagy

clean:
	rm -f autosarcophagy test.c test
