#ifndef NETWORK_LIBRARY_H
#define NETWORK_LIBRARY_H


#include "../utils/Logger.h"
#include <iostream>
#include <string>
#include <set>
#include <memory>
#include <mutex>

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

/**
 * @brief The main namespace for the network library.
 */

namespace networkLibrary
{
    /**
     * @brief Represents a chat session between a server and a client.
     * 
     * To be used only on Server. Any reading is done on the Chat Session, 
     * which then translates it to the server class.
     * 
     * The chat session does not implement write operation.
     */
    class chatSession;

    /**
     * @brief Namespace containing server-related classes.
     */
    namespace Server
    {
        /**
         * @brief An Asynchronous Server class for handling multiple chat sessions.
         * 
         * This Asynchronous Server accepts the message from read operation of chat session,
         * and is responsible to implement logic and send message to whichsoever client. 
         */
        class asyncServer;
    };

    /**
     * @brief Namespace containing client-related classes.
     */
    namespace Client
    {
        /**
         * @brief An asynchronous client class for connecting to the server.
         */
        class asyncClient;
    };
};

/**
 * @brief Asynchronous server class for handling chat sessions and sending message.
 */
class networkLibrary::Server::asyncServer
{
private:
    unsigned int m_port; ///< Port number the server listens on.
    boost::asio::io_context &m_io_context; ///< Reference to the IO context.
    boost::asio::ip::tcp::acceptor m_acceptor; ///< Acceptor object for accepting new connections.
    std::set<std::shared_ptr<chatSession>> m_chat_sessions; ///< Set of active chat sessions.
    std::mutex _server_mutex; ///< Mutex for thread-safe operations on the set of chat essions.
    Logger server_log;

    /**
     * @brief Starts accepting new chat sessions.
     */
    void startAccept();

    /**
     * @brief Parses a message into a pair of strings.
     * @param[in,out] message The message to parse.
     * @return A pair containing the parsed data.
     */
    std::pair<std::string, std::string> parse(std::string &message);

    /**
     * @brief Adds a new chat session to the server.
     * @param session Shared Pointer to the chat session to add.
     */
    void add_session(const std::shared_ptr<networkLibrary::chatSession> session);

    /**
     * @brief Removes a chat session from the server.
     * @param session Shared Pointer to the chat session to remove.
     */
    void remove_session(const std::shared_ptr<networkLibrary::chatSession> session);

public:

    friend class networkLibrary::chatSession;

    /**
     * @brief Constructs an asynchronous server.
     * @param io_context The IO context used for asynchronous operations.
     * @param port The port number on which the server will listen.
     */
    asyncServer(boost::asio::io_context &io_context, unsigned int port);

    /**
     * @brief Broadcasts a message to all connected chat sessions.
     * @param message The message to broadcast.
     */
    void write_broadcast(std::string message);

    /**
     * @brief Sends a message to a specific chat session.
     * @param session Shared Pointer to the chat session to send the message to.
     * @param message The message to send.
     */
    void write(const std::shared_ptr<networkLibrary::chatSession> session, std::string message);

    /**
     * @brief Sends a buffer to a specific chat session.
     * @param session Shared Pointer to the chat session to send the buffer to.
     * @param buffer The buffer to send.
     */
    void write(const std::shared_ptr<networkLibrary::chatSession> session, boost::asio::mutable_buffers_1 buffer);
};

/**
 * @brief Asynchronous client class for connecting to the chat server.
 */
class networkLibrary::Client::asyncClient
{
private:
    boost::asio::io_context &m_io_context; ///< Reference to the IO context.
    std::string m_ip; ///< Server IP address.
    unsigned int m_port; ///< Server port number.
    boost::asio::ip::tcp::socket m_socket; ///< Socket for communication with the server.
    boost::asio::ip::tcp::resolver m_resolver; ///< Resolver for determining server address.
    std::string m_buffer; ///< Buffer for storing received data.

    /**
     * @brief Continuously reads data from the server.
     */
    void read_continous();

public:
    std::string m_username; ///< Username of the client.

    /**
     * @brief Constructs an asynchronous client.
     * @param io_context The IO context used for asynchronous operations.
     * @param ip The IP address of the server.
     * @param port The port number of the server.
     */
    asyncClient(boost::asio::io_context &io_context, std::string ip, unsigned int port);

    /**
     * @brief Sends a message to the server.
     * @param message The message to send.
     * @return True if the message was successfully sent, false otherwise.
     */
    bool write(std::string &message);

    /**
     * @brief Immediately sends a message to the server.
     * @param message The message to send.
     * @return True if the message was successfully sent, false otherwise.
     */
    bool write_now(std::string message);

    /**
     * @brief Closes the connection to the server.
     */
    void close_connection();

    /**
     * @brief Destructor for the asynchronous client.
     */
    ~asyncClient();
};

/**
 * @brief Represents a chat session between a server and a client.
 */
class networkLibrary::chatSession : public std::enable_shared_from_this<networkLibrary::chatSession>
{
private:
    networkLibrary::Server::asyncServer &m_serv; ///< Reference to the associated server.
    // std::string m_buffer; ///< Buffer for storing received data.
    boost::asio::ip::tcp::socket m_socket; ///< Socket for communication.
    std::string m_ip; ///< Client's IP address.
    unsigned int m_port; ///< Client's port number.

public:

    friend class networkLibrary::Server::asyncServer;

    std::string m_name; ///< Name of the chat participant.

    /**
     * @brief Constructs a chat session.
     * @param socket The socket used for the chat session.
     * @param serv The server managing the session.
     */
    chatSession(boost::asio::ip::tcp::socket socket, networkLibrary::Server::asyncServer &serv);

    /**
     * @brief Destructor for the chat session.
     */
    ~chatSession();

    /**
     * @brief Starts the chat session.
     */
    void start();

    /**
     * @brief Continuously reads data from the client.
     */
    void read_continous();
};

#endif