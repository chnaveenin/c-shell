#include "echo.h"

void echo(char *message) {
    int pos = allign_str(message);
    printf("%s\n", message+pos);
    return;
}
