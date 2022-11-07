FROM ubuntu:20.04
RUN apt update
RUN apt install qt5-qmake -y
RUN apt install cmake -y
RUN apt-get install qt5-default -y
RUN apt install build-essential -y
COPY . /home/server
WORKDIR /home/server/untitled9
RUN qmake untitled.pro
RUN make
RUN make install
CMD ["./untitled"]
