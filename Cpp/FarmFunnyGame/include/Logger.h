#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "dlt/dlt.h"
#include <string>

namespace Farm {
class Logger {
private:
    DLT_DECLARE_CONTEXT(ctx)
public:
    /**
     * @brief Construct a new Logger object
     *
     * @param AppId
     * @param ContextId
     */
    Logger(std::string AppId, std::string ContextId);

    /**
     * @brief Destroy the Logger object
     */
    ~Logger(void);

    /**
     * @brief LogE functionality.
     *
     * @param Message
     */
    void LogE(std::string Message);

    /**
     * @brief LogI functionality.
     *
     * @param Message
     */
    void LogI(std::string Message);

    /**
     * @brief LogD functionality.
     *
     * @param Message
     */
    void LogD(std::string Message);

    /**
     * @brief LogV functionality.
     *
     * @param Message
     */
    void LogV(std::string Message);

};

}; // namespace Farm
#endif
