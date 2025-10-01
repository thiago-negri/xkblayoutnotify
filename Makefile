xkblayoutnotify: xkblayoutnotify.c
	cc -std=c89 -Wall -Wpedantic -o $@ $< -lX11
