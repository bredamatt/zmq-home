#include <zmq.hpp>
#include <iostream>
#include <sstream>

int main (int argc, char *argv[])
{
  zmq::context_t context(1);

  // Socket should talk to the server
  std::cout <<"Collecting updates from weather server... \n" << std::endl;
  zmq::socket_t subscriber(context, ZMQ_SUB);
  subscriber.connect("tcp://localhost::556");

  // Subscribe to zipcode, if none, set NYC ZIP as default 
  const char *filter = (argc >1) ? argv[1]: "10001 ";


}
