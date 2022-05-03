#ifndef QUEUE_BLOCK_QUEUE_H
#define QUEUE_BLOCK_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockQueue
{
public:
    using value_type        = T;
    using container_type    = std::queue<value_type>;
    using size_type         = typename container_type::size_type;
private:
    size_type capacity_ = 0;
    container_type contianer_;
    mutable std::mutex mutex_;
    mutable std::condition_variable not_empty_;
    mutable std::condition_variable not_full_;

public:
    BlockQueue() = delete;
    BlockQueue(const size_type capacity):capacity_(capacity){}
    BlockQueue(const BlockQueue &) = default;
    BlockQueue(BlockQueue &&) = default;
    BlockQueue &operator=(const BlockQueue&) = default;
    BlockQueue &operator=(BlockQueue &&) = default;

private:
    bool empty() const {return contianer_.empty();}
    bool full() const {return not(contianer_.size() < capacity_);}

public:
    void put(const value_type &item)
    {
        std::unqiue_lock<std::mutex> lock(mutex_);
        while(full())
        {
            not_full_.wait(lock);
        }
        contianer_.push(item);
        not_empty_.notify_one();
    }

    void take(value_type &out)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while(empty())
        {
            not_empty_.wait(lock);
        }
        out = container_.front();
        contianer_.pop();
        not_full_.notify_one();
    }

    template <typename Duration>
    bool put_for(const value_type &item, const Duration &d)
    {
        std::unqiue_lock<std::mutex> lock(mutex_);
        if(not_full_.wait_for(lock, d, [&](){return not full();}))
        {
            contianer_.push(item);
            not_empty_.notify_one();
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Duration>
    bool take_for(const Duration &d, value_type &out)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if(not_empty_.wait_for(lock, d, [&](){return not empty();}))
        {
            out = contianer_.front();
            contianer_.pop();
            not_full.notify_one();
            return true;
        }
        else
        {
            return false;
        }
    }
};

#endif