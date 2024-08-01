#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void itoa(int num) {
    char res = (char) num;
    printf("%d\n", res+10);
    printf("%d\n", res);
}

void download() {

}

void fileToDownload() {
    char *options[] = {
        "video+audio",
        "video only",
        "audio only"
    };

    int len = sizeof(options)/sizeof(char *);

    for (int i = 0; i < len; i++) {
        printf("%d. %s\n", i+1, options[i]);
    }

    int userChoice;

    int result = scanf("%d", &userChoice);
    printf("Which one you want to download: ");
    if  (result != 1) {
        printf("Please enter a valid number!\n");
        return;
    } else if (userChoice <= 0 || userChoice > len) {
        printf("Please select one of the option!\n");
        return;
    }

    printf("\n");
    printf("%d\n", result);

    printf("%d\n", len);
}

int main(int argc, char **argv) {
    itoa(10);
    return 0;
    fileToDownload();

    if (argc != 2) {
        printf("USAGE: \n");
        printf("%s URL\n", argv[0]);
        return 1;
    }

    char command[] = "yt-dlp --list-formats ";
    char *url = argv[1];

    strcat(command, url);

    // printf("Hello, world!\n");
    system(command);
    return 0;
}