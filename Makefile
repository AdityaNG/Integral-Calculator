run: calculator.out
	./calculator.out 

calculator.out: calculator.c
	gcc calculator.c `pkg-config gtk+-2.0 --cflags pkg-config gtk+-2.0 --libs` -o calculator.out
