#include<thread_pool.hpp>
#include<connection.hpp>

ThreadPool::ThreadPool(size_t numThreads, Router& r) : router(r){ //initialize router using member initializer because it can only be initilized at object construction

    //create worker threads
    for(size_t i=0;i<numThreads;i++){
        workers.emplace_back([this](){ //this means that thread can access : jobQueue, queueMutex, cv, stop, router

            while(true){ //infinite loop, thread waits for work forever

                std::pair<int, sockaddr_in> job;

                {
                    std::unique_lock<std::mutex> lock(queueMutex);

                    //wait until job available or stop signal
                    cv.wait(lock, [this](){
                        return !jobQueue.empty() || stop;
                    });

                    //if stopping and no jobs left -> exit thread
                    if(stop && jobQueue.empty()){
                        return;
                    }

                    //get job
                    job = jobQueue.front();
                    jobQueue.pop();
                }

                //process job outside lock
                ClientConnection conn(router);
                conn.getClientSession(job.first);
                conn.getClientAddress(job.second);
                conn.handleClient();
            }
        });
    }
}

void ThreadPool::enqueue(int sessionfd, sockaddr_in clientAddress){

    {
        std::lock_guard<std::mutex> lock(queueMutex);
        jobQueue.push({sessionfd, clientAddress});
    }

    //wake one worker
    cv.notify_one();
}

ThreadPool::~ThreadPool(){
    std::lock_guard<std::mutex> lock(queueMutex);
    stop = true;
    cv.notify_all(); //wake all workers

    //join all threads
    for(auto& t : workers){
        if(t.joinable()){
            t.join();
        }
    }
}