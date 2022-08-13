#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarArrSize(LOCAL_VARIABLE_ARRAY_SIZE) {
    b = new operand(opStackMaxSize/2);
    new_space = new float[LOCAL_VARIABLE_ARRAY_SIZE];
    for (int i = 0; i < LOCAL_VARIABLE_ARRAY_SIZE; i++) {
        new_space[i] = -1;
    }
}
StackFrame::~StackFrame() {
    delete b;
    delete[] new_space;
}

string instructions(string s) {
    string delimiter = " ";
    string token = s.substr(0, s.find(delimiter));
    return token;
}

string value(string s) {
    string delimiter = " ";
    string token = s.substr(0, s.find(delimiter));
    s.erase(0, s.find(delimiter) + delimiter.length());
    string token2 = s.substr(0, s.find(delimiter));
    return token2;
}
void operand::day(Node* tmp) {
    if (fulled() == true) { return; }
    else if (iEmpty() == true) {
        head = tail = new Node(tmp);
        countNode ++;
    }
    else {
        tail->next = new Node(tmp);
        tail = tail->next;
        countNode ++;
    }
}
float operand::tren() {
    if (tail->type == 1) { return tail->fvalue; }
    else if (tail->type == 0)
        return tail->ivalue;
    else return 0;
}
void operand::xoa() {
    if (iEmpty() == true) { return; }
    else {
        Node* tmp = new Node();
        tmp = head;
        if (countNode == 1) { head = nullptr; delete head; countNode --; }
        else if (countNode == 2) { tail = head; countNode --; }
        else {
            while (tmp->next != tail) {
                tmp = tmp->next;
            }
            tmp->next = nullptr;
            tail = nullptr;
            delete tail;
            tail = tmp;
            countNode --;
        }

    }
}
bool operand::fulled() {
    if (countNode >= 16 ) {
        return true;
    }
    else {
        return false;
    }
}
bool operand::iEmpty() {
    if (countNode == 0) {
        return true;
    }
    else {
        return false;
    }
}
int operand::kichco() {
    return countNode;
}

int operand::checktype() {
    return tail->type;
}
int operand::iconst(string val) {
    int s = stoi(val);
    if (fulled() == true) return 0;
    Node* tmp = new Node;
    tmp->ivalue = s;
    tmp->fvalue = 0;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::imul() {
    int a, b, c;
    if (kichco() < 2) return 2;
    a = tren(); c = checktype();
    if (c == 1) { return 0; }
    xoa();
    b = tren();
    c = checktype();
    if (c == 1) { return 0; }
    xoa();
    c = a * b;
    Node* tmp = new Node();
    tmp->ivalue = c;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::fconst(string s) {
    float number = stof(value(s));
    if (fulled() == true) return 0;
    Node* tmp = new Node();
    tmp->ivalue = 0;
    tmp->fvalue = number;
    tmp->type = 1;
    day(tmp);
    return 1;
}
int operand::fsub() {
    float a, b, c;
    if (kichco() < 2) return 2;
    a = tren();
    xoa();
    b = tren();
    xoa();
    c = b-a;
    Node* tmp = new Node();
    tmp->fvalue = c;
    tmp->type = 1;
    tmp->ivalue = 0;
    day(tmp);
    return 1;
}
int operand::iadd() {
    int a, b, c;
    if (kichco() < 2) return 2;
    a = tren(); c = checktype();
    if (c == 1) { return 0; }
    xoa();
    b = tren(); c = checktype();
    if (c == 1) { return 0; }
    xoa();
    c = a + b;
    Node* tmp = new Node();
    tmp->ivalue = c;
    tmp->type = 0;
    tmp->fvalue = 0;
    day(tmp);
    return 1;
}
int operand::fadd() {
    float a, b, c;
    if (kichco() < 2) return 2;
    a = tren();
    xoa();
    b = tren();
    xoa();
    c = a + b;
    Node* tmp = new Node();
    tmp->fvalue = c;
    tmp->ivalue = 0;
    tmp->type = 1;
    day(tmp);
    return 1;
}
int operand::isub() {
    int a, b, c;
    if (kichco() < 2) return 2;
    a = tren(); c = checktype();
    if (c == 1) { return 0; }
    xoa();
    b = tren(); c = checktype();
    if (c == 1) { return 0; }
    xoa();
    c = b-a;
    Node* tmp = new Node();
    tmp->fvalue = 0;
    tmp->ivalue = c;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::idiv() {
    int a, b, c;
    if (kichco() < 2) return 3;
    a = tren(); c = checktype();
    if (c == 1) { return 0; }
    xoa();
    b = tren(); c = checktype();
    if (c == 1) { return 0; }
    if (a == 0) { return 2; }
    xoa();
    c = b/a;
    Node* tmp = new Node();
    tmp->fvalue = 0;
    tmp->ivalue = c;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::fmul() {
    float a, b, c;
    if (kichco() < 2) return 2;
    a = tren();
    xoa();
    b = tren();
    xoa();
    c = a * b;
    Node* tmp = new Node();
    tmp->fvalue = c;
    tmp->ivalue = 0;
    tmp->type = 1;
    day(tmp);
    return 1;
}
int operand::fdiv() {
    float a, b, c;
    if (kichco() < 2) return 3;
    a = tren();  if (a == 0) { return 2; }
    xoa();
    b = tren();
    xoa();
    c = b/a;
    Node* tmp = new Node();
    tmp->fvalue = c;
    tmp->ivalue = 0;
    tmp->type = 1;
    day(tmp);
    return 1;
}
int operand::irem() {
    int a, b, c;
    if (kichco() < 2) return 3;
    a = tren();
    if (checktype() == 1) return 0;
    xoa();
    b = tren(); if (checktype() == 1) return 0;
    xoa(); if (b == 0) { return 2; }
    c = a - (a/b) * b;
    Node* tmp = new Node();
    tmp->fvalue = c;
    tmp->ivalue = 0;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::ineg() {
    int a;
    if (kichco() < 1) return 2;
    a = tren(); if (checktype() == 1) { return 0; }
    xoa();
    Node* tmp = new Node();
    tmp->fvalue = 0;
    tmp->ivalue = -a;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::fneg() {
    float a;
    if (kichco() < 1) return 2;
    a = tren();
    xoa();
    Node* tmp = new Node();
    tmp->fvalue = -a;
    tmp->ivalue = 0;
    tmp->type = 1;
    day(tmp);
    return 1;
}
int operand::iand() {
    int a, b;
    if (kichco() < 2) return 2;
    a = tren(); if (checktype() == 1) { return 0; }
    xoa();
    b = tren(); if (checktype() == 1) { return 0; }
    xoa();
    int c = a & b;
    Node* tmp = new Node();
    tmp->fvalue = 0;
    tmp->ivalue = c;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::ior() {
    int a, b;
    if (kichco() < 2) return 2;
    a = tren(); if (checktype() == 1) return 0;
    xoa();
    b = tren(); if (checktype() == 1) return 0;
    xoa();
    int c = a | b;
    Node* tmp = new Node();
    tmp->fvalue = 0;
    tmp->ivalue = c;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::ieq() {
    int a, b;
    if (kichco() < 2) return 2;
    a = tren(); if (checktype() == 1) return 0;
    xoa();
    b = tren(); if (checktype() == 1) return 0;
    xoa();
    int c = 0;
    if (a == b) { c = 1; }
    Node* tmp = new Node();
    tmp->ivalue = c;
    tmp->fvalue = 0;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::feq() {
    float a, b;
    if (kichco() < 2) return 2;
    a = tren();
    xoa();
    b = tren();
    xoa();
    int c = 0;
    if (a == b) { c = 1; }
    Node* tmp = new Node();
    tmp->ivalue = c;
    tmp->fvalue = 0;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::ineq() {
    int a, b;
    if (kichco() < 2) return 2;
    a = tren(); if (checktype() == 1) return 0;
    xoa();
    b = tren(); if (checktype() == 1) return 0;
    xoa();
    int c = 0;
    if (a != b) { c = 1; }
    Node* tmp = new Node();
    tmp->ivalue = c;
    tmp->fvalue = 0;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::fneq() {
    float a, b;
    if (kichco() < 2) return 2;
    a = tren(); 
    xoa();
    b = tren(); 
    xoa();
    int c = 0;
    if (a != b) { c = 1; }
    Node* tmp = new Node();
    tmp->ivalue = c;
    tmp->fvalue = 0;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::ilt() {
    int a, b;
    if (kichco() < 2) return 2;
    a = tren(); if (checktype() == 1) return 0;
    xoa();
    b = tren(); if (checktype() == 1) return 0;
    xoa();
    int c = 0;
    if (b < a) { c = 1; }
    Node* tmp = new Node();
    tmp->ivalue = c;
    tmp->fvalue = 0;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::flt() {
    float a, b;
    if (kichco() < 2) return 2;
    a = tren();
    xoa();
    b = tren();
    xoa();
    int c = 0;
    if (b < a) { c = 1; }
    Node* tmp = new Node();
    tmp->ivalue = c;
    tmp->fvalue = 0;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::igt() {
    int a, b;
    if (kichco() < 2) return 2;
    a = tren(); if (checktype() == 1) return 0;
    xoa();
    b = tren(); if (checktype() == 1) return 0;
    int c = 0;
    if (b > a) { c = 1; }
    Node* tmp = new Node();
    tmp->ivalue = c;
    tmp->fvalue = 0;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::fgt()
{
    float a, b;
    if (kichco() < 2) return 2;
    a = tren();
    xoa();
    b = tren();
    xoa();
    int c = 0;
    if (b > a) { c = 1; }
    Node* tmp = new Node();
    tmp->ivalue = c;
    tmp->fvalue = 0;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::ibnot() {
    int a;
    if (kichco() < 1) return 2;
    a = tren(); if (checktype() == 1)return 0;
    xoa();
    int c = 0;
    if (a != 0) c = 0;
    else c = 1;
    Node* tmp = new Node();
    tmp->ivalue = c;
    tmp->fvalue = 0;
    tmp->type = 0;
    day(tmp);
    return 1;
}
int operand::i2f() {
    int a;
    if (kichco() < 1) return 2;
    a = tren(); if (checktype() == 1) return 0;
    xoa();
    float c = float(a);
    Node* tmp = new Node();
    tmp->ivalue = 0;
    tmp->fvalue = c;
    tmp->type = 1;
    day(tmp);
    return 1;
}
int operand::f2i() {
    float a;
    if (kichco() < 1) return 2;
    a = tren(); if (checktype() == 0) return 0;
    xoa();
    int c = int(a);
    Node* tmp = new Node();
    tmp->ivalue = c;
    tmp->fvalue = 0;
    tmp->type = 0;
    day(tmp);
    return 1;
}
void StackFrame::doing(string* member, int n) {
    for (int i = 0; i < n; i++) {
        string s = member[i];
        string ins = instructions(s);
        string val = value(s);
        int number = 0;
        if (ins == "iconst" || ins == "fconst" || ins == "istore" || ins == "iload" || ins == "fstore" || ins == "fload") { number = stoi(val); }
        if (ins == "iadd") { int a = b->iadd(); if (a == 0) { throw TypeMisMatch(i + 1); } if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "fadd") { int a = b->fadd(); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "isub") { int a = b->isub(); if (a == 0) { throw TypeMisMatch(i + 1); } if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "fsub") { int a = b->fsub(); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "imul") { int a = b->imul(); if (a == 0) { throw TypeMisMatch(i + 1); }if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "fmul") { int a = b->fmul(); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "idiv") {
            int a = b->idiv();
            if (a == 0) throw TypeMisMatch(i + 1);
            else if (a == 3) { throw StackEmpty(i + 1); }
            else if (a == 2) throw DivideByZero(i + 1);
        }
        else if (ins == "fdiv") {
            int a = b->fdiv();
            if (a == 2) throw DivideByZero(i + 1);
            else if (a == 3) { throw StackEmpty(i + 1); }
        }
        else if (ins == "irem") {
            int a = b->irem();
            if (a == 2) throw DivideByZero(i + 1);
            else if (a == 3) { throw StackEmpty(i + 1); }
            else if (a == 0) throw TypeMisMatch(i + 1);
        }
        else if (ins == "ineg") {
            int a = b->ineg();
            if (a == 2) { throw StackEmpty(i + 1); }
            if (a == 0) throw TypeMisMatch(i + 1);
        }
        else if (ins == "fneg") { int a = b->fneg(); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "iand") { int a = b->iand(); if (a == 0) throw TypeMisMatch(i + 1); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "ior") { int a = b->ior(); if (a == 0)throw TypeMisMatch(i + 1); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "ieq") { int a = b->ieq(); if (a == 0)throw TypeMisMatch(i + 1); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "feq") { int a = b->feq(); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "ineq") { int a = b->ineq(); if (a == 0)throw TypeMisMatch(i + 1); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "fneq") {
            int a = b->fneq(); if (a == 2) { throw StackEmpty(i + 1); }}
        else if (ins == "ilt") { int a = b->ilt(); if (a == 0)throw TypeMisMatch(i + 1); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "flt") { int a = b->flt(); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "igt") { int a = b->igt(); if (a == 0)throw TypeMisMatch(i + 1); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "fgt") { int a = b->fgt(); if (a == 2) { throw StackEmpty(i + 1); } }
        else if (ins == "ibnot") { int a = b->ibnot(); if (a == 0) throw TypeMisMatch(i + 1); if (a == 2) { throw StackEmpty(i + 1); }}
        else if (ins == "iconst") { int a = b->iconst(val); if (a == 0) throw StackFull(i + 1); }
        else if (ins == "fconst") { int a = b->fconst(val); if (a == 0) throw StackFull(i + 1); }
        else if (ins == "top") {
            if (b->iEmpty()) throw StackEmpty(i + 1);
            else cout << b->tren() << endl;
        }
        else if (ins == "iload") {
            if (number > LOCAL_VARIABLE_ARRAY_SIZE - 1) throw ArrayOutOfRange(i + 1);
            else if (new_space[number] == -1) throw UndefinedVariable(i + 1);
            else if (new_space[number] == 1) throw TypeMisMatch(i + 1);
            else { string val = to_string(new_space[number + 1]); b->iconst(val); }
        }
        else if (ins == "fload") {
            if (number > LOCAL_VARIABLE_ARRAY_SIZE - 1) throw ArrayOutOfRange(i + 1);
            else if (new_space[number] == -1) throw UndefinedVariable(i + 1);
            else if (new_space[number] == 0) throw TypeMisMatch(i + 1);
            else {
                string val = to_string(new_space[number + 1]);
                b->fconst(val);
            }
        }
        else if (ins == "istore") {
            if (b->kichco() == 0) { throw StackEmpty(i+1); }
            if (number > LOCAL_VARIABLE_ARRAY_SIZE - 1) throw ArrayOutOfRange(i + 1);
            if (b->checktype() == 1) throw TypeMisMatch(i + 1);
            else {
                int a = b->tren();
                b->xoa();
                new_space[number] = 0;
                new_space[number + 1] = a;
            }
        }
        else if (ins == "fstore") {
            if (b->kichco() == 0) { throw StackEmpty(i + 1); }
            if (number > LOCAL_VARIABLE_ARRAY_SIZE - 1) throw ArrayOutOfRange(i + 1);
            if (b->checktype() == 0) throw TypeMisMatch(i + 1);
            else {
                float a = b->tren();
                b->xoa();
                new_space[number] = 0;
                new_space[number + 1] = a;
            }
        }
        else if (ins == "i2f") { int a = b->i2f(); if (a == 0) throw TypeMisMatch(i + 1); if (a == 2) throw StackEmpty(i + 1); }
        else if (ins == "f2i") { int a = b->f2i(); if (a == 0) throw TypeMisMatch(i + 1); if (a == 2) throw StackEmpty(i + 1); }
        else if (ins == "val") {
            if (number > LOCAL_VARIABLE_ARRAY_SIZE - 1) throw ArrayOutOfRange(i + 1);
            else if (new_space[number + 1] == -1) throw UndefinedVariable(i + 1);
            float a = new_space[number + 1];
            cout << a << endl;
        }
    }
}
void StackFrame::run(string filename) {
    string* member;
    int n = 0;
    ifstream ifs;
    string tmp = "";
    ifs.open(filename);
    while (!ifs.eof()) {
        getline(ifs, tmp);
        n++;
    }
    ifs.close();
    member = new string[n];
    n = 0;
    ifs.open(filename);
    while (!ifs.eof()) {
        getline(ifs, tmp);
        member[n] = tmp;
        n++;
    }
    ifs.close();
    doing(member, n);
    delete[] member;
}
