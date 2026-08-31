#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>

#include "../networkLibrary/networkLibrary.h"
#include "../utils/Logger.h"

int main(int argc, char* argv[]){
    unsigned int port;
    try{
        if(argc != 2) throw;
        port = stoi(std::string(argv[1]));
    }
    catch(...){
        std::cout << "Incorrect Format" << std::endl;
        std::cout << "Required - <Server> <Port>" << std::endl;
        return 0;
    }
    
    boost::asio::io_context io_context;
    networkLibrary::Server::asyncServer server(io_context, port);

    std::cout << "Threads Available " << std::thread::hardware_concurrency() << std::endl;

    std::vector<std::thread> all_threads;
    for(std::size_t i=0; i<std::thread::hardware_concurrency(); ++i){
        all_threads.emplace_back(
            [&io_context](){
                io_context.run();
            }
        );
    }

    for(auto& my_thread : all_threads){
        my_thread.join();
    }

    return 0;
}