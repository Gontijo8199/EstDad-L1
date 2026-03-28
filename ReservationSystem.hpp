#ifndef ReservationSystem_hpp
#define ReservationSystem_hpp

#include "ReservationRequest.hpp"
#include <iostream>
using namespace std;


struct Sala {
    bool disponivel;
    int capacidade;
};

class ReservationSystem {

private:
    int room_count;
    int* room_capacities;
    // buscaremos algo como [sala][dia][horario] = "nome_do_curso" 

    string*** schedule;


public:

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};

#endif