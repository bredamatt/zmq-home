// Task sink C++
// Binds PULL socket to tcp://localhost:5558
// Collects results from workers via the above socket

#include <zmq.hpp>
#include <time.h>
#include <sys/time.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[])
{

  // Prep context and seocket
  zmq::context_t context(1);
  zmq::socket_t receiver(context, ZMQ_PULL);
  receiver.bind("tcp://*:5558");

  // Wait for start of batch
  zmq::message_t message;
  receiver.recv(&message);

  // Start time now
  struct timeval tstart;
  gettimeofday(&tstart, NULL);

  // Process 100 confirmations
  int task_nbr;
  int total_msec = 0; // The total cost that becomes calculated
  for (task_nbr = 0; task_nbr < 100; task_nbr++){

    receiver.recv(&message);
    if (task_nbr % 10 == 0){
      cout << ":" << flush;
    } else {
      cout << "." << flush;
    }
  }

  // Record time again
  struct timeval tend, tdiff;
  gettimeofday(&tend, NULL);

  // Checking if first time reg. is greater, or less than the second 
  if (tend.tv_usec < tstart.tv_usec) {
    tdiff.tv_sec = tend.tv_sec - tstart.tv_sec - 1;
    tdiff.tv_usec = 1000000 + tend.tv_usec - tstart.tv_usec;
  }
  else {
    tdiff.tv_sec = tend.tv_sec - tstart.tv_sec;
    tdiff.tv_usec = tend.tv_usec - tstart.tv_usec;
  }

  total_msec = tdiff.tv_sec * 1000 + tdiff.tv_usec / 1000;
  cout  << "\nTotal elapsed time: " << total_msec << " msec\n" << endl;

  return 0;
}
