index.js: main.c
	emcc -Wall -O3 main.c -o index.js

run:
	python3 -m http.server
