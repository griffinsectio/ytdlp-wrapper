# ytdlpw: ytdlpw.o
# 	gcc ./src/ytdlpw.o -o ./build/ytdlpw

# ytdlpw.o: ./src/main.c
# 	gcc -c ./src/main.c -o ./src/ytdlpw.o

ytdlpw: ./src/main.c
	gcc ./src/main.c -o ./build/ytdlpw