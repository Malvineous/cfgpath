.PHONY: all check clean

all: test-linux test-win test-macos

check: test-linux test-win test-macos
	./test-linux
	./test-win
	./test-macos

clean:
	rm -f test-linux test-win test-macos

test-linux: test-linux.c cfgpath.h
	$(CC) -O0 -g -o $@ $<

test-win: test-win.c cfgpath.h shlobj.h
	$(CC) -O0 -g -o $@ $< -I.

test-macos: test-macos.c cfgpath.h
	$(CC) -O0 -g -o $@ $<
