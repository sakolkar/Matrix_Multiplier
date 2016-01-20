main:
	gcc -g -Wall -o main src/main.c src/lab1_IO.c -lm -lpthread

matrixgen:
	gcc -o matrixgen src/matrixgen.c

serialtester:
	gcc -o serialtester src/serialtester.c src/lab1_IO.c

clean:
	rm main serialtester matrixgen data_input data_output
