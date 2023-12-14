#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <future>

class Model {
    public:
        typedef std::function<void ()> task_type;

    public:
        Model()
        {
            m_tasks.emplace_back(&Model::protected_function);
            m_tasks.emplace_back(&Model::updated_function);
            
            for (int i = 0; i < m_tasks.size(); ++i) {
                m_thread = new std::thread(m_tasks[i]);
                m_thread++;
            }
        }

        ~Model() {
            // m_thread->detach();
        }

        void jointable() {
            if (m_thread->joinable()) {
                std::cout << "Joinable!" << std::endl;
                // m_thread->detach();
                m_thread->join();
                std::cout << "Joinable!" << std::endl;
            }
            else {
                std::cout << "unjoinable!" << std::endl;
            }

            std::cout << "-----------------> <--------------" << std::endl;
        }

        void setValue(const bool _val) {
            m_currentValue = _val;
            std::cout << "Setting current value: " << m_currentValue << std::endl;
        }
    protected:
        void protected_function() {
            int count = 0;
            while (count < 100) {
                std::cout << std::endl << __FUNCTION__ << " - id-thread: " << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                count += 5;

                if (m_currentValue) {
                    break;
                }
            }
        }

        void updated_function() {
            int count = 0;
            while (count < 100) {
                std::cout << std::endl << __FUNCTION__ << " - id-thread: " << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                count += 5;
                if (count == 50) m_currentValue = true;
            }
        }
    private: 
        std::thread* m_thread {nullptr};
        bool m_currentValue{false};
        int m_sizeOfThread{2};
        std::vector<task_type> m_tasks;
        std::mutex m_mutex;
};

int main() {
    Model* m_model = new Model();
    // auto func_1 = std::async(std::launch::async,[m_model]{
    //     m_model->function();
    // });


    std::cout << "================ Start Here ===============" << std::endl;
    int count = 0;
    while (count < 100) {
        std::cout << __FUNCTION__ << " - id-thread: " << std::this_thread::get_id() << std::endl;
        count += 10;
        if (count == 50) {
            m_model->setValue(true);
        }
    };
    std::cout << "================ Passing Here ===============" << std::endl;


    m_model->jointable();

    scanf("\n");
    // delete m_model;
    return 0;
}