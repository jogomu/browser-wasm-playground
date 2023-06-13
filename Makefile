index.js: main.c
	emcc main.c -o index.js

run:
	python3 -m http.server
