/*146. LRU Cache
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

The cache is initialized with a positive capacity.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache( 2 /* capacity */ );
/*
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4*/

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

public class LRUCache {
    class Node
    {
        int key;
        int val;
        Node prev;
        Node next;
    }
    
    final Node head = new Node();
    final Node tail = new Node();
    public Map<Integer, Node> lookup_map;
    int max_capacity;
    
    public LRUCache(int capacity) 
    {
        lookup_map = new HashMap<>(capacity);
        max_capacity = capacity;
        head.next = tail;
        tail.prev = head; 
    }
    
    public void put(int key, int value)
    {
        Node node = lookup_map.get(key);

        if (node != null)
        {
            evictNode(node);
            node.val = value;
            addNode(node);
        }
        else
        {
            if (lookup_map.size() == max_capacity)
            {
                lookup_map.remove(tail.prev.key);
                evictNode(tail.prev);
            }

            Node new_node = new Node();
            new_node.key = key;
            new_node.val = value;
            lookup_map.put(key, new_node);
            addNode(new_node);
        }
    }
    
    private void addNode(Node node)
    {
        Node head_next = head.next;
        node.next = head_next;
        head_next.prev = node;
        head.next = node;
        node.prev = head;
    }

    private void evictNode(Node node)
    {
        Node next_node = node.next;
        Node prev_node = node.prev;

        next_node.prev = prev_node;
        prev_node.next = next_node;
    }
    
    public int get(int key) 
    {
        int ret = -1;

        Node node = lookup_map.get(key);
        if (node != null)
        {
            ret = node.val;
            // move to tail
            evictNode(node);
            addNode(node);
        }

        return ret;
    }
    
}

