
#include <iostream>
#include <zmq.hpp>
#include <thread>
#include <chrono>

int main()
{

    zmq::context_t context(1);
   
    zmq::socket_t xpub(context, zmq::socket_type::xpub);
    xpub.bind("tcp://localhost:5556");

    zmq::socket_t xsub(context, zmq::socket_type::xsub);
    xsub.bind("tcp://localhost:5557");


    //// 비동기 리딩 함수를 이용한 노가다 구현
    while (1) {

        // publish message 리딩 및 전달
        zmq::recv_result_t check;
        int more;

        do {
            zmq::message_t pubMsg;
            
            if ((check = xpub.recv(pubMsg, zmq::recv_flags::dontwait)) > 0) {
                more = xpub.get(zmq::sockopt::rcvmore);
                xsub.send(pubMsg, more ? zmq::send_flags::sndmore : zmq::send_flags::none);
                if (!more) break;
            }
        } while (check.has_value());

        //  subscribe message 리딩 및 전달
        do {
            zmq::message_t subMsg;
            if ((check = xsub.recv(subMsg, zmq::recv_flags::dontwait)) > 0) {
                more = xpub.get(zmq::sockopt::rcvmore);
                xpub.send(subMsg, more ? zmq::send_flags::sndmore : zmq::send_flags::none);
                if (!more) break;
            }
        } while (check.has_value());

        // 아무런 동작 없을 시 지연
        std::this_thread::sleep_for(std::chrono::duration<double, std::micro>(1000));
    }



    // poller를 이용한 처리
    // poll set 초기화
   
    //std::vector<zmq::pollitem_t> pollerItems;
    //pollerItems.push_back({ xpub, 0, ZMQ_POLLIN , 0 });
    //pollerItems.push_back({ xsub, 0, ZMQ_POLLIN , 0 });
   
    //while (1) {
    //    zmq::poll(pollerItems, std::chrono::milliseconds{-1});
    //    // publish message 리딩 및 전달
    //    zmq::recv_result_t check;
    //    int more;

    //    if (pollerItems[0].revents & ZMQ_POLLIN) {
    //        while(true) {
    //            zmq::message_t pubMsg;
    //            xpub.recv(pubMsg, zmq::recv_flags::none);
    //            more = xpub.get(zmq::sockopt::rcvmore);
    //            xsub.send(pubMsg, more ? zmq::send_flags::sndmore : zmq::send_flags::none);
    //            if (!more) break;
    //        } 
    //    }

    //    if (pollerItems[1].revents & ZMQ_POLLIN) {
    //        while(true) {
    //            zmq::message_t subMsg;
    //            xsub.recv(subMsg, zmq::recv_flags::none);
    //            more = xpub.get(zmq::sockopt::rcvmore);
    //            xpub.send(subMsg, more ? zmq::send_flags::sndmore : zmq::send_flags::none);
    //            if (!more) break;
    //        }
    //    }
    //}


    // 내장 proxy 함수를 이용하는 방법
    //zmq::proxy(xpub, xsub);
}