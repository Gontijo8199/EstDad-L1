#include "ReservationRequest.hpp"
#include <iostream>
using namespace std;

class ReservationSystem {

private:
    int room_count;
    int* room_capacities;
    // XXX: Ainda falta implementar
    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...

public:

    ReservationSystem(int room_count, int* room_capacities){
        this->room_count = room_count;
        this->room_capacities = room_capacities;
    }
    ~ReservationSystem(){
       delete[] room_capacities; 
    }

    bool reserve(ReservationRequest request){
        
        return 0;
    }
    bool cancel(std::string course_name){
        
        return 0;
    }

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};

