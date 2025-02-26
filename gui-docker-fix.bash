XAUTH_COOKIES=$(xauth list | head -n 1 | sed 's/greater-demon\/unix:/:0/')
docker compose exec ros-desktop-full xauth add $XAUTH_COOKIES