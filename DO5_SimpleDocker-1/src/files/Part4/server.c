#include <stdio.h>
#include <fcgi_stdio.h>

void outoutHeaders() {
    printf("Content-type: text/html\r\n");
    printf("Status: 200 OK\r\n");
    printf("\r\n");
}

void outputContent() {
    printf("Hello World!");
}

int main() {
    while (FCGI_Accept() >= 0) {
        outputHeaders();
        outputContent();
    }
    return 0;
}