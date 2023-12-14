#include <iostream>
#include <thread>
#include <mutex>
std::mutex gMutex;
class Singletone {
    public:
        static Singletone* get_instance() {
            static Singletone _ins;
            return &_ins;
        }

        void set_value(const int _val) {
            m_value = _val;
        }

        int get_value() const {
            return m_value;
        }

    private:
        Singletone() {}

    protected:
        int m_value { 0 };
    
};


void thread_handle_one() {
    auto _pattern = Singletone::get_instance();
    int val = 0;
    {
        // std::lock_guard<std::mutex> guard(gMutex);
        val = _pattern->get_value();
        std::cout << "Thread 1 get value: " << val << std::endl;
    }

    {
        if (val != 0) {
            // std::lock_guard<std::mutex> guard(gMutex);
            _pattern->set_value(100);
            std::cout << "Thread 1: Set value to 100" << std::endl;
        }
    }
}

void thread_handle_two() {
    auto _pattern = Singletone::get_instance();
    int val = 0;
    {
        // std::lock_guard<std::mutex> guard(gMutex);
        val = _pattern->get_value();
        std::cout << "Thread 2 get value: " << val << std::endl;
    }

    {
        if (val != 0) {
            // std::lock_guard<std::mutex> guard(gMutex);
            _pattern->set_value(350);
            std::cout << "Thread 2: Set value to 350" << std::endl;
        }
    }
}


int main() {
    auto _pattern = Singletone::get_instance();
    std::thread _t1(thread_handle_one);
    std::thread _t2(thread_handle_two);
    _pattern->set_value(241);

    _t1.join();
    _t2.join();
    return 0;
}