#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <memory>

#include "../utils/Logger.h"

void handle_client(boost::asio::ip::tcp::socket& socket){
    boost::asio::streambuf recv_buffer;
    boost::system::error_code recv_error;

    //Read data from client
    boost::asio::read_until(socket,recv_buffer,'\0',recv_error);
    if(recv_error){
        std::cout << "Error Reading Data : " << recv_error.message() << std::endl;
    }

    //Echo data back to client
    std::string message = boost::asio::buffer_cast<const char*> (recv_buffer.data());
    boost::system::error_code send_error;
    boost::asio::write(
        socket,
        boost::asio::buffer(message),
        send_error
    );
    if(send_error){
        std::cout << "Error Writing Data : " << send_error.message() << std::endl;
    }
}

int main(){
    int serv_port = 8888;
    boost::asio::io_context serv_io_context;
    boost::asio::ip::tcp::acceptor serv_acceptor(
        serv_io_context,
        boost::asio::ip::tcp::endpoint(
            boost::asio::ip::tcp::v4(),
            serv_port
        )
    );
    std::cout << "TCP Server Started \nListening on Port : " << serv_port << std::endl;

    while(true){
        boost::asio::ip::tcp::socket socket(serv_io_context);
        serv_acceptor.accept(socket);

        std::cout << "New Connection from " << 
            socket.remote_endpoint() << std::endl;

        //Handle Client
        // std::thread(
        //     handle_client,
        //     std::ref(socket)
        // ).detach();
        
        //Implement Here
        boost::asio::streambuf recv_buffer;
        boost::system::error_code recv_error;

        //Read data from client
        boost::asio::read_until(socket,recv_buffer,'\n',recv_error);
        if(recv_error){
            std::cout << "Error Reading Data : " << recv_error.message() << std::endl;
        }

        //Echo data back to client
        std::string message = boost::asio::buffer_cast<const char*> (recv_buffer.data());
        boost::system::error_code send_error;
        boost::asio::write(
            socket,
            boost::asio::buffer(message),
            send_error
        );
        if(send_error){
            std::cout << "Error Writing Data : " << send_error.message() << std::endl;
        }
    }
    return 0;
}