FROM ubuntu:16.04
RUN apt update && apt install gcc
WORKDIR /app/
COPY ./* ./
RUN gcc my-program.c -o program
RUN chmod +x program
