FROM ubuntu:22.04
RUN apt-get update && apt-get install vim make git python3-pip -y && apt-get clean
RUN git clone https://github.com/emscripten-core/emsdk.git
RUN cd emsdk && git pull
RUN cd emsdk && ./emsdk update-tags

# to show which versions are available
#RUN cd emsdk && ./emsdk list

RUN cd emsdk && ./emsdk install 3.1.41
RUN cd emsdk && ./emsdk activate 3.1.41
