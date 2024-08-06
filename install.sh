if [ ! $EUID -eq 0 ]
then
	echo "Please run this script with root privilege"
	exit
fi

if [ -f /usr/bin/pacman ]
then
	pacman -Sy python3 ffmpeg
fi

if [ -f /usr/bin/apt ]
then
	apt update
	apt install python3 ffmpeg
fi

if [ -f /usr/bin/dnf ]
then
	dnf upgrade --refresh
	dnf install python3 ffmpeg
fi

wget https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp
mv ./yt-dlp /usr/bin/
chmod +x /usr/bin/yt-dlp
make
mv build/ytdlpw /usr/bin/
