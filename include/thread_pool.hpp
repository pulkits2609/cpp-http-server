//thread_pool.hpp
//this will be the core model providing scalability for the server
//the thread pool will introduce a worker based architecture
//in this architecture the number of worker threads is going to scale automatically with CPU
//using : std::thread::hardware_concurrency()

// responsibilities of ThreadPool:

// create worker threads
// maintain a queue of incoming client sockets
// synchronize access to the queue
// wake workers when new connections arrive
// allow graceful shutdown of workers

// internal Components (to be implemented):

// std::vector<std::thread> workers
// std::queue<std::pair<int, sockaddr_in>> jobQueue
// std::mutex queueMutex
// std::condition_variable condition
// Router reference (shared across workers)
#pragma once

