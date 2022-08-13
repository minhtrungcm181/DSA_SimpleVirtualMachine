#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>
using namespace std;
/*
StackFrame declaration
*/
class operand;
class StackFrame {
    int opStackMaxSize; // max size of operand stack
    int localVarArrSize; // size of local variable array
public:
    /*
    Constructor of StackFrame
     */
    operand* b;
    float* new_space;
    StackFrame();
    ~StackFrame();
    void doing(string*, int);
    /*
    Run the method written in the testcase

    @param filename name of the file
    */
    void run(std::string filename);


};
class operand {
private:
    int countNode;
    int maxsize;
    friend class StackFrame;
    class Node {
    private:
        Node* next;
        int ivalue;
        float fvalue;
        int type;
    public:
        Node() {
            this->ivalue = 0;
            this->type = 5;
            this->fvalue = 0.0;
            this->next = nullptr;
        };
        Node(Node* a) {
            this->ivalue = a->ivalue;
            this->type = a->type;
            this->fvalue = a->fvalue;
            this->next = a->next;
        }
        ~Node() {
            this->ivalue = 0;
            this->fvalue = 0;
            this->type = 0;
            this->next = nullptr;
        }
        friend class operand;
    };
public:
    Node* head;
    Node* tail;
    operand(int max) {
        head = tail = NULL;
        countNode = 0;
        maxsize = max;
    }
    ~operand() {
        head = tail = NULL;
        countNode = maxsize = 0;
    }
    void day(Node* tmp);
    float tren();
    void xoa();
    bool fulled();
    bool iEmpty();
    int kichco();
    int checktype();
    int iconst(string val);
    int imul();
    int fconst(string val);
    int fsub();
    int iadd();
    int fadd();
    int isub();
    int idiv();
    int fdiv();
    int irem();
    int ineg();
    int fneg();
    int iand();
    int ior();
    int ieq();
    int feq();
    int ineq();
    int fneq();
    int ilt();
    int flt();
    int igt();
    int fgt();
    int ibnot();
    int fmul();
    int i2f();
    int f2i();
};



#endif // !__STACK_FRAME_H__

