#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>

char const *ytdlp = "yt-dlp";
char *outputPath;

void download(char **url, char **format, char const **outputFormat) {
    system("clear");
    
    // 3 for "-o" and space
    char *output = (char *) malloc(strlen(*outputFormat) + 3 + 1);
    sprintf(output, "-o %s", *outputFormat);

    // 3 for "-P" and space
    char *tempOutputPath = malloc(strlen(outputPath) + 3);
    sprintf(tempOutputPath, "-P %s", outputPath);
    outputPath = tempOutputPath;

    // 4 for spaces between each command component
    int commandLen = strlen(ytdlp) + strlen(output) + strlen(*format) + strlen(*url) + 4 + 1;
    char *command = (char *) malloc(commandLen);
    sprintf(command, "%s %s %s %s %s", ytdlp, output, *format, *url);
    command[commandLen-1] = '\0';

    int exit_code = system(command);

    free(*url);
    free(*format);
    free(output);
    free(tempOutputPath);

    if (WEXITSTATUS(exit_code) != 0) {
        printf("\e[1m\e[31mCouldn't download the file with specified format/quality\e[0m\n");
        exit(1);
    }
    exit(0);
}

void downloadVideoAudio(char **url, char const **outputFormat) {
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
    
    download(url, &format, outputFormat);
}

void downloadVideo(char **url, char const **outputFormat) {
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

    download(url, &format, outputFormat);
}

void downloadAudio(char **url, char const **outputFormat) {
    system("clear");
    char *format = (char *) malloc(sizeof(char) * 8);
    sprintf(format, "-f \"ba\"");

    download(url, &format, outputFormat);
}

void setOutputFormat(char const **outputFormat) {
    system("clear");
    const char *outputFormats[] = {
        "\"%(title)s.%(ext)s\"",
        "\"%(uploader)s - %(title)s.%(ext)s\"",
        "\"[%(id)s] %(uploader)s - %(title)s.%(ext)s\"",
        "\"%(uploader)s (%(duration_string)s) - %(title)s.%(ext)s\"",
        "\"[%(id)s] %(uploader)s (%(duration_string)s) - %(title)s.%(ext)s\"",
    };

    const char *outputFormatsExamples[] = {
        "example.mp4",
        "John Doe - example.mp4",
        "[13231] - example.mp4",
        "John Doe (01:30:00) - example.mp4",
        "[13231] John Doe (01:30:00) - example.mp4",
    };

    int lenOutputFormats = sizeof(outputFormats)/sizeof(const char *);

    printf("\e[1m\e[33mCurrent format: %s\e[0m\n\n", *outputFormat);
    for (int i = 0; i < lenOutputFormats; i++) {
        printf("%d. \e[1m\e[34m%s\e[0m\n", i+1, outputFormats[i]);
        printf("example: %s\n", outputFormatsExamples[i]);
    }

    int userChoice;
    printf("\e[1m\e[36mSelect format: \e[0m");
    int result = scanf("%d", &userChoice);

    if (result != 1) {
        printf("\e[1m\e[31mPlease enter a valid number!\e[0m\n");
        return;
    }

    if (userChoice > 0 && userChoice <= lenOutputFormats) {
        *outputFormat = outputFormats[userChoice - 1];
    } else {
        printf("Please select the available format!\n");
    }
}

void mainMenu(char **url) {
    char const *outputFormat = "\"%(title)s.%(ext)s\"";
    while (1) {
        system("clear");

        const char *options[] = {
            "video+audio",
            "video only",
            "audio only",
            "Select Filename Format",
        };

        int len = sizeof(options)/sizeof(char *);

        for (int i = 0; i < len; i++) {
            printf("%d. \e[1m\e[34m%s\e[0m\n", i+1, options[i]);
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
            downloadVideoAudio(url, &outputFormat);
            break;
        case 2:
            downloadVideo(url, &outputFormat);
            break;
        case 3: 
            downloadAudio(url, &outputFormat);
            break;
        case 4:
            setOutputFormat(&outputFormat);
            break;
        default:
            printf("\e[1m\e[31mPlease select one of the option!\e[0m\n");
            break;
        }
        printf("\n");
    }
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
    if (argc == 1) {
        printf("USAGE:\n");
        printf("%s [OPTIONS] URL\n", argv[0]);
        printf("\n");
        printf("OPTIONS:\n");
        printf("-o DIR     Store downloaded file to DIR\n");
        return 1;
    }
    else if (argc == 2)
    {
        outputPath = "./";
    }
    else if (argc > 3)
    {
        for (int i = 1; i < argc; i++)
        {
            if (i + 1 < argc && strcmp(argv[i], "-o") == 0)
            {
                DIR* dir = opendir(argv[i + 1]);
                if (dir)
                {
                    outputPath = argv[i + 1];
                }
                else
                {
                    printf("\e[1m\e[31mCouldn't open directory!\e[0m\n");
                    exit(1);
                }
            }
        }
    }
    
    char *url;
    url = getUrl(argv);
    mainMenu(&url);

    return 0;
}