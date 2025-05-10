#include "Finanial.h"

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