#include <iostream>

#include <zmq.hpp>
#include <thread>
#include <chrono>

int main()
{

    zmq::context_t context(1);


    zmq::socket_t xrequest(context, zmq::socket_type::rep);
    xrequest.connect("tcp://localhost:5007");



    while (true) {

        zmq::message_t requestMsg;
        zmq::recv_result_t check;
        do {
            zmq::message_t contentMsg;
            check = xrequest.recv(requestMsg, zmq::recv_flags::none);
            if (check == 0) break;

            std::string content(static_cast<char*>(contentMsg.data()), contentMsg.size());
            std::cout << "request << " << content << std::endl;

            bool more = xrequest.get(zmq::sockopt::rcvmore);
            if (!more) break;

        } while (check > 0);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        zmq::message_t msg(std::string("reply1 world!!"));
        xrequest.send(msg, zmq::send_flags::none);
        std::cout << "reply1 >> " << std::endl;
        std::cout << "reply complete >> " << std::endl;

        std::this_thread::sleep_for(std::chrono::duration<double, std::micro>(1000));
    }
}
