// Hello World client

#include <zmq.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace zmq;

int main ()
{
  context_t context (1);
  socket_t socket (context, ZMQ_REQ);

  cout << "Connecting to Hello World server." << endl;
  socket.connect("tcp://localhost:5555");

  // Make 10 requests
  for (int request_nbr = 0; request_nbr != 10; request_nbr++){
    message_t request(5);
    memcpy(request.data(), "Hello", 5);
    cout << "Sending Hello " << request_nbr << "..." << endl;
    socket.send (request);

    // Get a reply for each request
    message_t reply;
    socket.recv (&reply);
    cout << "Received World " << request_nbr << endl;
  }

  return 0;
}
