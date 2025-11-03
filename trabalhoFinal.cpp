#include <iostream>
#include <queue>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

struct pacientes {
    string senha;
    char prioridade;
    int chegada;
};

int tempoEmMin(int hh, int mm) {
    return hh * 60 + mm;
}

int main() {
    queue<pacientes> prioV, prioA, prioD, prioB;
    string comando;
    int totalAtendidos = 0;
    int totalNaFila = 0;
    map<char, int> atendidos = {{'V',0}, {'A',0}, {'D',0}, {'B',0}};
    int picoLotacao = 0;
    int esperaMaxima = 0;

    while (cin >> comando) {
        comando[0] = toupper(comando[0]);

        if (comando == "Q"){
            break;
        }

        if (comando == "C") {
            pacientes p;
            int hh, mm;
            cin >> p.senha >> p.prioridade >> hh >> mm;
            
            if (hh < 0 || hh > 23 || mm < 0 || mm > 59) {
                cerr << "Horario invalido: " << hh << ":" << mm << endl;
                continue;
            }
            
            p.chegada = tempoEmMin(hh, mm);
            p.prioridade = toupper(p.prioridade);

            if (p.prioridade != 'V' && p.prioridade != 'A' && 
                p.prioridade != 'D' && p.prioridade != 'B') {
                cerr << "Prioridade inválida: " << p.prioridade << endl;
                continue;
            }

            if (p.prioridade == 'V') prioV.push(p);
            else if (p.prioridade == 'A') prioA.push(p);
            else if (p.prioridade == 'D') prioD.push(p);
            else if (p.prioridade == 'B') prioB.push(p);

            totalNaFila++;
            picoLotacao = max(picoLotacao, totalNaFila);
        }

        else if (comando == "A") {
            int hh, mm;
            cin >> hh >> mm;
            
            if (hh < 0 || hh > 23 || mm < 0 || mm > 59) {
                cerr << "Horário inválido: " << hh << ":" << mm << endl;
                continue;
            }
            
            int tempoAtual = tempoEmMin(hh, mm);

            if (prioV.empty() && prioA.empty() && prioD.empty() && prioB.empty()) {
                cout << setw(2) << setfill('0') << hh << " "
                     << setw(2) << setfill('0') << mm << " "
                     << "Sem pacientes aguardando atendimento" << endl;
                continue;
            }

            pacientes p;
            if (!prioV.empty()) { p = prioV.front(); prioV.pop(); }
            else if (!prioA.empty()) { p = prioA.front(); prioA.pop(); }
            else if (!prioD.empty()) { p = prioD.front(); prioD.pop(); }
            else { p = prioB.front(); prioB.pop(); }

            totalNaFila--;
            
            int espera = tempoAtual - p.chegada;
            
            if (espera < 0) {
                espera += 24 * 60;
            }
            
            esperaMaxima = max(esperaMaxima, espera);
            atendidos[p.prioridade]++;
            totalAtendidos++;
        }

        else if (comando == "D") {
            cout << "V:" << prioV.size()
                 << " A:" << prioA.size()
                 << " D:" << prioD.size()
                 << " B:" << prioB.size()
                 << " | Atendidos:" << totalAtendidos << endl;
        }
    }

    cout << "--- RELATORIO FINAL ---" << endl;
    cout << "Total atendidos: " << totalAtendidos << endl;
    cout << "Por prioridade: V=" << atendidos['V']
         << " A=" << atendidos['A']
         << " D=" << atendidos['D']
         << " B=" << atendidos['B'] << endl;
    cout << "Pico de lotacao: " << picoLotacao << endl;
    cout << "Espera maxima: " << esperaMaxima << " min" << endl;

    return 0;
}
