FROM resin/rpi-raspbian:jessie
MAINTAINER nagama
# RUN : docker build するときに実行される
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    curl \
    wget \
    bzr \
    git \
    mercurial \
    openssh-client \
    subversion \
    procps \
    autoconf \
    automake \
    bzip2 \
    file \
    g++ \
    gcc \
    imagemagick \
    libbz2-dev \
    libc6-dev \
    libcurl4-openssl-dev \
    libevent-dev \
    libffi-dev \
    libgeoip-dev \
    libglib2.0-dev \
    libjpeg-dev \
    liblzma-dev \
    libmagickcore-dev \
    libmagickwand-dev \
    libmysqlclient-dev \
    libncurses-dev \
    libpng-dev \
    libpq-dev \
    libreadline-dev \
    libsqlite3-dev \
    libssl-dev \
    libtool \
    libwebp-dev \
    libxml2-dev \
    libxslt-dev \
    libyaml-dev \
    make \
    patch \
    xz-utils \
    zlib1g-dev \
  && rm -rf /var/lib/apt/lists/* \
  && apt-get clean

RUN apt-get update && apt-get -y install libi2c-dev\
    ruby-dev\
    libssl-dev\
    libreadline-dev\
    cmake
RUN apt-get -y install --upgrade gcc

# install wiringpi
WORKDIR /mylib
RUN git clone git://git.drogon.net/wiringPi
WORKDIR wiringPi
RUN ./build
WORKDIR /mylib

# install msgpack-c
RUN git clone https://github.com/msgpack/msgpack-c.git
WORKDIR msgpack-c
RUN cmake .
RUN make
RUN sudo make install
WORKDIR /root
WORKDIR src

# install libfluent
RUN git clone https://github.com/m-mizutani/libfluent.git
WORKDIR libfluent
RUN cmake .
RUN make
RUN sudo make install
WORKDIR /root
WORKDIR src

COPY 99-serial.rules /etc/udev/rules.d
RUN sudo /sbin/ldconfig -v

# CMD : docker run  するときに実行される
