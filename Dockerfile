FROM gcc:4.8
WORKDIR /opt/fireworks/
COPY fireworks.cpp fireworks.cpp
RUN ["gcc", "-Wno-deprecated-declarations", "fireworks.cpp", "-o", "fireworks", "-lGL", "-lGLU", "-lglut"];
CMD ["./fireworks"]
