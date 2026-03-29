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

    for (int i=0; i<room_count; i++)
        for (int j=0; j<room_count-i-1; j++) // < r_c -i -1 pois ja tem i ordenados no final
            if (room_capacities[j] > room_capacities[j+1]) {
                int temp = room_capacities[j];
                room_capacities[j] = room_capacities[j+1];
                room_capacities[j+1] = temp;
            } 

    // array de ponteiros pois a sala sempre tem que possuir sua capacidade
    this->salas = new Sala*[room_count]; 
    for (int i = 0; i < room_count; i++) 
        this->salas[i] = new Sala(room_capacities[i]);
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

    if (end <= start) // não faz sentido uma reserva começar depois ou na hora que acaba
        return false;

    if (start < 0 || end > 14)
        return false;
    
    int dia = -1;
    for (int idx=0; idx<5; idx++)
        if (request.getWeekday() == semana[idx]){
            dia=idx;
            break;
        }

    if (dia == -1) 
        return false;

    bool sucesso = false;
    int vagas_necessarias = request.getStudentCount(), sala = -1;
    for (int i=0; i<room_count; i++) 
        if (vagas_necessarias <= this->salas[i]->vagas) {
            bool valido = true;
            for (int hr=start; hr<end; hr++) 
                if (this->salas[i]->ocupacao[dia][hr] != "") {
                    valido = false;
                    break;
                }
            if (valido) {
                sala = i;
                break;
            }
        }

    if (sala == -1) // caso algum boloco no meio esteja ocupado, sala será -1
        return false;

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
                if (this->salas[i]->ocupacao[j][k] == course_name){
                    this->salas[i]->ocupacao[j][k] = "";
                    canceled = true;
                }
    
    return canceled;
}

void ReservationSystem::printSchedule(){

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
                        if (k == 13)
                            cout << "\t> " << (start + 7) << "h ~ " << (13 + 7) << "h: " << this->salas[i]->ocupacao[j][k] << endl;
                        else if (this->salas[i]->ocupacao[j][k] != this->salas[i]->ocupacao[j][k + 1])
                            cout << "\t> " << (start + 7) << "h ~ " << (k + 7) << "h: " << this->salas[i]->ocupacao[j][k] << endl;                        
                    }
                }
        }
        if (i < this->room_count - 1)
            cout  << endl;
    }
}