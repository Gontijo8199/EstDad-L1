#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"

#include <iostream>
using namespace std;

Sala::Sala(int vagas) {
    this->vagas = vagas;

    for (int i=0; i<5; i++)
        for (int j=0; j<14; j++) 
            this->ocupacao[i][j] = ""; // nenhuma disciplina em nenhum horário
}

ReservationSystem::ReservationSystem(int room_count, int* room_capacities){
    this->room_count = room_count;
    int *room_capacities_ordenado = new int[room_count];
    
    for (int i=0; i<room_count; i++)
        room_capacities_ordenado[i] = room_capacities[i];

    // ordenando as salas na ordem crescente de vagas para que, ao reservar uma sala, 
    // seja alocada aqula com a menor capacidade que suporta a reserva
    for (int i=0; i<room_count; i++)
        for (int j=0; j<room_count-i-1; j++) // < r_c -i -1 pois ja tem i ordenados no final
            if (room_capacities_ordenado[j] > room_capacities_ordenado[j+1]) {
                int temp = room_capacities_ordenado[j];
                room_capacities_ordenado[j] = room_capacities_ordenado[j+1];
                room_capacities_ordenado[j+1] = temp;
            } 

    // array de ponteiros pois a sala sempre tem que possuir sua capacidade na inicialização
    this->salas = new Sala*[room_count]; 
    for (int i = 0; i < room_count; i++) 
        this->salas[i] = new Sala(room_capacities_ordenado[i]);

    delete[] room_capacities_ordenado;
}

ReservationSystem::~ReservationSystem(){
    for (int i=0; i<room_count; i++) 
        delete this->salas[i];
    delete[] this->salas;
}


const string semana[] = {"segunda", "terca", "quarta", "quinta", "sexta"};
bool ReservationSystem::reserve(ReservationRequest request){

    int start = request.getStartHour() - 7;
    int end = request.getEndHour() - 7;

    // Uma reserva que começa depois ou na hora que acaba não é válida
    if (end <= start) 
        return false;

    // uma reserva iniciando antes das 7 ou depois das 21 não é válida
    if (start < 0 || end > 14)
        return false;
    
    // identificando o dia informado
    int dia = -1;
    for (int idx=0; idx<5; idx++)
        if (request.getWeekday() == semana[idx]){
            dia=idx;
            break;
        }

    // verificando se o dia é válido
    if (dia == -1) 
        return false;

    // percorre as salas e avalia se algum bloco já está ocupado 
    // (bloco iniciado em [end] não é uma preocupação pois reservas podem ser feitas uma seguida da outra)
    int vagas_necessarias = request.getStudentCount(), sala = -1;
    for (int i=0; i<room_count; i++) 
        if (vagas_necessarias <= this->salas[i]->vagas) {
            bool valido = true;
            for (int hr=start; hr<end; hr++) 
                if (this->salas[i]->ocupacao[dia][hr] != "") {
                    // caso de algum bloco estar ocupado
                    valido = false;
                    break;
                }
            if (valido) {
                sala = i;
                break;
            }
        }

    // caso algum boloco no meio esteja ocupado, sala será -1
    if (sala == -1) 
        return false;

    // salvando a reserva
    string materia = request.getCourseName();
    for (int hr = start; hr < end; hr++) 
        this->salas[sala]->ocupacao[dia][hr] = materia;

    return true;
}

bool ReservationSystem::cancel(string course_name){
    bool canceled = false;
    for (int i = 0; i< this->room_count; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 14; k++)
                if (this->salas[i]->ocupacao[j][k] == course_name) {
                    // remove todas as reservas para essa disciplina
                    this->salas[i]->ocupacao[j][k] = "";
                    canceled = true;
                }
    
    return canceled;
}

void ReservationSystem::printSchedule() {
    for (int i = 0; i< this->room_count; i++) {
        cout << "Sala: " << i <<  endl;
        for (int j = 0; j < 5; j++){
            cout << "Dia: " << semana[j] << endl;
            int start = -1;
            for (int k = 0; k < 14; k++) {
                if (this->salas[i]->ocupacao[j][k] != "") {
                    if (k == 0) 
                        start = 0;
                    else if (this->salas[i]->ocupacao[j][k] != this->salas[i]->ocupacao[j][k - 1])
                        start = k;

                    // avalia se o bloco de horários da reserva encerrou para que um bloco contíguo seja impresso junto 
                    if (k == 13)        // + 1 pois o horário de fim da aula é o horário de início do próximo bloco
                        cout << "\t> " << (start + 7) << "h ~ " << (13 + 7 + 1) << "h: " << this->salas[i]->ocupacao[j][k] << endl;
                    else if (this->salas[i]->ocupacao[j][k] != this->salas[i]->ocupacao[j][k + 1])
                        cout << "\t> " << (start + 7) << "h ~ " << (k + 7 + 1) << "h: " << this->salas[i]->ocupacao[j][k] << endl;                        
                }
            }
        }
        if (i < this->room_count - 1)
            cout  << endl;
    }
}