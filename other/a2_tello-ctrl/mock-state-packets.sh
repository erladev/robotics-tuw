echo "mocking tello state packets"
while :
do
    printf "pitch:0;roll:0;yaw:0;vgx:0;vgy0;vgz:0;templ:0;temph:0;tof:0;h:0;bat:80;baro:0.1;time:0;agx:0.0;agy:0.0;agz:0.0;\r\n" > /dev/udp/ros-desktop-full/8890 
    # | netcat -u ros-desktop-full 8890
    sleep 10
done
