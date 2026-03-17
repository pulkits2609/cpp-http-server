//thread_pool.hpp

//with this we will be shifting from accept -> handleClient (blocking sequence)
// to 
//accept -> queue -> worker thread -> handleClient (non blocking + scalable)

//the thread pool will be responsible for : 
// 1. Create worker threads
// 2. Maintain a queue of jobs (client sockets)
// 3. Synchronize access using mutex
// 4. Sleep workers when no jobs
// 5. Wake workers when jobs arrive
// 6. Stop gracefully

#pragma once

#include<iostream>
#include<vector>
#include<thread>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<arpa/inet.h>
#include<router.hpp>

class ThreadPool{
    private:
    std::vector<std::thread> workers; //worker threads vector

    //job queue where each job contains session fd and client address
    std::queue<std::pair<int, sockaddr_in>> jobQueue;

    std::mutex queueMutex; //queue mutex so that queue access is protected

    std::condition_variable cv; //condition variable for waking up worker threads

    bool stop = false; //flag to stop all threads

    Router& router; //router reference shared across all connections

    public:
    ThreadPool(size_t numThreads, Router& r); //constructor for creating worker threads

    void enqueue(int sessionfd, sockaddr_in clientAddress); //adding new job to queue

    ~ThreadPool(); //graceful shutdown
};
