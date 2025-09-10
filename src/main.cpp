#include <Foco.hpp>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    Foco foco;
    foco.Encender();
    cout << foco.LeerEstado() << endl;
    return 0;
}
