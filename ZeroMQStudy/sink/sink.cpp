
#include <zmq.hpp>
#include <string>
#include <time.h>
#include <iostream>

int main()
{
 
    zmq::context_t context(1);
    zmq::socket_t receiver(context, ZMQ_PULL);
    receiver.bind("tcp://*:5558");

    while (true) {
        zmq::message_t resultMsg;
        receiver.recv(resultMsg);

        std::string result(static_cast<char*>(resultMsg.data()), resultMsg.size());

        std::cout << "완료된 내용 : " << result << std::endl;
    }



    return 0;
}
