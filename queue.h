#include <vector>
#ifndef QUEUE
#define QUEUE

template<typename T>
class Queue {
    
private:
    
    std::vector<T> queue;
    
public:
    
    T itemInQueue();
    void enqueue(T item);
    void dequeue();
    void requeueItemInQueue();
    int size();
    
};

#endif
