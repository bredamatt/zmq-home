#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n) Sleep(n)
#endif

using namespace zmq;
using namespace std;

int main() {
  context_t context(1);
  socket_t socket(context, ZMQ_REP);
  socket.bind("tcp://*:5555");

  while (true) {
    message_t request;

    socket.recv(&request);
    cout << "Received Hello" << endl;

    sleep(5);

    message_t reply(5);
    memcpy(reply.data(), "World", 5);
    socket.send(reply);
  }
  return 0;
}
