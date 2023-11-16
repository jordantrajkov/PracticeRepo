#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class RTOSQueue {
public:
    void push(int data) {
        std::unique_lock<std::mutex> lock(mutex_);
         queue_.push(data); // push the data in the queue
         lock.unlock(); // unlock 
         condition_.notify_one(); // notify the next thread 
    }

    int pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return !queue_.empty(); });// if queue not empty lock if empty unlock
        int data = queue_.front();// if empty put in the front (FIFO)
        queue_.pop(); // Serve and then pop 
        return data; 
    }

private:
    std::queue<int> queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
};

RTOSQueue dataQueue;

void ProducerTask() {
    for (int i = 1; i <= 10; ++i) {
        dataQueue.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate data production time
    }
}

void ConsumerTask() {
    for (int i = 1; i <= 10; ++i) {
        int data = dataQueue.pop();
        std::cout << "Consumed: " << data << std::endl;
    }
}

int main() {
    std::thread producer(ProducerTask);
    std::thread consumer(ConsumerTask);

    producer.join();
    consumer.join();

    return 0;
}
