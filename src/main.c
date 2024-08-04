#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

const char *ytdlp = "yt-dlp";
const char *outputFormat = "-o \"%(title)s.%(ext)s\" --restrict-filenames";

void download(char **url, char **format) {
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
        printf("Couldn't download the file with specified format/quality\n");
        exit(1);
    }
}

void downloadVideoAudio(char **url) {
    const char *quality[] = {"144", "240", "360", "480", "720", "1080", "1440", "2160", "4320"};
    unsigned long len = sizeof(quality)/sizeof(char*);
    
    for (unsigned long i = 0; i < len; i++) {
        printf("%lu. %sp\n", i+1, quality[i]);
    }

    unsigned long userChoice;
    printf("Choose the resolution for the video: ");
    int res = scanf("%lu", &userChoice);
    if (res != 1) {
        printf("Please enter a valid number!\n");
    }

    char *resolution;

    if (userChoice > 0 && userChoice < len + 1) {
        resolution = (char *) quality[userChoice-1];
    } else {
        free(*url);
        printf("Please select one of available resolution!\n");
        exit(1);
    }

    char formatString[] = "-f \"bv*[height=%s]+ba\"";
    char *format = (char *) malloc(strlen(resolution) + strlen(formatString));
    sprintf(format, formatString, resolution);
    
    download(url, &format);
}

void downloadVideo(char **url) {
    const char *quality[] = {"144", "240", "360", "480", "720", "1080", "1440", "2160", "4320"};
    unsigned long len = sizeof(quality)/sizeof(char*);
    
    for (unsigned long i = 0; i < len; i++) {
        printf("%lu. %sp\n", i+1, quality[i]);
    }

    unsigned long userChoice;
    printf("Choose the resolution for the video: ");
    int res = scanf("%lu", &userChoice);
    if (res != 1) {
        printf("Please enter a valid number!\n");
    }

    char *resolution;

    if (userChoice > 0 && userChoice < len + 1) {
        resolution = (char *) quality[userChoice-1];
    } else {
        free(*url);
        printf("Please select one of available resolution!\n");
        exit(1);
    }

    char formatString[] = "-f \"bv*[height=%s]\"";
    char *format = (char *) malloc(strlen(resolution) + strlen(formatString));
    sprintf(format, formatString, resolution);

    download(url, &format);
}

void downloadAudio(char **url) {
    char *format = (char *) malloc(sizeof(char) * 8);
    sprintf(format, "-f \"ba\"");

    download(url, &format);
}

void mainMenu(char **url) {
    const char *options[] = {
        "video+audio",
        "video only",
        "audio only"
    };

    int len = sizeof(options)/sizeof(char *);

    for (int i = 0; i < len; i++) {
        printf("%d. %s\n", i+1, options[i]);
    }

    int userChoice;

    printf("Which one you want to download: ");
    int result = scanf("%d", &userChoice);
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
    printf("%s\n", url);
    mainMenu(&url);

    return 0;
}