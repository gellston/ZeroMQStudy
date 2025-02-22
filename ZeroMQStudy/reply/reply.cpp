// reply.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include <zmq.hpp>
#include <Windows.h>
#include <string>

#define sleep(n)	Sleep(n)

int main()
{
    // 소켓 컨텍스트 준비
    zmq::context_t context(2);
    zmq::socket_t socket(context, zmq::socket_type::rep);
    socket.bind("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        //  클라이언트 응답 기다림
        socket.recv(request, zmq::recv_flags::none);
        std::cout << "Received Hello" << std::endl;

        //  작업
        sleep(1);

        // 클라이언트로 응답
        std::string temp = "world!!";
        zmq::message_t reply(temp);
        socket.send(reply, zmq::send_flags::none);
    }
}
