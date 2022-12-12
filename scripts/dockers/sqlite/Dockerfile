from ubuntu:22.04
MAINTAINER "dobigthing"

ENV DEBIAN_FRONTEND noninteractive

# common config
RUN apt-get update
RUN apt-get -y install make cmake build-essential vim sudo git -y tcl8.6 tcl8.6-tdbc-sqlite3\
    clang libmysqlclient-dev ninja-build pkg-config clang-format \
    libpq-dev libyaml-cpp-dev lld

RUN mkdir -p /home && \
    groupadd dobigthing && \
    useradd -l -K UMASK=0000 -d /home -g dobigthing dobigthing && \
    chown dobigthing:dobigthing /home

RUN	echo "dobigthing:dobigthing" | chpasswd && usermod -a -G sudo dobigthing
RUN chmod +w /etc/sudoers && \
    echo "%dobigthing   ALL=(ALL:ALL)NOPASSWD:ALL" >> /etc/sudoers && \
    chmod -w /etc/sudoers


RUN apt-get -y install apt-transport-https curl software-properties-common gnutls-dev
RUN curl -o /etc/apt/trusted.gpg.d/mariadb_release_signing_key.asc \
    'https://mariadb.org/mariadb_release_signing_key.asc'
RUN echo "deb https://ftp.osuosl.org/pub/mariadb/repo/10.10/ubuntu jammy main" >> /etc/apt/sources.list
RUN echo "deb-src https://ftp.osuosl.org/pub/mariadb/repo/10.10/ubuntu jammy main" >> /etc/apt/sources.list
RUN apt-get update && apt-get -y build-dep mariadb

USER dobigthing
WORKDIR /home

RUN git clone https://github.com/s3team/Squirrel.git && \
    cd Squirrel && git submodule update --init && \
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build -j && \
    cd AFLplusplus/ && LLVM_CONFIG=llvm-config-14 make -j20

RUN git clone https://github.com/sqlite/sqlite sqlite/ && \
    mkdir bld/ && cd bld/ && \
    CC=/home/Squirrel/AFLplusplus/afl-clang-lto CXX=/home/Squirrel/AFLplusplus/afl-clang-lto++ \
    ../sqlite/configure && make -j && make sqlite3.c && sudo make install

ENTRYPOINT bash