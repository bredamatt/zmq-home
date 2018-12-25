// A parallel task worker
// Connects PULL socket to tcp://localhost:5557 (defined in taskvent.cpp)
// Collects workloards from ventilator from the above socket
// Connects PUSH socket to tcp://localhost:5558
// Sends the results to the sink via that socket

#include "zhelpers.hpp"
#include <string>

using namespace zmq;
using namespace std;

int main (int argc, char *argv[])
{
    context_t context(1);

    // Receive messages on this socket:
    socket_t receiver(context, ZMQ_PULL); // define receive with ZMQ_PULL
    receiver.connect("tcp://localhost:5557");

    // Socket to send messages to
    socket_t sender(context, ZMQ_PUSH); // define send with ZMQ_PUSH
    sender.connect("tcp://localhost:5558");

    cout << "Worker up" << endl;

    // Should always process tasks
    while (1) {

      // Serialize the message
      message_t message;
      int workload;
      receiver.recv(&message);

      // Deserialize using string and istringstream
      string smessage(static_cast<char*>(message.data()), message.size());
      istringstream iss(smessage);
      iss >> workload;

      // Do the work
      s_sleep(workload);

      // Send results to sink
      message.rebuild();
      sender.send(message);

      cout << "." << flush;
    }

    return 0;
}
