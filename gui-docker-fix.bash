XAUTH_COOKIES=$(xauth list | head -n 1 | sed -E 's/.+\sMIT-/:0 MIT-/')
echo $(xauth list | head -n 1)
echo $XAUTH_COOKIES
podman-compose exec ros-desktop-full bash -c "touch /root/.Xauthority && xauth add $XAUTH_COOKIES && echo 'setup ok'"
