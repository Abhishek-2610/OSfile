#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable read_cv, write_cv;
int readers = 0, writers = 0, active_writers = 0;

void reader(int id) {
    unique_lock<mutex> lock(mtx);
    while (writers > 0 || active_writers > 0) {
        read_cv.wait(lock);
    }
    readers++;
    lock.unlock();

    // Reading...
    cout << "Reader " << id << " is reading." << endl;

    lock.lock();
    readers--;
    if (readers == 0 && writers > 0) {
        write_cv.notify_one();
    }
    lock.unlock();
}

void writer(int id) {
    unique_lock<mutex> lock(mtx);
    while (readers > 0 || writers > 0) {
        active_writers++;
        write_cv.wait(lock);
        active_writers--;
    }
    writers++;
    lock.unlock();

    // Writing...
    cout << "Writer " << id << " is writing." << endl;

    lock.lock();
    writers--;
    if (writers == 0) {
        read_cv.notify_all();
    } else {
        write_cv.notify_one();
    }
    lock.unlock();
}

int main() {
    const int num_readers = 5;
    const int num_writers = 2;
    thread reader_threads[num_readers];
    thread writer_threads[num_writers];

    for (int i = 0; i < num_readers; ++i) {
        reader_threads[i] = thread(reader, i);
    }

    for (int i = 0; i < num_writers; ++i) {
        writer_threads[i] = thread(writer, i);
    }

    for (int i = 0; i < num_readers; ++i) {
        reader_threads[i].join();
    }

    for (int i = 0; i < num_writers; ++i) {
        writer_threads[i].join();
    }

    return 0;
}
