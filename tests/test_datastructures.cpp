#include <iostream>
#include <string>
#include "../utils/linkedList.h"
#include "../utils/hashTable.h"
#include "../utils/binaryTree.h"
#include "../utils/priorityQueue.h"

int main() {
    bool ok = true;
    using std::cout; using std::endl;

    // LinkedList<int>
    LinkedList<int> ll;
    ll.insertAtEnd(1);
    ll.insertAtEnd(2);
    ll.insertAtEnd(3);
    if (ll.search(2) == nullptr) { cout<<"LinkedList: FAIL search present\n"; ok=false; } else cout<<"LinkedList: search present OK\n";
    ll.remove(2);
    if (ll.search(2) != nullptr) { cout<<"LinkedList: FAIL remove\n"; ok=false; } else cout<<"LinkedList: remove OK\n";

    // HashTable<int,string>
    HashTable<int,std::string> ht;
    ht.insert(1,std::string("one"));
    std::string* s = ht.search(1);
    if (!s || *s!="one") { cout<<"HashTable: FAIL insert/search\n"; ok=false;} else cout<<"HashTable: insert/search OK\n";
    ht.remove(1);
    s = ht.search(1);
    if (s!=nullptr) { cout<<"HashTable: FAIL remove\n"; ok=false; } else cout<<"HashTable: remove OK\n";

    // BinaryTree<int>
    BinaryTree<int> bt;
    bt.add(10); bt.add(5); bt.add(15);
    auto free1 = bt.findFreeBed();
    if (!free1) { cout<<"BinaryTree: FAIL findFree (none)\n"; ok=false; } else cout<<"BinaryTree: first free OK: "<<free1->data<<endl;
    bt.assignBed(10);
    auto free2 = bt.findFreeBed();
    if (!free2 || free2->data==10) { cout<<"BinaryTree: FAIL findFree after assign\n"; ok=false; } else cout<<"BinaryTree: findFree after assign OK: "<<free2->data<<endl;

    // PriorityQueue<string>
    PriorityQueue<std::string> pq;
    pq.insert(std::string("a"), 2);
    pq.insert(std::string("b"), 1);
    pq.insert(std::string("c"), 3);
    std::string top = pq.peek();
    if (top != "b") { cout<<"PriorityQueue: FAIL peek expected b got "<<top<<endl; ok=false; } else cout<<"PriorityQueue: peek OK\n";
    std::string r1 = pq.removeHighestPriority();
    if (r1 != "b") { cout<<"PriorityQueue: FAIL removeHighestPriority expected b got "<<r1<<endl; ok=false; } else cout<<"PriorityQueue: remove 1 OK\n";
    std::string r2 = pq.removeHighestPriority();
    if (r2 != "a") { cout<<"PriorityQueue: FAIL remove 2 expected a got "<<r2<<endl; ok=false; } else cout<<"PriorityQueue: remove 2 OK\n";

    cout << (ok ? "ALL TESTS PASSED\n" : "SOME TESTS FAILED\n");
    return ok ? 0 : 1;
}
