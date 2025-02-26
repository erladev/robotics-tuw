FROM ros-desktop-custom:latest

RUN apt update && \
    apt upgrade -y --no-install-recommends

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

RUN rm -fr /tmp/*

copy ./src/socket_publisher/ /tmp/socket_publisher/

RUN cd /tmp/socket_publisher && \
    . /opt/ros/humble/setup.sh && \
    mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .. && \
    make -j6 && \
    sudo make install

RUN rm -fr /tmp/*

RUN apt install xauth

# TODO somehow it was already installed ._.

#RUN curl -sL https://deb.nodesource.com/setup_12.x | sudo -E bash - && \
#    apt install -y nodejs
