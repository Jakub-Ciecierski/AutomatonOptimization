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
class ThreadPool {
private:
    // The actual threads
    std::vector<pthread_t> threads;

    /*
     * Returns the number of cores on current device.
     */
    int getNumberOfCores();

public:

    ThreadPool();

    ~ThreadPool();

    // Number of threads to create
    int numberOfCores;

    // Mutex to synchronize all threads
    pthread_mutex_t mutex;

    /*
     * Create a thread which is stored in vector of threads
     */
    void createThread(void* (*func)(void*), void* argv);

    /*
     * Wait for a thread with given id
     */
    void join(unsigned int id);

    /*
     * Waits for all threads in vector of threads.
     */
    void joinAll();
};


#endif //AC_THREADPOOL_H
