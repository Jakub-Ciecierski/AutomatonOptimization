//
// Created by jakub on 11/24/15.
//

#include "thread_pool.h"
#include "error.h"
#include <semaphore.h>
#include <stdexcept>
#include <thread>
#include <settings/global_settings.h>
#include <logger/log.h>

ThreadPool::ThreadPool() {
    if(pthread_mutex_init(&mutex, NULL) < 0) ERR("pthread_mutex_destroy");

    numberOfCores = getNumberOfCores();
    if(numberOfCores < 1){
        numberOfCores = global_settings::DEFAULT_THREAD_COUNT;
    }
}

ThreadPool::~ThreadPool(){
    if(pthread_mutex_destroy(&mutex) < 0) ERR("pthread_mutex_destroy");

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void ThreadPool::createThread(void* (*func)(void*), void* argv){
    pthread_t thread;
    if(pthread_create(&thread, NULL, func, argv) < 0)
        ERR("pthread_create");
    threads.push_back(thread);
}

void ThreadPool::joinAll() {
    for(int i = 0; i < numberOfCores;i++){
        if (pthread_join(threads[i], NULL) != 0)
            ERR("pthread_join");
    }
    threads.clear();
}

void ThreadPool::join(unsigned int id) {
    if(id < 0 || id >= threads.size())
        throw std::invalid_argument("Index out of bound");
    if (pthread_join(threads[id], NULL) != 0)
        ERR("pthread_join");

    threads.erase(threads.begin() + id);
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

int ThreadPool::getNumberOfCores(){
    return std::thread::hardware_concurrency();
}