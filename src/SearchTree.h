#include <chrono>

using namespace std;

class SearchTree {
    private:
        chrono::_V2::system_clock::time_point start;
    public:
        /* Functions that must be implemented in Search Tree implementations */
        void insert(int data);
        int* find(int key);
        void remove(int key);


        /* Timer functions */
        void startTimer(){
            start = std::chrono::high_resolution_clock::now();
        }
        /**
         * @return The time in microseconds that have elapsed since the timer was started.
        */
        long stopTimer(){
            auto end = std::chrono::high_resolution_clock::now();
            return chrono::duration_cast<chrono::microseconds>(end-start).count();
        }
};