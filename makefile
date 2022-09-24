CC=gcc
all:
	$(CC) shell.c prompt.c exec.c cd.c echo.c pwd.c ls.c pinfo.c bg.c discover.c history.c jobs.c fg.c auto.c -o shell