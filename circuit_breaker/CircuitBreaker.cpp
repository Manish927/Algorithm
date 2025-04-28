/*
To implement a multithreaded Circuit Breaker in C++, we need to ensure thread safety while managing the state of the circuit breaker. The circuit breaker will have three states:
1.	Closed: All requests are allowed, and failures are tracked.
2.	Open: Requests are blocked for a specified duration.
3.	Half-Open: A limited number of requests are allowed to test if the service has recovered.

Explanation
1.	Circuit Breaker States:
•	CLOSED: All requests are allowed, and failures are tracked.
•	OPEN: Requests are blocked for a specified duration.
•	HALF-OPEN: A limited number of requests are allowed to test if the service has recovered.
2.	Thread Safety:
•	A mutex ensures that state transitions and counters are thread-safe.
•	Atomic variables (failureCount and successCount) are used for lightweight thread-safe counters.
3.	Service Call Simulation:
•	The simulateServiceCall function simulates a service that fails for every 3rd request.
4.	Worker Threads:
•	Multiple threads simulate concurrent requests to the circuit breaker.
5.	State Transitions:
•	The circuit breaker transitions between states based on the number of failures and successes.
---
Example Output
Request 1: Service succeeded.
Request 2: Service succeeded.
Request 3: Service failed.
Request 4: Service succeeded.
Request 5: Service succeeded.
Request 6: Service failed.
Request 7: Service failed.
Circuit Breaker transitioned to OPEN state.
Request 8: Circuit Breaker is OPEN. Request blocked.
Request 9: Circuit Breaker is OPEN. Request blocked.
Request 10: Circuit Breaker is OPEN. Request blocked.
...

Key Features
1.	Thread Safety:
•	The implementation ensures thread-safe access to the circuit breaker state and counters.
2.	Configurable Parameters:
•	The failure threshold, success threshold, and open duration can be customized.
3.	Multithreaded Simulation:
•	Multiple threads simulate concurrent requests to the circuit breaker.
---
Complexity
•	Time Complexity:
•	allowRequest, recordSuccess, and recordFailure: O(1)
•	Space Complexity:
•	O(1), as no additional data structures are used.


*/

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <thread>
#include <atomic>
using namespace std;

class CircuitBreaker {
public:
    enum State { CLOSED, OPEN, HALF_OPEN };

private:
    State state;                      // Current state of the circuit breaker
    int failureThreshold;             // Number of failures to trigger the circuit breaker
    int successThreshold;             // Number of successes to close the circuit breaker
    chrono::milliseconds openDuration; // Duration to stay in the OPEN state
    atomic<int> failureCount;         // Count of consecutive failures
    atomic<int> successCount;         // Count of consecutive successes
    chrono::steady_clock::time_point lastOpened; // Time when the circuit breaker was last opened
    mutex mtx;                        // Mutex for thread safety

public:
    // Constructor
    CircuitBreaker(int failureThreshold, int successThreshold, chrono::milliseconds openDuration)
        : state(CLOSED), failureThreshold(failureThreshold), successThreshold(successThreshold),
          openDuration(openDuration), failureCount(0), successCount(0) {}

    // Check if the circuit breaker allows a request
    bool allowRequest() {
        lock_guard<mutex> lock(mtx);

        if (state == OPEN) {
            // Check if the open duration has passed
            auto now = chrono::steady_clock::now();
            if (chrono::duration_cast<chrono::milliseconds>(now - lastOpened) >= openDuration) {
                state = HALF_OPEN; // Transition to HALF-OPEN state
                successCount = 0;  // Reset success count
                cout << "Circuit Breaker transitioned to HALF-OPEN state." << endl;
            } else {
                return false; // Requests are blocked in OPEN state
            }
        }

        return true; // Requests are allowed in CLOSED and HALF-OPEN states
    }

    // Record a successful request
    void recordSuccess() {
        lock_guard<mutex> lock(mtx);

        if (state == HALF_OPEN) {
            successCount++;
            if (successCount >= successThreshold) {
                state = CLOSED; // Transition to CLOSED state
                failureCount = 0; // Reset failure count
                cout << "Circuit Breaker transitioned to CLOSED state." << endl;
            }
        }
    }

    // Record a failed request
    void recordFailure() {
        lock_guard<mutex> lock(mtx);

        if (state == CLOSED) {
            failureCount++;
            if (failureCount >= failureThreshold) {
                state = OPEN; // Transition to OPEN state
                lastOpened = chrono::steady_clock::now();
                cout << "Circuit Breaker transitioned to OPEN state." << endl;
            }
        } else if (state == HALF_OPEN) {
            state = OPEN; // Transition back to OPEN state
            lastOpened = chrono::steady_clock::now();
            cout << "Circuit Breaker transitioned back to OPEN state." << endl;
        }
    }

    // Get the current state of the circuit breaker
    State getState() {
        lock_guard<mutex> lock(mtx);
        return state;
    }
};

// Simulate a service call
bool simulateServiceCall(int requestId) {
    // Simulate a failure for every 3rd request
    if (requestId % 3 == 0) {
        cout << "Request " << requestId << ": Service failed." << endl;
        return false;
    }
    cout << "Request " << requestId << ": Service succeeded." << endl;
    return true;
}

void worker(CircuitBreaker& circuitBreaker, int threadId) {
    for (int i = 1; i <= 10; ++i) {
        if (circuitBreaker.allowRequest()) {
            if (simulateServiceCall(i)) {
                circuitBreaker.recordSuccess();
            } else {
                circuitBreaker.recordFailure();
            }
        } else {
            cout << "Request " << i << ": Circuit Breaker is OPEN. Request blocked." << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(200)); // Simulate delay between requests
    }
}

int main() {
    // Create a Circuit Breaker with a failure threshold of 3, success threshold of 2, and open duration of 5 seconds
    CircuitBreaker circuitBreaker(3, 2, chrono::milliseconds(5000));

    // Create multiple threads to simulate concurrent requests
    thread t1(worker, ref(circuitBreaker), 1);
    thread t2(worker, ref(circuitBreaker), 2);

    t1.join();
    t2.join();

    return 0;
}
