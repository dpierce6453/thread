//
// Created by Dan on 8/5/2020.
//

#ifndef THREAD_QUEUETHREADCANNOTSTART_H
#define THREAD_QUEUETHREADCANNOTSTART_H

#include <exception>
#include <string>

class QueueThreadCannotStart : public std::exception {
public:
    virtual const char* what() const throw()
      {
        return errMsg.c_str();
      }

private:
    std::string errMsg;
public:
    void setErrMsg(const std::string &errMsg) {
        QueueThreadCannotStart::errMsg = errMsg;
    }

    QueueThreadCannotStart(const std::string &errMsg) : errMsg(errMsg) {}

    QueueThreadCannotStart() {}
};


#endif //THREAD_QUEUETHREADCANNOTSTART_H
