#include <iostream>
#include <string>

using namespace std;

class AtivoCampo {
private:
    // private: protege o estado importante da base.
    string tag;
    bool bloqueado;

public:
    // public: permite criar o objeto já com estado inicial controlado.
    AtivoCampo(string novaTag, bool estadoInicial = false)
        : tag(novaTag), bloqueado(estadoInicial) {}

    // public: acesso controlado à tag, sem expor escrita direta.
    string getTag() const {
        return tag;
    }

    // public: consulta controlada do estado de bloqueio.
    bool estaBloqueado() const {
        return bloqueado;
    }

    // public: alteração controlada do bloqueio.
    void bloquear() {
        bloqueado = true;
    }

    // public: alteração controlada do bloqueio.
    void desbloquear() {
        bloqueado = false;
    }
};

class SensorNivel : public AtivoCampo {
private:
    // private: o nível deve ser alterado somente por método validador.
    double nivel;

public:
    // public: constrói reaproveitando a classe-base.
    SensorNivel(string novaTag, double nivelInicial, bool estadoInicial = false)
        : AtivoCampo(novaTag, estadoInicial), nivel(0.0) {
        atualizarNivel(nivelInicial);
    }

    // public: valida a alteração de nível antes de gravar.
    bool atualizarNivel(double novoNivel) {
        if (estaBloqueado()) {
            return false;
        }

        if (novoNivel < 0.0) {
            return false;
        }

        nivel = novoNivel;
        return true;
    }

    // public: leitura controlada do nível.
    double getNivel() const {
        return nivel;
    }

    // public: resumo legível do objeto.
    void exibirResumo() const {
        cout << "SensorNivel | Tag: " << getTag()
             << " | Bloqueado: " << (estaBloqueado() ? "Sim" : "Nao")
             << " | Nivel: " << nivel << endl;
    }

    // friend: usado apenas para inspecao tecnica localizada.
    friend void inspecionarSensor(const SensorNivel& sensor);
};

// friend definida fora da classe, apenas para inspecao tecnica.
void inspecionarSensor(const SensorNivel& sensor) {
    cout << "[Inspecao tecnica] "
         << "Tag=" << sensor.getTag()
         << ", Bloqueado=" << (sensor.estaBloqueado() ? "Sim" : "Nao")
         << ", Nivel=" << sensor.nivel << endl;
}

class BombaDosadora : public AtivoCampo {
private:
    // private: a vazão deve ser alterada somente por método validador.
    double vazao;

public:
    // public: constrói reaproveitando a classe-base.
    BombaDosadora(string novaTag, double vazaoInicial, bool estadoInicial = false)
        : AtivoCampo(novaTag, estadoInicial), vazao(0.0) {
        ajustarVazao(vazaoInicial);
    }

    // public: valida a alteração de vazão antes de gravar.
    bool ajustarVazao(double novaVazao) {
        if (estaBloqueado()) {
            return false;
        }

        if (novaVazao < 0.0) {
            return false;
        }

        vazao = novaVazao;
        return true;
    }

    // public: leitura controlada da vazão.
    double getVazao() const {
        return vazao;
    }

    // public: resumo legível do objeto.
    void exibirResumo() const {
        cout << "BombaDosadora | Tag: " << getTag()
             << " | Bloqueado: " << (estaBloqueado() ? "Sim" : "Nao")
             << " | Vazao: " << vazao << endl;
    }
};

int main() {
    SensorNivel sensor("SN-101", 42.5);
    BombaDosadora bomba("BD-201", 18.0);

    sensor.atualizarNivel(55.2);
    bomba.ajustarVazao(27.8);

    sensor.bloquear();
    if (!sensor.atualizarNivel(70.0)) {
        cout << "Falha ao atualizar nivel do sensor bloqueado." << endl;
    }

    cout << endl;
    sensor.exibirResumo();
    bomba.exibirResumo();

    cout << endl;
    inspecionarSensor(sensor);

    return 0;
}