#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>

#include "../networkLibrary/networkLibrary.h"
#include "../utils/Logger.h"

int main(int argc, char* argv[]){
    std::string IPAddress;
    unsigned int port;
    try{
        if(argc != 3) throw;
        IPAddress = argv[1];
        port = stoi(std::string(argv[2]));
    }
    catch(...){
        std::cout << "Incorrect Format" << std::endl;
        std::cout << "Required - <Client> <Server-IPAddress> <Server-Port>" << std::endl;
        return 0;
    }

    boost::asio::io_context clt_io_context;
    networkLibrary::Client::asyncClient client(clt_io_context, IPAddress, port);
    
    std::thread t([&clt_io_context](){
        clt_io_context.run();
    });

    std::string clt_input;
    while(std::getline(std::cin, clt_input)){
        if(!client.write(clt_input)) break;
    }

    t.join();

    return 0;
}