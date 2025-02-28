// request.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include <zmq.hpp>
#include <thread>
#include <chrono>

int main()
{
    //  Context 및 소켓 준비
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::req);

    std::cout << "Connecting to hello world server..." << std::endl;
    socket.connect("tcp://localhost:5555");

    // 10번 반복
    for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
        std::string request_context = "Hello!!!";
        zmq::message_t request(request_context);
        std::cout << "Sending Hello " << request_nbr << "..." << std::endl;
        auto send_result = socket.send(request, zmq::send_flags::none);


        std::this_thread::sleep_for(std::chrono::duration<double, std::micro>(1000));
     
        
        //  Get the reply.
        zmq::message_t reply;
        auto result = socket.recv(reply, zmq::recv_flags::none);
        std::cout << "Received World " << request_nbr << std::endl;


    }
}

