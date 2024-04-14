#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

#define NUM_THREADS 2

atomic<int> turn(0);
atomic<bool> flag[NUM_THREADS] = {false};

void critical_section(int thread_id) {
    cout << "Thread " << thread_id << " is entering the critical section." << endl;
    // Critical section
    cout << "Thread " << thread_id << " is in the critical section." << endl;
    // Simulating work
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Thread " << thread_id << " is exiting the critical section." << endl;
}

void non_critical_section(int thread_id) {
    // Non-critical section
    cout << "Thread " << thread_id << " is in the non-critical section." << endl;
    // Simulating work
    this_thread::sleep_for(chrono::seconds(1));
}

void peterson_solution(int thread_id) {
    int other = 1 - thread_id; // Index of the other thread
    flag[thread_id] = true;
    turn = other;

    // Wait until it's the thread's turn and the other thread isn't in its critical section
    while (flag[other] && turn == other) {
        // Busy wait
    }

    // Critical section
    critical_section(thread_id);

    // Exiting the critical section
    flag[thread_id] = false;
}

void thread_function(int thread_id) {
    // Simulating multiple iterations
    for (int i = 0; i < 3; ++i) {
        non_critical_section(thread_id);
        peterson_solution(thread_id);
    }
}

int main() {
    thread threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads[i] = thread(thread_function, i);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads[i].join();
    }

    return 0;
}
