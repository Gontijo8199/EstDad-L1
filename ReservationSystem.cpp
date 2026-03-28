#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"

#include <iostream>
using namespace std;

ReservationSystem::ReservationSystem(int room_count, int* room_capacities){
    this->room_count = room_count;
    this->room_capacities = new int[room_count]; // evitar o caso em que o array original sai de escopo
    for (int i = 0; i < room_count; i++) {
        this->room_capacities[i] = room_capacities[i];
    }

    // Para armazenar o status das salas em cada horário sem usar estruturas do stl,
    // definimos uma estrutura com [sala][dia][horário] = "disciplina" de modo a 
    // associar cada sala a 5 dias da semana e cada dia aos 14 horários de reserva.
    // Assim, para cada sala, podemos podemos avaliar seu status de reserva em cada 
    // horário em tempo constante, e avaliar o status de todas as salas na ordem 
    // assintótica de O(n).  

    // TODO: implementar uma classe para sala, e implementar uma lista de salas aqui

    this->schedule = new string**[this->room_count]; // 1 array de array de string p/ cada sala
    for (int i=0; i< this->room_count; i++){
        this->schedule[i] = new string*[5]; // seg, ter, qua, qui, sex
        for (int j=0; j<5; j++){
            this->schedule[i][j] = new string[14]; // temos 7-8,8-9,9-10, etc.... #[7,21] = 14
            for (int k = 0; k<14; k++){
                this->schedule[i][j][k] = ""; // nenhum
            }
        }
    }
}

ReservationSystem::~ReservationSystem(){
    for (int i=0; i< this->room_count; i++){
        for (int j=0; j<5; j++){
            delete[] this->schedule[i][j];
        }
        delete[] this->schedule[i];
    }
    delete[] this->schedule;
}


const string semana[] = {"segunda", "terca", "quarta", "quinta", "sexta"};


bool ReservationSystem::reserve(ReservationRequest request){

    int start = request.getStartHour() - 7;
    int end = request.getEndHour() - 7;

    if (end <= start) { // não faz sentido uma reserva começar depois ou na hora que acaba
        return false;
    }

    if (start < 0 || end > 14)
        return false;
    
    int dia = -1;
    for (int idx=0; idx<5; idx++){
        if (request.getWeekday() == semana[idx]){
            dia=idx;
            break;
        }
    }

    int sala = -1;
    for (int idx = 0; idx < this->room_count; idx++){
        if (request.getStudentCount() <= this->room_capacities[idx]){
            bool valido = true;
            for (int hr = start; hr < end; hr++) { 
                // validando requests que incluem mais de um bloco de horário. ex: 7-9 ou 9-12
                // verifica se a sala está livre em cada bloco de horário solicitado
                if (this->schedule[idx][dia][hr] != "") {
                    valido = false;
                    break;
                }
            }
            if (valido) {
                sala=idx;
                break;
            }
        }
    }   

    if (dia == -1 || sala == -1) // caso algum boloco no meio esteja ocupado, sala será -1
        return false;

    // if (this->schedule[sala][dia][start] != "") // não é mais necessário pois se confere no loop anterior
    //     return false;

    for (int hr = start; hr < end; hr++) { // 
        this->schedule[sala][dia][hr] = request.getCourseName();
    }

    return true;
}

bool ReservationSystem::cancel(string course_name){
    bool canceled = false;
    for (int i = 0; i< this->room_count; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 14; k++)
                if (this->schedule[i][j][k] == course_name){
                    this->schedule[i][j][k] = "";
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
                    if (this->schedule[i][j][k] != "") {
                        if (k == 0) 
                            start = 0;
                        else if (this->schedule[i][j][k] != this->schedule[i][j][k - 1])
                            start = k;
                        if (k == 13)
                            cout << "\t> " << (start + 7) << "h ~ " << (13 + 7) << "h: " << this->schedule[i][j][k] << endl;
                        else if (this->schedule[i][j][k] != this->schedule[i][j][k + 1])
                            cout << "\t> " << (start + 7) << "h ~ " << (k + 7) << "h: " << this->schedule[i][j][k] << endl;                        
                    }
                }
        }
        if (i < this->room_count - 1)
            cout  << endl;
    }
}