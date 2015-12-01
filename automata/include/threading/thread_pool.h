//
// Created by jakub on 11/24/15.
//

#ifndef AC_THREADPOOL_H
#define AC_THREADPOOL_H

#include <pthread.h>
#include <vector>

/*
 * ThreadPool creates and destroys threads.
 *
 */
namespace threading
{
    class ThreadPool {
    private:
        // The actual threads
        std::vector<pthread_t> threads;
    public:

        ThreadPool();

        ~ThreadPool();

        // Mutex to synchronize all threads
        pthread_mutex_t mutex;

        /*
         * Create a thread which is stored in vector of threads
         */
        void createThread(void *(*func)(void *), void *argv);

        /*
         * Wait for a thread with given id
         */
        void join(unsigned int id);

        /*
         * Waits for all threads in vector of threads.
         */
        void joinAll();
    };
}

#endif //AC_THREADPOOL_H
