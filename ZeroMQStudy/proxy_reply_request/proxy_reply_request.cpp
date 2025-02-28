
#include <iostream>

#include <zmq.hpp>
#include <thread>
#include <chrono>

int main()
{

    zmq::context_t context(1);


    zmq::socket_t router(context, zmq::socket_type::router);
    zmq::socket_t dealer(context, zmq::socket_type::dealer);


    router.bind("tcp://*:5006");
    dealer.bind("tcp://*:5007");


    zmq::proxy(router, dealer);

}
