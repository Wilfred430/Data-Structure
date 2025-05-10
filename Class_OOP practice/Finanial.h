#include<iostream>
using namespace std;

class Finanial
{
private:
    int *array;
    int data;
    double rate;
    int length;

public:
    Finanial();
    Finanial(const Finanial &F);
    ~Finanial();
    void display();
    friend ostream & operator << (ostream & out, const Finanial& F);
    Finanial operator+(const Finanial& right);
    Finanial& operator=(const Finanial& other);
    void set_data(const int da);
    void set_rate(const double ra);
    void set_array(const int b[], const int len);
    int get_data();
    double get_rate();
};

Finanial::Finanial() : array(nullptr), data(0), rate(0), length(0) {}

Finanial::Finanial(const Finanial &F) : data(F.data), rate(F.rate)
{
    this->length = F.length;
    this->array = new int[this->length];
    for (int i = 0; i < this->length; i++)
    {
        this->array[i] = F.array[i];
    }
}

Finanial::~Finanial()
{
    delete[] this->array;
}

void Finanial::display()
{
    for (int i = 0; i < this->length; i++)
    {
        cout << this->array[i] << " ";
    }
    cout << endl;
}

ostream & operator << (ostream & out, const Finanial& F)
{
    out << "data: " << F.data << " , " << "rate: " << F.rate << endl;
    for(int i=0;i<F.length;i++)
    {
        out << F.array[i] << " ";
    }
    out << endl;

    return out;
}

Finanial Finanial::operator+(const Finanial& right) {
    Finanial result;
    result.data = this->data + right.data;
    result.rate = this->rate + right.rate;
    result.length = std::max(this->length, right.length);
    result.array = new int[result.length];
    for (int i = 0; i < result.length; i++) {
        int leftVal = (i < this->length) ? this->array[i] : 0;
        int rightVal = (i < right.length) ? right.array[i] : 0;
        result.array[i] = leftVal + rightVal;
    }
    return result;
}

Finanial& Finanial::operator=(const Finanial& other) {
    if (this != &other) {
        delete[] array;
        data = other.data;
        rate = other.rate;
        length = other.length;
        array = new int[length];
        for (int i = 0; i < length; i++) {
            array[i] = other.array[i];
        }
    }
    return *this;
}

void Finanial::set_data(const int da)
{
    this->data = da;
}

void Finanial::set_rate(const double ra)
{
    this->rate = ra;
}

void Finanial::set_array(const int b[], const int len)
{
    this->length = len;
    this->array = new int[len];
    for (int i = 0; i < len; i++)
    {
        this->array[i] = b[i];
    }
}

int Finanial::get_data()
{
    return this->data;
}

double Finanial::get_rate()
{
    return this->rate;
}