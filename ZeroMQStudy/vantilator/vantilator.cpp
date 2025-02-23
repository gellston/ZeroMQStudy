

#include <zmq.hpp>
#include <iostream>
#include <chrono>
#include <Windows.h>

#define sleep(delay) Sleep(delay)

int main()
{
    zmq::context_t context(1);

    //  Socket to send messages on
    zmq::socket_t  sender(context, ZMQ_PUSH);
    sender.bind("tcp://*:5557");

    std::cout << "작업 분배 시작: " << std::endl;

    //  sink에 스타드 신호 주기
    zmq::socket_t sink(context, ZMQ_PUSH);
    sink.connect("tcp://localhost:5558");


    std::string startSig = "startSink";
    zmq::message_t startSigMsg(startSig);
    sink.send(startSigMsg, zmq::send_flags::none);

    //  100개 작업 요청
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int task_nbr = 0; task_nbr < 100; task_nbr++) {
        std::string task = "there is no cow level";
        zmq::message_t taskMessage(task);
        sender.send(taskMessage, zmq::send_flags::none);

        sleep(1);
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    
    auto elapseTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "테스트 요청이 걸린 시간" << elapseTime.count() << std::endl;

    

    return 0;
}

