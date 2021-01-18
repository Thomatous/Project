#include "job_scheduler.hpp"

bool running = true;

bool start = false;
std::mutex m_start;
std::condition_variable cv_start;

bool end = false;
std::mutex m_end;
std::condition_variable cv_end;

std::mutex print_mutex;
std::condition_variable cv;
std::mutex m;
std::mutex queue_mutex;
std::mutex train_mutex;
std::mutex retrain_mutex;

void thread_f(JobScheduler* js){
    while(js->q->head != NULL){
        queue_mutex.lock();
        bool locked = true;
        if(js->q->head != NULL){
            Job* cj = js->q->pop();
            queue_mutex.unlock();
            locked = false;

            cj->run();
            delete cj; 
        }
        if(locked == true)
            queue_mutex.unlock();
    }
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

lr_train_Job::lr_train_Job(std::string l, HashTable* hash, SM* f, LR* log_reg) {
    line = l;
    ht = hash;
    files = f;
    lr = log_reg;
}

void lr_train_Job::run() {
    Entry *e1, *e2;
    std::string url1, url2, label_str;
    short int label;
    std::string word, site1, id1, site2, id2;
    size_t first_slash;
    std::stringstream line_stream(line);
    for(int k=0 ; k < 3 ; ++k  ) {
        if(k == 0) {
            getline(line_stream, url1 , ',');
            first_slash = url1.find_first_of('/');
            site1 = url1.substr(0,first_slash);
            id1 = url1.substr(first_slash+2);
        }
        else if(k == 1) {
            getline(line_stream, url2, ',');
            first_slash = url2.find_first_of('/');
            site2 = url2.substr(0,first_slash);
            id2 = url2.substr(first_slash+2);
        }
        else if(k == 2) {
            getline(line_stream, label_str, ',');
            label = atoi(label_str.c_str());       
        }
    }
    e1 = ht->search(hash_value_calculator(site1, id1));
    e2 = ht->search(hash_value_calculator(site2, id2));

    lr->gradient_descent(e1->loc, e2->loc, label, files);
}

//============================================================================================================

lr_retrain_Job::lr_retrain_Job(Entry* a, Entry* b, SM* f, DoubleLinkedList* ls, LR* log_reg, float t) {
    e1 = a;
    e2 = b;
    results = ls;
    files = f;
    lr = log_reg;
    threshold = t;
}

void lr_retrain_Job::run(){
    float pred = lr->predict(files, e1, e2);
    if(pred < threshold || pred > 1.0-threshold){
        retrain_mutex.lock();
        results->push(e1, e2, pred);
        retrain_mutex.unlock();
    }
}

//============================================================================================================

JobScheduler::JobScheduler(int n_execution_threads){
    execution_threads = n_execution_threads;
    tids = new std::thread[execution_threads];
    q = new Queue();

}

void JobScheduler::execute_all_jobs(){
    for(int i = 0 ; i < execution_threads ; i++){
        tids[i] = std::thread(thread_f, this);
    }

    // start = true;
    // end = false;
    // cv_start.notify_all();
}

void JobScheduler::wait_all_tasks_finish(){
    for(int i = 0 ; i < execution_threads ; i++) 
        tids[i].join();
    start = false;
    // end = true;
    // cv_end.notify_all();
 
}

void JobScheduler::submit_job(Job* j){
    q->push_back(j);
}

JobScheduler::~JobScheduler(){
    delete q;
    delete[] tids;
}   

