if [ ! $EUID -eq 0 ]
then
	echo "Please run this script with root privilege"
	exit
fi

pacman -Sy python3 ffmpeg
wget https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp
mv ./yt-dlp /usr/bin/
chmod +x /usr/bin/yt-dlp
make
mv build/ytdlpw /usr/bin/
