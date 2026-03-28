#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"

#include <iostream>
using namespace std;



ReservationSystem::ReservationSystem(int room_count, int* room_capacities){
    this->room_count = room_count;
    this->room_capacities = room_capacities;

    // buscaremos algo como [sala][dia][horario] = "nome_do_curso" 
    // acredito que esse armazenamento é melhor do que os outros q pensei sem stl
    // porque eu itero n (room_cout), depois 5 fixo (dias da semana), 14 fixo (horarios possivéis), 
    // e depois faço uma operação (leitura ou escrita), isso custa então 21n, o que é O(n), em big O
    // o uso de this é pra deixar bem explicito

    this->schedule = new std::string**[this->room_count]; // é bem esquisito a implementação da matrx3d
    for (int i=0; i< this->room_count; i++){
        this->schedule[i] = new string*[5]; // seg,ter,qua,qui,sex
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


    if (request.getStartHour() < 7 || request.getEndHour() > 21)
        return false;
    
    int k = request.getStartHour() - 7;
    
    
    int j = -1;
    for (int idx=0; idx<5; idx++){
        if (request.getWeekday() == semana[idx]){
            j=idx;
            break;
        }
    }

    
    int i = -1;
    for (int idx = 0; idx < this->room_count; idx++){
        if (request.getStudentCount() < this->room_capacities[idx]){
            i=idx;
            break;
        }
    }   

    if (j == -1 || i == -1)
        return false;

    if (this->schedule[i][j][k] != "")
        return false;

    this->schedule[i][j][k] = request.getCourseName();

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

    for (int i = 0; i< this->room_count; i++){
    cout << "Sala: " << i <<  endl;
        for (int j = 0; j < 5; j++){
        cout << "Dia: " << semana[j] << endl;
            for (int k = 0; k < 14; k++)
                if (this->schedule[i][j][k] != "")
                cout << "   > Horario:" << (k+7) << "-" << (k+8) << "h  - " << this->schedule[i][j][k] << endl; 
        }
        if (i < this->room_count - 1)
            cout  << endl;
    }
}