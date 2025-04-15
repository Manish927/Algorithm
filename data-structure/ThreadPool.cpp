/*
ThreadPool in C++ using C++14 features. This implementation allows you to submit tasks to a pool of worker threads, which execute them concurrently.

Explanation
1.	ThreadPool Class:
•	workers: A vector of threads that execute tasks.
•	tasks: A queue to store tasks submitted to the pool.
•	mtx: A mutex to ensure thread-safe access to the task queue.
•	cv: A condition variable to notify worker threads when tasks are available.
•	stop: An atomic flag to signal the threads to stop when the pool is destroyed.
2.	Worker Threads:
•	Each thread runs the workerThread function, which continuously waits for tasks to execute.
•	If the stop flag is set and the task queue is empty, the thread exits.
3.	Task Submission:
•	The submit method allows you to add tasks to the queue. Tasks are stored as std::function<void()> objects.
•	The method uses a variadic template to accept any callable object (e.g., lambdas, function pointers).
4.	ThreadPool Lifecycle:
•	The constructor initializes the worker threads.
•	The destructor stops all threads and ensures they finish execution before the program exits.
5.	Main Function:
•	Demonstrates creating a thread pool with 4 threads and submitting 10 tasks.
•	Each task prints its ID and the thread processing it, then simulates work with a delay.
---
Output
The output will look something like this (thread IDs may vary):

Task 1 is being processed by thread 140735680885760
Task 2 is being processed by thread 140735672493056
Task 3 is being processed by thread 140735664100352
Task 4 is being processed by thread 140735655707648
Task 5 is being processed by thread 140735680885760
Task 6 is being processed by thread 140735672493056
Task 7 is being processed by thread 140735664100352
Task 8 is being processed by thread 140735655707648
Task 9 is being processed by thread 140735680885760
Task 10 is being processed by thread 140735672493056


Key Features
1.	Concurrency: Tasks are executed concurrently by multiple threads.
2.	Thread Safety: The task queue is protected by a mutex.
3.	Dynamic Task Submission: Tasks can be submitted at runtime.
4.	Graceful Shutdown: The destructor ensures all threads finish before the program exits.
---
Complexity
•	Task Submission: O(1) (queue insertion).
•	Task Execution: O(1) (queue removal and execution).
•	Space Complexity: O(n), where n is the number of tasks in the queue.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
using namespace std;

class ThreadPool {
private:
    vector<thread> workers; // Worker threads
    queue<function<void()>> tasks; // Task queue
    mutex mtx; // Mutex for thread safety
    condition_variable cv; // Condition variable for task scheduling
    atomic<bool> stop; // Flag to stop the thread pool

    // Worker thread function
    void workerThread() {
        while (true) {
            function<void()> task;

            {
                unique_lock<mutex> lock(mtx);

                // Wait for a task or stop signal
                cv.wait(lock, [this]() { return !tasks.empty() || stop; });

                if (stop && tasks.empty()) {
                    return; // Exit the thread
                }

                // Get the next task
                task = move(tasks.front());
                tasks.pop();
            }

            // Execute the task
            task();
        }
    }

public:
    // Constructor: Initialize the thread pool with a given number of threads
    ThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this]() { workerThread(); });
        }
    }

    // Destructor: Stop all threads and clean up
    ~ThreadPool() {
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all(); // Notify all threads to stop
        for (thread& worker : workers) {
            if (worker.joinable()) {
                worker.join(); // Wait for threads to finish
            }
        }
    }

    // Submit a task to the thread pool
    template <typename F, typename... Args>
    void submit(F&& func, Args&&... args) {
        {
            lock_guard<mutex> lock(mtx);
            tasks.emplace([func, args...]() { func(args...); });
        }
        cv.notify_one(); // Notify one thread to process the task
    }
};

int main() {
    // Create a thread pool with 4 threads
    ThreadPool pool(4);

    // Submit tasks to the thread pool
    for (int i = 1; i <= 10; ++i) {
        pool.submit([i]() {
            cout << "Task " << i << " is being processed by thread " 
                 << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::milliseconds(500)); // Simulate work
        });
    }

    // Allow some time for tasks to complete
    this_thread::sleep_for(chrono::seconds(6));

    return 0;
}

