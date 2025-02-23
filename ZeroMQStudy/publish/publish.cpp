#include <zmq.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <Windows.h>

#define sleep(delay) Sleep(delay)

int main()
{
    // 퍼블리셔 준비
    zmq::context_t context(1);
    zmq::socket_t publisher(context, zmq::socket_type::pub);
    publisher.bind("tcp://*:5556");
    //publisher.bind("ipc://weather.ipc");				// Not usable on Windows.

    while (1) {


        //  subscribe로 메세지 전달
        //  메세지의 내용을 이용하여 토픽으로 필터링이 가능하다 (subscribe에서 필터링)
        //  test라는 메세지가 포함되어있기 때문에 subscribe에서 test키워드로 필터링 가능

        std::string topic = "bonghoe";
        zmq::message_t topicMessage(topic);

        std::string content = "there is no cow level";
        zmq::message_t contentMessage(content);
        
        publisher.send(topicMessage, zmq::send_flags::sndmore);
        publisher.send(contentMessage, zmq::send_flags::none);
        sleep(1);
    }
    return 0;
}

