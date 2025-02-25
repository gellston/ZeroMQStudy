
#include <iostream>
#include <thread>
#include <chrono>
#include <zmq.hpp>
#include <string>

int main()
{
    zmq::context_t context(1);
    zmq::socket_t sub(context, zmq::socket_type::sub);


    //  topic 설정 
    sub.set(zmq::sockopt::subscribe, "");
    sub.connect("tcp://localhost:5556");



    while (1) {

  
        zmq::recv_result_t check;
        do {
            zmq::message_t contentMsg;
            check = sub.recv(contentMsg, zmq::recv_flags::none);
            if (check == 0) break;

            std::string content(static_cast<char*>(contentMsg.data()), contentMsg.size());
            std::cout << "received : " << content << std::endl;

            bool more = sub.get(zmq::sockopt::rcvmore);
            if (!more) break;

        } while (check > 0);

        std::this_thread::sleep_for(std::chrono::duration<double, std::micro>(1000));
    }
}

