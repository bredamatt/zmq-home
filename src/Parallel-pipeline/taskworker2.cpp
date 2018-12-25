// Task worker (round 2) in C++
// Due to difficulties with terminating the process when running taskworker

#include "zhelpers.cpp"
#include <string>

int main (int argc, char *argv[])
{

  // Create the context
  zmq::context_t context(1);

  // Create the receive socket, or pull req
  zmq::socket_t receiver(context, ZMQ_PULL);
  receiver.connect("tcp://localhost:5557");

  // Create the send socket. or push req 
}
