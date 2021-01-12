#ifndef _JOB_SCHEDULER_
#define _JOB_SCHEDULER_

#include <iostream>
#include <thread>

class Job{
public:
    virtual void run() = 0;
    virtual ~Job() { }
};

class DemoJob : public Job{
public:
    DemoJob(){};
    void run() override {
        //code here
    }
};

struct JobScheduler{
    int execution_threads;  //number of execution threads
    //Queue* q;             // a queue that holds submitted jobs / tasks    !IMPLEMENT QUEUE
    std::thread* tids;      // execution threads
    // mutex, condition variable, ...

    JobScheduler* initialize_scheduler(int execution_threads);
    int submit_job(JobScheduler* sch, Job* j);
    int execute_all_jobs(JobScheduler* sch);
    int wait_all_tasks_finish(JobScheduler* sch);
    int destroy_scheduler(JobScheduler* sch);

};
#endif