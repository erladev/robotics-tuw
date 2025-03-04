FROM osrf/ros:humble-desktop-full

RUN apt update && \
    apt upgrade -y --no-install-recommends

RUN apt install -y autogen autoconf libtool ros-humble-libg2o vim xauth

copy ./src/socket.io-client-cpp/ /tmp/socket.io-client-cpp/

RUN cd /tmp/socket.io-client-cpp && \
    mkdir -p build && cd build && \
    cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/usr/local \
        -DBUILD_UNIT_TESTS=OFF \
        .. && \
    make -j4 && \
    make install
    
copy ./src/stella_vslam/ /tmp/stella_vslam/
    
RUN cd /tmp/stella_vslam && \
    . /opt/ros/humble/setup.sh && \
    mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .. && \
    make -j6 && \
    make install

copy ./src/socket_publisher/ /tmp/socket_publisher/

RUN cd /tmp/socket_publisher && \
    . /opt/ros/humble/setup.sh && \
    mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .. && \
    make -j6 && \
    sudo make install

RUN rm -fr /tmp/*

# add ROS to bashrc
RUN echo ". /opt/ros/humble/setup.bash" >> /root/.bashrc && \
    echo "test -f /workspace/install/setup.bash && . /workspace/install/setup.bash" >> /root/.bashrc


#RUN curl -sL https://deb.nodesource.com/setup_12.x | sudo -E bash - && \
#    apt install -y nodejs
