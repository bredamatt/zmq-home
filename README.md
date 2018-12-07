# zmq-home
This repository contains ZMQ examples. During XMAS 2018, the goal is to push towards improving my distributed system design and implementation skills. I decided to do so with ZMQ and by using the C++ binder cppzmq.

## How to build and run the examples
You need to install libzmq (https://github.com/zeromq/libzmq) and cppzmq (https://github.com/zeromq/cppzmq). The latter allows you to use zmq in C++ programs. It is also important to copy the header file (zmq.hpp) to your /usr/local/bin in order to compile the source code correctly. This can be done by executing the following command in a mac terminal:

1. First check your compiler version:
`$ g++ -v`

My output looks like the following:

```
Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
Apple LLVM version 10.0.0 (clang-1000.10.44.4)
Target: x86_64-apple-darwin18.0.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```

If yours does too, then navigate to the `src` directory in the repository and choose an example to compile.

2.  To compile a C++ example written using cppzmq, execute the following in the `src` directory:

`$ g++ -std=c++17 example.cpp -o example -lzmq`

This should create the binary of the "example.cpp" file.

3. To execute the binary, simply run `$ ./example`


## Conclusions
Hope the above was helpful. Now, lets go back to coding!
