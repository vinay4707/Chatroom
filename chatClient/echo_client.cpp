#include "../utils/Logger.h"

#include <iostream>
#include <boost/asio.hpp>

int main(){
    boost::asio::io_context clt_io_context;
    
    //socket
    boost::asio::ip::tcp::socket clt_socket(clt_io_context);
    boost::asio::ip::tcp::resolver clt_resolver(clt_io_context);

    //connect
    boost::asio::connect(
        clt_socket,
        clt_resolver.resolve("127.0.0.1","8888")
    );

    //wrtie to server
    std::string send_data("Hello From Client\n");
    int size_sent = boost::asio::write(
        clt_socket,
        boost::asio::buffer(send_data)
    );

    std::cout << "Data Sent : " << "/" << size_sent << send_data.length() << std::endl;

    //read from server
    boost::asio::streambuf recv_buffer;
    boost::system::error_code recv_error;
    boost::asio::read_until(clt_socket,recv_buffer,'\n',recv_error);
    if(recv_error){
        std::cout << "Error Reading Data : " << recv_error.message() << std::endl;
    }
    else{
        std::string message = boost::asio::buffer_cast<const char*> (recv_buffer.data());
        std::cout << message << std::endl;
    }
    boost::system::error_code clt_error;
    clt_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, clt_error);
    clt_socket.close();
    return 0;
}



