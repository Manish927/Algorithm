/*

Design your implementation of the circular queue. The circular queue is a linear data structure in which the operations are performed based on FIFO (First In First Out) principle and the last position is connected back to the first position to make a circle. It is also called "Ring Buffer".

One of the benefits of the circular queue is that we can make use of the spaces in front of the queue. In a normal queue, once the queue becomes full, we cannot insert the next element even if there is a space in front of the queue. But using the circular queue, we can use the space to store new values.

Implementation the MyCircularQueue class:

MyCircularQueue(k) Initializes the object with the size of the queue to be k.
int Front() Gets the front item from the queue. If the queue is empty, return -1.
int Rear() Gets the last item from the queue. If the queue is empty, return -1.
boolean enQueue(int value) Inserts an element into the circular queue. Return true if the operation is successful.
boolean deQueue() Deletes an element from the circular queue. Return true if the operation is successful.
boolean isEmpty() Checks whether the circular queue is empty or not.
boolean isFull() Checks whether the circular queue is full or not.
 

Example 1:

Input
["MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear", "isFull", "deQueue", "enQueue", "Rear"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]
Output
[null, true, true, true, false, 3, true, true, true, 4]

Explanation
MyCircularQueue myCircularQueue = new MyCircularQueue(3);
myCircularQueue.enQueue(1); // return True
myCircularQueue.enQueue(2); // return True
myCircularQueue.enQueue(3); // return True
myCircularQueue.enQueue(4); // return False
myCircularQueue.Rear();     // return 3
myCircularQueue.isFull();   // return True
myCircularQueue.deQueue();  // return True
myCircularQueue.enQueue(4); // return True
myCircularQueue.Rear();     // return 4
*/

class MyCircularQueue {
public:
    
    int front = 0;
    int rear = 0;
    int size = 0;
    int curr_len = 0;
    
    using CircularQueueT = std::vector<int>;
    CircularQueueT cq;
    
    MyCircularQueue(int k) {
        
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        
        size = k;
        cq.assign(k, -1);
    }
    
    bool enQueue(int value) {
        if (isFull())
        {return false;}
        
        curr_len++;
        
        cq[rear] = value;
        rear++;
        rear = rear % size;  // bound the 'rear' within the 'size' limit
        
        return true;
    }
    
    bool deQueue() {
        if (isEmpty())
            return false;
        
        curr_len--;
        cq[front] = -1;
        front = (front + 1) % size;
        
        return true;
        
    }
    
    int Front() {
        if (isEmpty())
            return -1;
        
        return cq[front];
    }
    
    int Rear() {
        if (isEmpty())
            return -1;
        
        int index = rear - 1;
        
        if (index < 0)
            index = index + size;
        
        return cq[index];
    }
    
    bool isEmpty() {
        if (curr_len == 0)
            return true;
        
        return false;
    }
    
    bool isFull() {
        if (curr_len == size)
            return true;
        
        return false;
    }
};
