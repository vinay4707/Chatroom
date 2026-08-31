#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>   // for including ofstream
#include <string>    // for dealing with names
#include <ctime>     // for writing time 
#include <mutex>     // for mutex lock handling 
#include <thread>    // for thread handling 

/**
 * @brief A class for logging messages to different locations such as text files or databases.
 *
 * The Logger class provides functionality to log messages to various locations depending on the configuration.
 */

class Logger {
public:
    /**
     * @brief Enum representing the possible logging locations.
     */
    enum Location {
        DISABLED,   ///< Logging is disabled.
        TEXT_FILE,  ///< Log messages to a text file.
        STDOUT    ///< Log messages to terminal.
    };

private:
    std::mutex m_mutex;             ///< Mutex Lock 
    const std::string m_FileName;   ///< The name of the file where logs will be written.
    std::ofstream m_OutStream;      ///< Output stream for writing to the log file.
    const Location m_Location;      ///< The location where logs should be written.

    /**
     * @brief Initializes the logger based on the specified location.
     * @return True if initialization was successful, false otherwise.
     */
    bool init();

protected:
    std::string m_ClassName;  ///< The name of the class, intended for use by derived classes.

public:
    /**
     * @brief Default constructor that initializes the logger with logging disabled.
     */
    Logger();

    /**
     * @brief Constructor that initializes the logger with the specified logging location.
     * @param loc The location where logs should be written.
     */
    Logger(const Location loc);

    /**
     * @brief Constructor that initializes the logger with a file name and logging location.
     * @param loc The location where logs should be written.
     * @param fileName The name of the file where logs will be written.
     */
    Logger(const Location loc, const std::string fileName);

    /**
     * @brief Copy constructor is deleted to prevent copying of the logger.
     */
    Logger(const Logger &) = delete;

    /**
     * @brief Destructor that cleans up resources used by the logger.
     */
    ~Logger();

    /**
     * @brief Logs an empty string.
     * @return True if the log was successful, false otherwise.
     */
    bool log();

    /**
     * @brief Logs a specific message.
     * @param message The message to be logged.
     * @return True if the log was successful, false otherwise.
     */
    bool log(const std::string &message);

    /**
     * @brief Logs multiple messages provided in an initializer list.
     * @param messages The list of messages to be logged.
     * @return True if the log was successful, false otherwise.
     */
    bool log(const std::initializer_list<std::string> &messages, std::string);
};

#endif // LOGGER_H
