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
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));

  // Process 100 updates
  int update_nbr;
  long total_temp = 0;

  for(update_nbr = 0; update_nbr < 100; update_nbr++)
  {
    // Define message object
    zmq::message_t update;
    // Define variables to receive in message object
    int zipcode, temperature, relhumidity;
    // Receive values from subscriber
    subscriber.recv(&update);

    // Need to process the information
    std::istringstream iss(static_cast<char*>(update.data()));
    iss >> zipcode >> temperature >> relhumidity ;

    total_temp += temperature;
  }
  std::cout << "Average temperature for zipcode " << filter
            << " was " << (int) (total_temp / update_nbr) << "F"
            << std::endl;

  return 0;
}
