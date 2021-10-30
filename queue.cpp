#include "queue.h"
#include "mail.h"

// Gets the next item in the queue: gets the first item in the vector
template<typename T>
T Queue<T>::itemInQueue() {
    return queue.front();
}

// Enqueues a new item to the queue: adds the item to the end of the vector
template<typename T>
void Queue<T>::enqueue(T item) {
    queue.insert(queue.begin(), item);
}

// Dequeues the next item in the queue: deletes the first item in the vector
template<typename T>
void Queue<T>::dequeue() {
    queue.erase(queue.begin());
}

// Requeues the next item in the queue: moves the first item in the vector to the last item
template<typename T>
void Queue<T>::requeueItemInQueue() {
    std::rotate(queue.begin(), queue.begin() + 1, queue.end());
}

// Gets the size of the queue
template<typename T>
int Queue<T>::size() {
    return queue.size();
}

// Avoid linker error
template class Queue<Mail>;
