CC=gcc
all:
	$(CC) -g shell.c prompt.c exec.c cd.c echo.c pwd.c ls.c pinfo.c bg.c discover.c history.c -o shell