#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

const char *ytdlp = "yt-dlp";
const char *outputFormat = "-o \"%(title)s.%(ext)s\" --restrict-filenames";

void download(char **url, char **format) {
    system("clear");
    // 1 for null character
    // 3 for spaces between each command component
    int commandLen = strlen(ytdlp) + strlen(outputFormat) + strlen(*format) + strlen(*url) + 1 + 3;
    char *command = (char *) malloc(commandLen);
    sprintf(command, "%s %s %s %s", ytdlp, outputFormat, *format, *url);
    command[commandLen-1] = '\0';

    int exit_code = system(command);

    free(*url);
    free(*format);

    if (WEXITSTATUS(exit_code) != 0) {
        printf("\e[1m\e[31mCouldn't download the file with specified format/quality\e[0m\n");
        exit(1);
    }
}

void downloadVideoAudio(char **url) {
    system("clear");
    const char *quality[] = {"144", "240", "360", "480", "720", "1080", "1440", "2160", "4320"};
    unsigned long len = sizeof(quality)/sizeof(char*);
    
    for (unsigned long i = 0; i < len; i++) {
        printf("%lu. \e[1m\e[34m%sp\e[0m\n", i+1, quality[i]);
    }

    unsigned long userChoice;
    printf("\e[1m\e[36mChoose the resolution for the video: \e[0m");
    int res = scanf("%lu", &userChoice);
    if (res != 1) {
        printf("\e[1m\e[31mPlease enter a valid number!\e[0m\n");
    }

    system("clear");

    char *resolution;

    if (userChoice > 0 && userChoice < len + 1) {
        resolution = (char *) quality[userChoice-1];
    } else {
        free(*url);
        printf("\e[1m\e[31mPlease select one of available resolution!\e[0m\n");
        exit(1);
    }

    char formatString[] = "-f \"bv*[height=%s]+ba\"";
    char *format = (char *) malloc(strlen(resolution) + strlen(formatString));
    sprintf(format, formatString, resolution);
    
    download(url, &format);
}

void downloadVideo(char **url) {
    system("clear");
    const char *quality[] = {"144", "240", "360", "480", "720", "1080", "1440", "2160", "4320"};
    unsigned long len = sizeof(quality)/sizeof(char*);
    
    for (unsigned long i = 0; i < len; i++) {
        printf("%lu. %sp\n", i+1, quality[i]);
    }

    unsigned long userChoice;
    printf("\e[1m\e[36mChoose the resolution for the video: \e[0m");
    int res = scanf("%lu", &userChoice);
    if (res != 1) {
        printf("\e[1m\e[31mPlease enter a valid number!\e[0m\n");
    }

    system("clear");

    char *resolution;

    if (userChoice > 0 && userChoice < len + 1) {
        resolution = (char *) quality[userChoice-1];
    } else {
        free(*url);
        printf("\e[1m\e[31mPlease select one of available resolution!\e[0m\n");
        exit(1);
    }

    char formatString[] = "-f \"bv*[height=%s]\"";
    char *format = (char *) malloc(strlen(resolution) + strlen(formatString));
    sprintf(format, formatString, resolution);

    download(url, &format);
}

void downloadAudio(char **url) {
    system("clear");
    char *format = (char *) malloc(sizeof(char) * 8);
    sprintf(format, "-f \"ba\"");

    download(url, &format);
}

void mainMenu(char **url) {
    system("clear");
    const char *options[] = {
        "\e[1m\e[34mvideo+audio\e[0m",
        "\e[1m\e[34mvideo only\e[0m",
        "\e[1m\e[34maudio only\e[0m",
    };

    int len = sizeof(options)/sizeof(char *);

    for (int i = 0; i < len; i++) {
        printf("%d. %s\n", i+1, options[i]);
    }

    int userChoice;

    printf("\e[1m\e[36mWhich one you want to download: \e[0m");
    int result = scanf("%d", &userChoice);
    if  (result != 1) {
        printf("\e[1m\e[31mPlease enter a valid number!\e[0m\n");
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
        printf("\e[1m\e[31mPlease select one of the option!\e[0m\n");
        break;
    }
    printf("\n");
}

char *getUrl(char *argv[]) {
    char *url = argv[1];
    printf("%s\n", url);

    // 2 for ""
    // 1 for null character
    char *formattedUrl = (char *) malloc(strlen(url) + 1 + 2);
    sprintf(formattedUrl, "\"%s\"", url);
    return formattedUrl;
    
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("USAGE:\n");
        printf("%s URL\n", argv[0]);
        return 1;
    }

    char *url;
    url = getUrl(argv);
    mainMenu(&url);

    return 0;
}