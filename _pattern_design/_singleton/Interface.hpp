#ifndef _INTERFACE_H_
#define _INTERFACE_H_

class PatternInterface {
    public:
        static PatternInterface* create() {
            if (_ins == nullptr) {
                _ins = new PatternInterface();
            }
            return _ins;
        }

        void setValue(const int val) {
            m_value = val;
        }

        int getValue() const { return m_value; }
    protected:
        static PatternInterface* _ins;
    private:
        int m_value{10};
};

PatternInterface* PatternInterface::_ins = nullptr;

#endif 