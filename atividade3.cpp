#include <iostream>
#include <string>

using namespace std;

class SensorNivel {
private:
    string tag;
    double minimo;
    double maximo;
    double nivelAtual;

    static double ajustarParaFaixa(double valor, double faixaMinima, double faixaMaxima) {
        if (valor < faixaMinima) {
            return faixaMinima;
        }

        if (valor > faixaMaxima) {
            return faixaMaxima;
        }

        return valor;
    }

public:
    // Faz sentido quando o sensor foi apenas identificado e ainda usara faixa padrao segura.
    explicit SensorNivel(string novaTag)
        : SensorNivel(novaTag, 0.0, 100.0, 0.0) {
        cout << "SensorNivel " << tag << " nasceu pelo construtor minimo.\n";
    }

    // Faz sentido quando o sensor ja precisa nascer calibrado para uma faixa de operacao.
    SensorNivel(string novaTag, double novoMinimo, double novoMaximo)
        : SensorNivel(novaTag, novoMinimo, novoMaximo, novoMinimo) {
        cout << "SensorNivel " << tag << " nasceu com faixa de operacao.\n";
    }

    // Faz sentido quando o sensor deve iniciar ja com faixa e leitura inicial definidas.
    SensorNivel(string novaTag, double novoMinimo, double novoMaximo, double novoNivelAtual)
        : tag(novaTag), minimo(novoMinimo), maximo(novoMaximo), nivelAtual(novoNivelAtual) {
        if (minimo >= maximo) {
            minimo = 0.0;
            maximo = 100.0;
        }

        nivelAtual = ajustarParaFaixa(nivelAtual, minimo, maximo);
    }

    void exibirResumo() const {
        cout << "[SensorNivel] " << tag
             << " | faixa: " << minimo << " a " << maximo
             << " | nivel atual: " << nivelAtual << "\n";
    }
};

class Bomba {
private:
    string tag;
    double velocidade;
    bool ligada;

    static double ajustarVelocidade(double novaVelocidade) {
        if (novaVelocidade < 0.0) {
            return 0.0;
        }

        if (novaVelocidade > 100.0) {
            return 100.0;
        }

        return novaVelocidade;
    }

public:
    // Faz sentido para cadastrar a bomba com identificacao basica e parada em estado seguro.
    explicit Bomba(string novaTag)
        : Bomba(novaTag, 0.0, false) {
        cout << "Bomba " << tag << " nasceu pelo construtor minimo.\n";
    }

    // Faz sentido quando a bomba ja deve nascer com velocidade e estado de operacao definidos.
    Bomba(string novaTag, double velocidadeInicial, bool estadoInicial)
        : tag(novaTag), velocidade(ajustarVelocidade(velocidadeInicial)), ligada(estadoInicial) {
        cout << "Bomba " << tag << " nasceu com parametros de operacao.\n";
    }

    void exibirResumo() const {
        cout << "[Bomba] " << tag
             << " | velocidade: " << velocidade << "%"
             << " | estado: " << (ligada ? "ligada" : "desligada") << "\n";
    }
};

class ControladorTanque {
private:
    string tag;
    double setpoint;
    double ganhoProporcional;

public:
    // Faz sentido quando o controlador foi identificado, mas ainda usara ajuste padrao seguro.
    explicit ControladorTanque(string novaTag)
        : ControladorTanque(novaTag, 50.0, 1.0) {
        cout << "ControladorTanque " << tag << " nasceu pelo construtor minimo.\n";
    }

    // Faz sentido quando o controlador ja precisa iniciar com alvo e ganho definidos.
    ControladorTanque(string novaTag, double novoSetpoint, double novoGanhoProporcional)
        : tag(novaTag), setpoint(novoSetpoint), ganhoProporcional(novoGanhoProporcional) {
        if (ganhoProporcional <= 0.0) {
            ganhoProporcional = 1.0;
        }

        cout << "ControladorTanque " << tag << " nasceu com parametros de controle.\n";
    }

    void exibirResumo() const {
        cout << "[ControladorTanque] " << tag
             << " | setpoint: " << setpoint
             << " | Kp: " << ganhoProporcional << "\n";
    }
};

int main() {
    SensorNivel sensorBasico("LT-101");
    SensorNivel sensorCalibrado("LT-102", 0.0, 5.0);

    Bomba bombaBasica("P-101");
    Bomba bombaConfigurada("P-102", 75.0, true);

    ControladorTanque controladorBasico("LIC-101");
    ControladorTanque controladorConfigurado("LIC-102", 3.5, 2.0);

    cout << "\nResumo dos gemeos digitais criados:\n";
    sensorBasico.exibirResumo();
    sensorCalibrado.exibirResumo();
    bombaBasica.exibirResumo();
    bombaConfigurada.exibirResumo();
    controladorBasico.exibirResumo();
    controladorConfigurado.exibirResumo();

    return 0;
}
