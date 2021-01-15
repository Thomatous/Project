#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <csignal>
#include <thread>
#include <mutex>

#include <dirent.h>
#include "entry.hpp"
#include "hashtable.hpp"
#include "parser.hpp"
#include "dict.hpp"
#include "logistic_regression.hpp"
#include "sparse_matrix.hpp"
#include "job_scheduler.hpp"

//global variables
sig_atomic_t signal_caught;
std::mutex cout_mutex;

//sigint signal handler
void signal_handler(int sig){
    signal_caught = 0;
}

//print to cout with mutexes
void cout_print(std::string message){
    cout_mutex.lock();
    std::cout << message << std::endl;
    cout_mutex.unlock();
}

int main() {
    signal(SIGINT, &signal_handler);    //init sigint signal handler
    std::cout << "Starting..." << std::endl;
    
    JobScheduler jb(3);

    for(int i = 0 ; i < 10 ; i++){
        TestJob* t = new TestJob(i);
        jb.submit_job(t);
    }

    jb.execute_all_jobs();
    jb.wait_all_tasks_finish();
    
    return 0;
}