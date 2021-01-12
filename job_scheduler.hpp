#ifndef _JOB_SCHEDULER_
#define _JOB_SCHEDULER_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <csignal>
#include <thread>
#include <mutex>
#include <pthread.h>
#include <dirent.h>
#include "entry.hpp"
#include "hashtable.hpp"
#include "parser.hpp"
#include "dict.hpp"
#include "logistic_regression.hpp"
#include "sparse_matrix.hpp"

class Job{
public:
    virtual void run() = 0;
    virtual ~Job() { }
};

class vectorify_Job : public Job{
private:
    Dict *all_words;
    std::string *all_words_vector;
    float *all_idf_vector;
    float *all_tfidf_sum_vector;

    unsigned int *loc;
    int num_entries;
public:
    vectorify_Job(Dict* n_all_words, std::string * n_all_words_vector, float * n_all_idf_vector, float * n_all_tfidf_sum_vector, unsigned int * n_loc, int n_num_entries){
        all_words = n_all_words;
        all_words_vector = n_all_words_vector;
        all_idf_vector = n_all_idf_vector;
        all_tfidf_sum_vector = n_all_idf_vector;
        loc = n_loc;
        num_entries = n_num_entries;
    };
    void run() override {
        all_words->vectorify(all_words->root, all_words_vector, all_idf_vector, all_tfidf_sum_vector, loc, num_entries);
    }
};

struct JobScheduler{
    int execution_threads;  //number of execution threads
    pthread_t* tids; // execution threads    
    
    //Queue* q;             // a queue that holds submitted jobs / tasks
    // mutex, condition variable, ...

    JobScheduler* initialize_scheduler(int n_execution_threads){
        execution_threads = n_execution_threads;
        tids = new pthread_t[execution_threads];
    };

    int submit_job(JobScheduler* sch, Job* j);
    int execute_all_jobs(JobScheduler* sch);
    int wait_all_tasks_finish(JobScheduler* sch);
    int destroy_scheduler(JobScheduler* sch);

};
#endif