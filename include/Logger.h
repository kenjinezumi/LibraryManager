#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <ctime>

/**
 * @class Logger
 * @brief Provides logging functionality for the library system.
 */
class Logger {
private:
    std::ofstream logFile;

public:
    /**
     * @brief Constructs a new Logger object.
     * @param filename The name of the log file.
     */
    Logger(const std::string& filename);

    /**
     * @brief Destroys the Logger object and closes the log file.
     */
    ~Logger();

    /**
     * @brief Logs a message to the log file with a timestamp.
     * @param message The message to log.
     */
    void log(const std::string& message);
};

#endif // LOGGER_H
