#include "Finanial.h"

int main()
{
    Finanial F;
    int b[10] = {1,4,5,5,2,4,23,10,134,54};
    F.set_array(b,10);
    F.set_data(100);
    F.set_rate(14314.1341);
    cout << F << endl;

    Finanial F_add(F);
    F_add.set_data(-100);
    F_add.set_rate(-1414.15);
    cout << F + F_add << endl;

    return 0;
}