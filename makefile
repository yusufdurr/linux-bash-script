all: clean execx writef myshell 

all:
	@./myshell

execx:
	@gcc execx.c -o execx

writef:
	@gcc writef.c -o writef

myshell:
	@gcc myshell.c -lreadline -o myshell

clean:
	@rm -f execx writef myshell

