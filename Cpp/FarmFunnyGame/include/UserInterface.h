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
    std::string mUserInput;
    std::mutex *pMutex;
public:

    std::condition_variable mCV;
    std::istringstream mIss;

    UserInterface(std::mutex *Mutex);

    ~UserInterface();

    void start();
};
}; // namespace Farm

#endif /* __USER_INTERFACE_H__ */
