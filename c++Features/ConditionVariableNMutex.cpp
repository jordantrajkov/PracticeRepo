#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool dataReady = false;

void producer() {
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::unique_lock<std::mutex> lock(mtx);
    dataReady = true;
    lock.unlock();

    cv.notify_one(); // Notify the waiting thread
}

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return dataReady; }); // Wait until dataReady is true

    // Do something with the data
    std::cout << "Consumer: Data is ready!" << std::endl;
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
