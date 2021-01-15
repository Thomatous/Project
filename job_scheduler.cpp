#include "job_scheduler.hpp"

bool start = false;
std::mutex print_mutex;
std::condition_variable cv;
std::mutex m;
std::mutex queue_mutex;

void thread_f(JobScheduler* js){
    
    // print_mutex.lock(); 
    // std::cout << "Thread " << std::this_thread::get_id() << " is waiting..." << std::endl;
    // print_mutex.unlock();

    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [] {return start;});
    }

    while(js->q->head != NULL){
        queue_mutex.lock();
        bool locked = true;
        if(js->q->head != NULL){
            Job* cj = js->q->pop();
            queue_mutex.unlock();
            locked = false;

            cj->run();
            // print_mutex.lock(); 
            std::cout  << std::this_thread::get_id() << std::endl;
            print_mutex.unlock();   
        }

        if(locked == true)
            queue_mutex.unlock();
    }

    // print_mutex.lock(); 
    // std::cout << "Thread " << std::this_thread::get_id() << " run." << std::endl;
    // print_mutex.unlock();
}

//============================================================================================================


TestJob::TestJob(unsigned int i){
    id = i;
}

void TestJob::run(){
    print_mutex.lock();
    std::cout << "Job " << id << " executed by ";
    // print_mutex.unlock();
    sleep(1);
}

//============================================================================================================

JobScheduler::JobScheduler(int n_execution_threads){
    execution_threads = n_execution_threads;
    tids = new std::thread[execution_threads];
    q = new Queue();

    for(int i = 0 ; i < execution_threads ; i++){
        tids[i] = std::thread(thread_f, this);
    }
}

void JobScheduler::execute_all_jobs(){
    start = true;
    cv.notify_all();
};

void JobScheduler::submit_job(Job* j){
    q->push_back(j);
};

void JobScheduler::wait_all_tasks_finish(){
    for(int i = 0 ; i < execution_threads ; i++) 
        tids[i].join(); 
    std::cout << "All " << execution_threads << " have terminated." << std::endl;
}
