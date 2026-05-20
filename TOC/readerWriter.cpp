#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

int readCount = 0;

void reader(int id) {

    mtx.lock();

    readCount++;

    cout << "Reader " << id << " is Reading\n";

    mtx.unlock();
}

void writer(int id) {

    mtx.lock();

    cout << "Writer " << id << " is Writing\n";

    mtx.unlock();
}

int main() {

    thread r1(reader, 1);
    thread r2(reader, 2);
    thread w1(writer, 1);

    r1.join();
    r2.join();
    w1.join();

    return 0;
}