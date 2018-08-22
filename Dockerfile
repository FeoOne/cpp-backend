FROM centos:7
MAINTAINER Feo

RUN yum update -y

RUN yum install -y centos-release-scl && \
        yum-config-manager --enable rhel-server-rhscl-7-rpms && \
        yum install -y devtoolset-7 && \
        scl enable devtoolset-7 bash

RUN yum install -y git wget

RUN yum install -y glib-devel libsoup-devel libconfig-devel libuv-devel

RUN cd /tmp && \
        wget https://cmake.org/files/v3.12/cmake-3.12.1.tar.gz && \
        tar -xzf https://cmake.org/files/v3.12/cmake-3.12.1.tar.gz && \
        cd cmake-3.12.1 && \
        ./configure && \
        make && \
        make install && \
        cd /tmp && \
        rm cmake-3.12.1.tar.gz && \
        rm -Rf cmake-3.12.1

RUN cd /tmp && \
        git clone https://github.com/google/flatbuffers.git flatbuffers && \
        cd flatbuffers && \
        cmake -G "Unix Makefiles" && \
        make && \
        make install && \
        cd - && \
        rm -Rf /tmp/flatbuffers


