all:	shell2.exe
shell2.exe:	shell2.o
			gcc -o shell2.exe shell2.o
shell2.o:	shell2.c
			gcc -c shell2.c
clean:
			rm shell2.o	shell2.exe
			