#include <stdio.h>

int main(void) {
    printf("Hello, world!\n");
    
    char buffer[100];
    printf("Type something: ");
    scanf("%s", buffer);
    printf("You typed: %s\n", buffer);
    
    while (1) {}
    
    return 0;
}
