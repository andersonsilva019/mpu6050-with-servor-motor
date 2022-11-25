all: app

app: main.o pwm.o
	arm-linux-gnueabihf-gcc obj/main.o obj/pwm.o -o bin/exec

main.o: src/main.c
	arm-linux-gnueabihf-gcc --static -c src/main.c -Iinc -o obj/main.o

pwm.o: src/pwm.c
	arm-linux-gnueabihf-gcc --static -c src/pwm.c -Iinc -o obj/pwm.o

run: 
	./bin/exec

clean:
	rm obj/*.o bin/exec