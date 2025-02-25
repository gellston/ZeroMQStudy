
#include <iostream>
#include <thread>
#include <chrono>
#include <zmq.hpp>
#include <string>

int main()
{

    zmq::context_t context(1);
    zmq::socket_t pub(context, zmq::socket_type::pub);

    pub.connect("tcp://localhost:5557");
    while (1) {

        std::string topic = "bonghoe";
        zmq::message_t topicMsg(topic);


        std::string content = "there is no cow level";
        zmq::message_t contentMsg(content);

        pub.send(topicMsg, zmq::send_flags::sndmore);
        pub.send(contentMsg, zmq::send_flags::none);

        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1000));
    }
}
