# zmq-home
This repository contains ZMQ examples. During XMAS 2018, the goal is to push towards improving my distributed system design and implementation skills. I decided to do so with ZMQ and by using the C++ binding cppzmq.

## How to build and run the examples
You need to install libzmq (https://github.com/zeromq/libzmq) and cppzmq (https://github.com/zeromq/cppzmq). The latter allows you to use zmq in C++ programs. It is also important to copy the header file (zmq.hpp) to your /usr/local/bin in order to compile the source code correctly. This can be done by executing the following command in a mac terminal:

``` $ g++ -version
```

Should return
