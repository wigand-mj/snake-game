#include "Io.h"

#ifdef _WIN32

#include <windows.h>
#include <conio.h>

void io_init() {

}

void io_clear() {
	system("CLS");
}

char io_read_key(int timeout_ms) {
	Sleep(timeout_ms);
	if (!_kbhit()) 
		return 0;
	return _getch();
}

#else

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

void io_init() {
	struct termios tio;
	tcgetattr(STDIN_FILENO, &tio);
	tio.c_lflag &= (~ICANON & ~ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}

void io_clear() {
	printf("\x1B[2J\x1B[0;0f");
}

char io_read_key(int timeout_ms) {
	struct timeval tv = { 0L, timeout_ms * 1000L };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	int r = select(1, &fds, NULL, NULL, &tv);
	if (!r) return 0;

	return getchar();
}

#endif