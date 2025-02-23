
#include <zmq.hpp>
#include <iostream>

int main()
{
    zmq::context_t context(1);

    //  Socket to talk to server
    std::cout << "publish 서버로 접속\n" << std::endl;
    zmq::socket_t subscriber(context, zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:5556");

    //  test 
    subscriber.set(zmq::sockopt::subscribe, "bonghoe");

    //  Process 100 updates
    int update_nbr;
    for (update_nbr = 0; update_nbr < 100; update_nbr++) {

        zmq::message_t topicMessage;
        auto topicResult = subscriber.recv(topicMessage, zmq::recv_flags::none);
        if (topicResult.has_value() && topicResult.value() > 0) {
            std::string topic(static_cast<char*>(topicMessage.data()), topicMessage.size());
            std::cout << "topic : " << topic << std::endl;
        }

        zmq::message_t contentMessage;
        auto conentResult = subscriber.recv(contentMessage, zmq::recv_flags::none);
        if (conentResult.has_value() && conentResult.value() > 0) {
            std::string content(static_cast<char*>(contentMessage.data()), contentMessage.size());
            std::cout << "content : " << content << std::endl;
        }
    }
}
