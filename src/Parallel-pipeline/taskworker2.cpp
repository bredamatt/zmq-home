// Task worker (round 2) in C++
// Due to difficulties with terminating the process when running taskworker

#include "zhelpers.hpp"
#include <string>

int main (int argc, char *argv[])
{

  // Create the context
  zmq::context_t context(1);

  // Create and bind the receive socket, or pull req
  zmq::socket_t receiver(context, ZMQ_PULL);
  receiver.connect("tcp://localhost:5557");

  // Create and bind the send socket. or push req
  zmq::socket_t sender(context, ZMQ_PUSH);
  sender.connect("tcp://localhost:5558");

  // Create socket for control input
  zmq::socket_t controller (context, ZMQ_SUB);
  controller.connect("tcp://localhost:5559");
  controller.setsockopt(ZMQ_SUBSCRIBE, "", 0);

  // Process messages from receiver and controller
  zmq::pollitem_t items [] = {
    { receiver, 0, ZMQ_POLLIN, 0 },
    { controller, 0, ZMQ_POLLIN, 0 }
  };

  // Process messages from both sockets using multiplex I/O
  while(1) {
    zmq::message_t message;
    zmq::poll (&items [0], 2, -1);

    if (items [0].revents & ZMQ_POLLIN) {
      receiver.recv(&message);

      // The receiver processes soem work
      int workload;

      // Create string defined as length of message
      std::string sdata(static_cast<char*>(message.data()), message.size());

      // Define a istringstream to process the message
      std::istringstream iss(sdata);
      iss >> workload;

      // Then do the work
      s_sleep(workload);

      // Rebuild and send the results to the sink
      message.rebuild();
      sender.send(message);

      // Progress indicator
      std::cout << "." << std::flush;
    }

    // Any waiting controller command acts like 'KILL'
    if (items [1].revents & ZMQ_POLLIN) {
      std::cout << std::endl;
      break;
    }
  }
  return 0;
}
