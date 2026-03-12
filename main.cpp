#include <iostream>
#include <string>
using namespace std;

class Carro {
  public:
    string marca;
    string modelo;
    int ano;

    void acelerar(int taxa) {
      velocidadeInstantanea += taxa;
    }

    int getVelocidade() {
      return velocidadeInstantanea;
    }

  private:
    int velocidadeInstantanea = 0;
};

int main() {
  Carro carro1;

  carro1.marca = "Toyota";
  carro1.modelo = "Corolla";
  carro1.ano = 2012;

  carro1.acelerar(10);
  carro1.acelerar(20);
  carro1.acelerar(15);

  cout << "Carro: " << carro1.marca << " " << carro1.modelo << "\n";
  cout << "Ano: " << carro1.ano << "\n";
  cout << "Velocidade final: " << carro1.getVelocidade() << " km/h\n";

  return 0;
}