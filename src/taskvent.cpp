#include <zmq.hpp>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;
using namespace zmq;

#define within(num) (int) ((float) num * random() / (RAND_MAX + 1.0))

int main (int argc, char *argv[])
{
  context_t context(1);

  // Send messages from this socket:
  socket_t sender(context, ZMQ_PUSH);
  sender.bind("tcp://*:5557");

  cout << "Press Enter when workers are ready: " << endl;
  getchar();
  cout << "Sending tasks to workers... \n" << endl;

  // Need to bind the sink
  socket_t sink(context, ZMQ_PUSH);
  sink.connect("tcp://localhost:5558");
  message_t message(2);
  memcpy(message.data(), "0", 1);
  sink.send(message);

  // Random number generator initialised
  srandom((unsigned) time(NULL));

  // Send 100 tasks
  int task_nbr;
  int total_msec = 0;
  for(task_nbr = 0; task_nbr < 100; task_nbr++) {
    int workload;
    // Make the workload random from 1 to 100 msec
    workload = within(100) + 1;
    total_msec += workload;

    message.rebuild(10);
    memset(message.data(), '\0', 10);
    sprintf((char *) message.data(), "%d", workload);
    sender.send(message);
  }

    cout << "Expected cost: " << total_msec << " msec" << endl;
    sleep(1);

    return 0;
}
