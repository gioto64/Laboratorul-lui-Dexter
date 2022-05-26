main: main.c expr.c
	gcc -DLOCAL_DEFINE -Wall -Wextra -Wshadow -Wunused -fsanitize=address,undefined,signed-integer-overflow -lm -g main.c expr.c terms.c matrix.c poly.c expr.h macros.h -o main

clean:
	rm main
