#include <iostream>
#include "entry.hpp"
#include "hashtable.hpp"
#include "parser.hpp"
#include "dict.hpp"
#include "logistic_regression.hpp"
#include "sparse_matrix.hpp"
#include "job_scheduler.hpp"

using namespace std;

int main() {
    Entry* e1 = new Entry("a", "1");
    Entry* e2 = new Entry("a", "2");
    Entry* e3 = new Entry("a", "3");
    Entry* e4 = new Entry("a", "4");
    Entry* e5 = new Entry("a", "5");

    e2->differs_from(e5);
    e2->differs_from(e3);
    e2->differs_from(e4);
    e1->differs_from(e3);
    e1->merge(e2);
    e4->merge(e1);

    cout << "end" << endl;

    return 0;
}