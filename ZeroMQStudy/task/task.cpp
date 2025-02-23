
#include <iostream>
#include <chrono>
#include <string>
#include <zmq.hpp>

#include <Windows.h>

#define sleep(delay) Sleep(delay)

int main()
{
    zmq::context_t context(1);

    //  vantilator 수신 소켓 연결
    zmq::socket_t receiver(context, ZMQ_PULL);
    receiver.connect("tcp://localhost:5557");

    //  sink 송신 소켓 연결
    zmq::socket_t sender(context, ZMQ_PUSH);
    sender.connect("tcp://localhost:5558");

    //  테스크 무한 처리
    while (1) {
        zmq::message_t requestMsg;
        receiver.recv(requestMsg, zmq::recv_flags::none);
        std::string request(static_cast<char*>(requestMsg.data()), requestMsg.size());
        std::cout << "요청된 내용 : " << request << std::endl;

        std::string result = "complete";
        zmq::message_t resultMsg(result);
        sender.send(resultMsg, zmq::send_flags::none);
    }
    return 0;

}
