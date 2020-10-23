# Create a virtual environment with all tools installed
# ref: https://hub.docker.com/_/ubuntu
FROM ubuntu:rolling AS env
LABEL maintainer="mizux.dev@gmail.com"
# Install system build dependencies
ENV PATH=/usr/local/bin:$PATH
RUN apt-get update -q \
&& DEBIAN_FRONTEND=noninteractive apt-get install -yq git wget build-essential \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Install CMake 3.18.4
RUN wget "https://cmake.org/files/v3.18/cmake-3.18.4-Linux-x86_64.sh" \
&& chmod a+x cmake-3.18.4-Linux-x86_64.sh \
&& ./cmake-3.18.4-Linux-x86_64.sh --prefix=/usr/local/ --skip-license \
&& rm cmake-3.18.4-Linux-x86_64.sh
CMD [ "/bin/sh" ]

FROM env AS devel
WORKDIR /home/project
COPY . .

RUN cmake -version
RUN cmake -S. -Bbuild
RUN cmake --build build --target all -v
RUN cmake --build build --target install -v

FROM devel AS test
RUN cmake --build build --target test

FROM env AS install
COPY --from=devel /usr/local /usr/local/

WORKDIR /home/sample
COPY ci/sample .

RUN cmake -S. -Bbuild
RUN cmake --build build --target all -v
RUN cmake --build build --target test
