#include <iostream>

#include <zmq.hpp>
#include <thread>
#include <chrono>

int main()
{
    

    zmq::context_t context(1);


    zmq::socket_t xrequest(context, zmq::socket_type::req);
    xrequest.connect("tcp://localhost:5006");



    while (true) {

        zmq::message_t msg(std::string("hello"));

        xrequest.send(msg, zmq::send_flags::none);


        std::cout << "send >> " << std::endl;

        zmq::recv_result_t check;
        do {
            zmq::message_t contentMsg;
            check = xrequest.recv(contentMsg, zmq::recv_flags::none);
            if (check == 0) break;

            std::string content(static_cast<char*>(contentMsg.data()), contentMsg.size());
            std::cout << "received << " << content << std::endl;

            bool more = xrequest.get(zmq::sockopt::rcvmore);
            if (!more) break;

        } while (check > 0);

        std::this_thread::sleep_for(std::chrono::duration<double, std::micro>(1000));
    }
}
