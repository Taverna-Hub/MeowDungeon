all:
	gcc ./src/*.c -I./include -o MeowDungeon.out -lm

run:
	./MeowDungeon.out

clean:
	rm MeowDungeon.out