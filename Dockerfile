FROM ubuntu:18.04
WORKDIR /app/
COPY ./* ./
RUN gcc my-program.c -o program
RUN chmod +x program
