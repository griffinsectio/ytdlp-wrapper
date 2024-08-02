#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

const char *ytdlp = "yt-dlp";
const char *outputFormat = "-o \"%(title)s.%(ext)s\" --restrict-filenames";

void download(char *url, char *format) {
    int commandLen = strlen(ytdlp) + strlen(outputFormat) + strlen(format) + strlen(url) + 1;
    char *command = (char *) malloc(commandLen);
    sprintf(command, "%s %s %s %s", ytdlp, outputFormat, format, url);
    command[commandLen-1] = '\0';

    int exit_code = system(command);

    if (WEXITSTATUS(exit_code) != 0) {
        printf("Couldn't download the file with specified format/quality\n");
        exit(1);
        // download(url, format);
    }
}

void downloadVideoAudio(char *url) {
    char quality[9][5] = {"144", "240", "360", "480", "720", "1080", "1440", "2160", "4320"};
    unsigned long len = sizeof(quality)/sizeof(char*);
    
    for (unsigned long i = 0; i < len; i++) {
        printf("%lu. %sp\n", i+1, quality[i]);
    }

    unsigned long userChoice;
    int res = scanf("%lu", &userChoice);
    if (res != 1) {
        printf("Please enter a valid number!\n");
    }

    char *resolution = (char *)malloc(6 * sizeof(char));

    if (userChoice > 0 && userChoice < len + 1) {
        resolution = quality[userChoice-1];
    } else {
        printf("Please select one of available resolution!\n");
        exit(1);
    }

    char formatString[] = "-f \"bv*[height<=%s]+ba\"";
    char *format = (char *) malloc(strlen(resolution) + strlen(formatString));
    sprintf(format, formatString, resolution);
    
    download(url, format);

}

void downloadVideo(char *url) {
    char quality[9][5] = {"144", "240", "360", "480", "720", "1080", "1440", "2160", "4320"};
    unsigned long len = sizeof(quality)/sizeof(char*);
    
    for (unsigned long i = 0; i < len; i++) {
        printf("%lu. %sp\n", i+1, quality[i]);
    }

    unsigned long userChoice;
    int res = scanf("%lu", &userChoice);
    if (res != 1) {
        printf("Please enter a valid number!\n");
    }

    char *resolution = (char *)malloc(6 * sizeof(char));

    if (userChoice > 0 && userChoice < len + 1) {
        resolution = quality[userChoice-1];
    } else {
        printf("Please select one of available resolution!\n");
        exit(1);
    }

    char formatString[] = "-f \"bv*[height=%s]\"";
    char *format = (char *) malloc(strlen(resolution) + strlen(formatString));
    sprintf(format, formatString, resolution);
    
    download(url, format);
}

void downloadAudio(char * url) {
    char format[] = "-f \"ba\"";
    download(url, format);
}

void mainMenu(char * url) {
    char options[3][12] = {
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
    }

    switch (userChoice)
    {
    case 1:
        downloadVideoAudio(url);
        break;
    case 2:
        downloadVideo(url);
        break;
    case 3: 
        downloadAudio(url);
        break;
    default:
        printf("Please select one of the option!\n");
        break;
    }
    printf("\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("USAGE:\n%s URL\n", argv[0]);
        return 1;
    }

    char *url = argv[1];
    mainMenu(url);

    return 0;
}