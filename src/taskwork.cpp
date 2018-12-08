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
    socket_t receiver(context, ZMQ_PULL);
    receiver.connect("tcp://localhost:5557");

    // Socket to send messages to
    socket_t sender(context, ZMQ_PUSH);
    sender.connect("tcp://localhost:5558");
    
}
