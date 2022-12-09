#ifndef RECORDER_H
#define RECORDER_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <chrono>
#include <QImage>

class Recorder {
public:
    enum class Mode {
        kInstantStop,
        kWaitProcessing
    };
    // explicit constructor
    explicit Recorder(Mode mode);

    // virtual destructor
    virtual ~Recorder() noexcept;

    // start recording
    void start();

    // stop recording
    void stop();

    void push_back(std::pair<QImage, QString> &&data); // lock and move the data

private:
    void run();

    const bool instantStop;
    std::atomic_bool running = false;
    std::thread worker;

    std::queue<std::pair<QImage, QString>> queue;
    std::mutex queueMutex;
    std::condition_variable queueCondition;
};

#endif // RECORDER_H
