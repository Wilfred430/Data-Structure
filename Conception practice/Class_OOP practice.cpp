#include <iostream>
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

int main()
{
    Finanial Fin;
    int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Fin.set_array(b, 10);
    Finanial Fial(Fin);
    Fial.display();
    Fial.set_data(1000);
    Fial.set_rate(151.165431);
    cout << Fial.get_data() << endl;
    cout << Fial.get_rate() << endl;

    return 0;
}