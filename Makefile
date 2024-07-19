CFLAGS = -Wall 

watch_dawg: watch_dawg.c
	gcc -o watch_dawg watch_dawg.c $(CFLAGS) `pkg-config --cflags --libs libnotify`  
