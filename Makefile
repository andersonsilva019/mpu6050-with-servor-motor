all: app

app: main.o pwm.o servo.o common.o
	arm-linux-gnueabihf-g++ obj/main.o obj/pwm.o obj/common.o obj/servo.o -o bin/exec

main.o: src/main.cpp
	arm-linux-gnueabihf-g++ --static -c src/main.cpp -Iinc -o obj/main.o

pwm.o: src/pwm.cpp
	arm-linux-gnueabihf-g++ --static -c src/pwm.cpp -Iinc -o obj/pwm.o

servo.o: src/servo.cpp
	arm-linux-gnueabihf-g++ --static -c src/servo.cpp -Iinc -o obj/servo.o

common.o: src/common.cpp
	arm-linux-gnueabihf-g++ --static -c src/common.cpp -Iinc -o obj/common.o

run: 
	./bin/exec

clean:
	rm obj/*.o bin/exec