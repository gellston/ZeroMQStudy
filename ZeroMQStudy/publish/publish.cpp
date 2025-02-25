#include <zmq.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>

int main()
{
    // 퍼블리셔 준비
    zmq::context_t context(1);
    zmq::socket_t publisher(context, zmq::socket_type::pub);
    
    publisher.bind("tcp://*:5556");

    while (1) {
        //  subscribe로 메세지 전달
        //  메세지의 내용을 이용하여 토픽으로 필터링이 가능하다 (subscribe에서 필터링)

        std::string topic = "bonghoe";
        zmq::message_t topicMessage(topic);

        std::string content = "there is no cow level";
        zmq::message_t contentMessage(content);
        
        publisher.send(topicMessage, zmq::send_flags::sndmore);
        publisher.send(contentMessage, zmq::send_flags::none);
        std::this_thread::sleep_for(std::chrono::duration<double, std::nano>(1000));
    }
    return 0;
}

