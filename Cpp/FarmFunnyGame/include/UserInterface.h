#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__

#include <condition_variable>
#include <mutex>
#include <sstream>
#include <string>

#include "Logger.h"

namespace Farm {
class UserInterface {
private:
    Farm::Logger *mLogger;
    std::istringstream *pIss;
    std::string mUserInput;
    std::mutex *pMutex;
    std::condition_variable *pCV;

public:
    UserInterface(Farm::Logger *Log, std::istringstream *Iss,
                  std::mutex *Mutex, std::condition_variable *CV);

    ~UserInterface();

    void start();
};
}; // namespace Farm

#endif /* __USER_INTERFACE_H__ */
