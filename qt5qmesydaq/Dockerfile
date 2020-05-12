FROM ubuntu:18.04
ENV container docker
RUN apt-get update && \
    apt-get install -y software-properties-common && \
    rm -rf /var/lib/apt/lists/*
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test

RUN export TZ=Europe/Berlin
RUN apt-get install tzdata 
RUN apt-get install -y libgtk-3-dev pkg-config apt-utils
RUN apt-get install -y git curl unzip tar

RUN apt install -y python3-pip python3-dev
RUN pip3 install numpy
RUN pip3 install opencv-python
RUN ln -s /usr/bin/python3 /usr/bin/python

RUN apt-get install -y wget
RUN apt-get install -y libssl-dev openssl
RUN apt-get install -y gcc g++
RUN apt-get install -y cmake
RUN mv /usr/bin/cmake /usr/bin/cmake.3.10.2
RUN apt-get install -y libssl-dev
ARG cmake_ver=3.17.2

RUN cd /opt && wget https://github.com/Kitware/CMake/releases/download/v${cmake_ver}/cmake-${cmake_ver}.tar.gz && tar -zxvf ./cmake-${cmake_ver}.tar.gz
RUN cd /opt && rm ./cmake-${cmake_ver}.tar.gz
RUN cd /opt/cmake-${cmake_ver}  && ./bootstrap
RUN cd /opt/cmake-${cmake_ver}  && make
RUN cd /opt/cmake-${cmake_ver}  && make install

#<p>*****TANGO_ONLY*************</p>
RUN  apt-get install libtango-dev
RUN  apt-get install libtango9
RUN cd /opt && wget https://sourceforge.net/projects/omniorb/files/latest/download/omniORB-4.2.3.tar.bz2 && tar -xvf ./omniORB-4.2.3.tar.bz2
RUN cd /opt && cd omniORB-4.2.3 && mkdir build && cd build
RUN cd /opt/omniORB-4.2.3/build && ../configure && make && make install

#<p>**ENDE*TANGO_ONLY*************</p>


RUN git clone https://github.com/microsoft/vcpkg.git
RUN cd /vcpkg && ./bootstrap-vcpkg.sh
RUN cd /vcpkg && ./vcpkg integrate install
RUN cd /vcpkg && ./vcpkg install magic-enum
RUN cd /vcpkg && ./vcpkg install libuv

ARG boostversion=1_73_0

RUN cd /opt && wget https://dl.bintray.com/boostorg/release/$(echo ${boostversion} | sed "s/_/./g")/source/boost_${boostversion}.tar.bz2 && tar --bzip2 -xf ./boost_${boostversion}.tar.bz2
RUN cd /opt && rm  ./boost_${boostversion}.tar.bz2
RUN cd /opt/boost_${boostversion} && ./bootstrap.sh --prefix=/usr/
RUN cd /opt/boost_${boostversion} && ./b2
RUN cd /opt/boost_${boostversion} && ./b2 install

RUN apt-get install qt5-default
RUN apt-get install libqt5svg5-dev
RUN apt-get install libqt5webkit5-dev
RUN apt-get install qtwebengine5-dev


RUN apt-get install -y gcc-9 g++-9
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 700 --slave /usr/bin/g++ g++ /usr/bin/g++-7
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 900 --slave /usr/bin/g++ g++ /usr/bin/g++-9

RUN echo '#!/bin/bash' >entrypoint.sh && \
    echo 'set -e'>>entrypoint.sh && \
	echo 'if [[ $# -eq 0 ]] ; then'>>entrypoint.sh && \
	echo '   exec /bin/cat'>>entrypoint.sh && \
	echo 'fi'>>entrypoint.sh && \
	echo 'exec "$@"'>>entrypoint.sh 

RUN chmod +x ./entrypoint.sh

#USER jenkins
ARG gitdir=qt5qmesydaq
ADD https://api.github.com/repos/zweistein-frm2/${gitdir}/git/refs/heads/master version.json
RUN git clone -b master https://github.com/zweistein-frm2/${gitdir}.git ${gitdir}/


RUN cd ${gitdir} && git submodule init && git submodule update
RUN echo ${gitdir}
ARG targ1=/hiersolleshin
RUN mkdir ${targ1}
RUN cd ${targ1} && cmake -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake  -DCharm_DIR=/qt5qmesydaq/charm  -S /${gitdir}/ -B ${targ1} 
RUN cd ${targ1} && make install


USER root
ENTRYPOINT ["/entrypoint.sh"]
