FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

ENV TZ=Asia/Tokyo

RUN apt-get update && \
    apt-get install -y zsh time tzdata tree git curl

RUN chsh -s /bin/zsh

RUN apt-get update && \
    apt-get install -y gcc-10 g++-10 python3.8 python3-pip pypy3 nodejs npm

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 30 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 30 && \
    update-alternatives --install /usr/bin/python python /usr/bin/python3.8 30 && \
    update-alternatives --install /usr/bin/pip pip /usr/bin/pip3 30 && \
    update-alternatives --install /usr/bin/pypy pypy /usr/bin/pypy3 30 && \
    update-alternatives --install /usr/bin/node node /usr/bin/nodejs 30

RUN pip install -U pip && \
    pip install numpy==1.18.2 scipy==1.4.1 scikit-learn==0.22.2.post1 \
    numba==0.48.0 networkx==2.4

RUN git clone https://github.com/atcoder/ac-library.git /lib/ac-library
ENV CPLUS_INCLUDE_PATH /lib/ac-library

RUN pip install online-judge-tools==11.5.1

RUN curl https://sh.rustup.rs -sSf | sh -s -- -y
ENV PATH $PATH:/home/root/.cargo/bin

WORKDIR /root


