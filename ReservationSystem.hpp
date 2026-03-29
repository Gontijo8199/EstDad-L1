#ifndef ReservationSystem_hpp
#define ReservationSystem_hpp

#include "ReservationRequest.hpp"
#include <iostream>
using namespace std;

class Sala {
public:
    int vagas;
    string ocupacao[5][14];

    Sala(int vagas);
};

class ReservationSystem {
private:
    int room_count;

    Sala** salas;

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