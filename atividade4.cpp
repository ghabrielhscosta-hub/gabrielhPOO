#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class AtivoCampo {
private:
    string tag;
    bool bloqueado;

protected:
    string area;
    void redefinirArea(const string& novaArea) {
        area = novaArea;
    }

public:
    AtivoCampo(const string& novaTag, const string& novaArea)
        : tag(novaTag), bloqueado(false), area(novaArea) {}

    string getTag() const {
        return tag;
    }

    bool estaBloqueado() const {
        return bloqueado;
    }

    void bloquear() {
        bloqueado = true;
    }

    void liberar() {
        bloqueado = false;
    }

    // public: leitura da area sem expor escrita irrestrita.
    string getArea() const {
        return area;
    }
};

class SensorNivel : public AtivoCampo {
private:
    // private: estado especifico do sensor nao deve ser alterado externamente.
    double nivelAtual;
    double limiteAlto;

public:
    // public: construtor reutiliza a base e permite criar o sensor corretamente.
    SensorNivel(const string& novaTag, const string& novaArea,
                double nivelInicial, double novoLimiteAlto)
        : AtivoCampo(novaTag, novaArea),
          nivelAtual(nivelInicial >= 0 ? nivelInicial : 0),
          limiteAlto(novoLimiteAlto >= 0 ? novoLimiteAlto : 0) {}

    // public: metodo de negocio para validar alteracao de nivel.
    bool atualizarNivel(double novoNivel) {
        if (estaBloqueado()) {
            return false;
        }

        if (novoNivel < 0) {
            return false;
        }

        nivelAtual = novoNivel;
        return true;
    }

    // public: resumo legivel do objeto.
    void exibirResumo() const {
        cout << "SensorNivel\n";
        cout << "  Tag: " << getTag() << "\n";
        cout << "  Area: " << getArea() << "\n";
        cout << "  Bloqueado: " << (estaBloqueado() ? "sim" : "nao") << "\n";
        cout << "  Nivel atual: " << fixed << setprecision(2) << nivelAtual << "\n";
        cout << "  Limite alto: " << fixed << setprecision(2) << limiteAlto << "\n";
    }

    // friend: usado apenas para inspecao tecnica pontual e localizada.
    friend void inspecaoTecnicaSensor(const SensorNivel& sensor);
};

// Definicao localizada da funcao friend para inspecao tecnica.
void inspecaoTecnicaSensor(const SensorNivel& sensor) {
    cout << "[Inspecao tecnica do sensor]\n";
    cout << "  Tag........: " << sensor.getTag() << "\n";
    cout << "  Area.......: " << sensor.getArea() << "\n";
    cout << "  Nivel atual: " << fixed << setprecision(2) << sensor.nivelAtual << "\n";
    cout << "  Limite alto: " << fixed << setprecision(2) << sensor.limiteAlto << "\n";
}

class BombaDosadora : public AtivoCampo {
private:
    // private: vazao eh estado interno da bomba e deve mudar por validacao.
    double vazaoPercentual;

public:
    // public: construtor reutiliza a base e evita duplicacao.
    BombaDosadora(const string& novaTag, const string& novaArea,
                  double vazaoInicial)
        : AtivoCampo(novaTag, novaArea),
          vazaoPercentual((vazaoInicial >= 0 && vazaoInicial <= 100) ? vazaoInicial : 0) {}

    // public: metodo de negocio para validar ajuste de vazao.
    bool ajustarVazao(double novaVazao) {
        if (estaBloqueado()) {
            return false;
        }

        if (novaVazao < 0 || novaVazao > 100) {
            return false;
        }

        vazaoPercentual = novaVazao;
        return true;
    }

    // public: comportamento da derivada reaproveitando o recurso protegido da base.
    void moverParaArea(const string& novaArea) {
        redefinirArea(novaArea);
    }

    // public: resumo legivel do objeto.
    void exibirResumo() const {
        cout << "BombaDosadora\n";
        cout << "  Tag: " << getTag() << "\n";
        cout << "  Area: " << getArea() << "\n";
        cout << "  Bloqueado: " << (estaBloqueado() ? "sim" : "nao") << "\n";
        cout << "  Vazao (%): " << fixed << setprecision(2) << vazaoPercentual << "\n";
    }
};

int main() {
    SensorNivel sensor("LT-101", "Tanque A", 35.5, 80.0);
    BombaDosadora bomba("P-201", "Dosagem B", 45.0);

    cout << "=== Atualizando estados ===\n";
    cout << "Atualizacao de nivel para 42.3: "
         << (sensor.atualizarNivel(42.3) ? "ok" : "falhou") << "\n";

    cout << "Ajuste de vazao para 60: "
         << (bomba.ajustarVazao(60.0) ? "ok" : "falhou") << "\n";

    bomba.moverParaArea("Dosagem C");

    sensor.bloquear();
    cout << "Atualizacao de nivel com sensor bloqueado: "
         << (sensor.atualizarNivel(50.0) ? "ok" : "falhou") << "\n";

    cout << "\n=== Resumo dos ativos ===\n";
    sensor.exibirResumo();
    cout << "\n";
    bomba.exibirResumo();
    cout << "\n\n";

    inspecaoTecnicaSensor(sensor);

    return 0;
}