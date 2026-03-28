#include<iostream> 
#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"

using namespace std;

int main(){
    
    int room_count = 2;
    int room_capacity[] = {45, 30};
    ReservationSystem r = ReservationSystem(room_count, room_capacity);

    cout << "gerando sistema com 2 salas, de 45 e 30 vagas" << endl;

    // Caso de reserva antes das 7 horas
    ReservationRequest request = ReservationRequest("Cálculo", "segunda", 6, 7, 40); 
    bool result = r.reserve(request);
    cout << "reserva 6h às 12h: " << (result ? "sucesso" : "falha");
    cout << endl;

    // Caso de reserva após as 21 horas
    request = ReservationRequest("Cálculo", "terça", 23, 24, 40);
    result = r.reserve(request);
    cout << "reserva 23h às 24h: " << (result ? "sucesso" : "falha") << endl;

    // Caso de reserva com horário de início antes do horário de fim 
    request = ReservationRequest("Cálculo", "quinta", 12, 9, 40);
    result = r.reserve(request);
    cout << "reserva 12h às 9h: " << (result ? "sucesso" : "falha") << endl;

    // Caso de reserva com horário de início igual ao de fim
    request = ReservationRequest("Cálculo", "quinta", 12, 12, 40);
    result = r.reserve(request);
    cout << "reserva 12h às 12h: " << (result ? "sucesso" : "falha") << endl;
    
    // Caso de reserva válida para sala de 45 vagas
    request = ReservationRequest("Cálculo", "quinta", 7, 10, 40);
    result = r.reserve(request);
    cout << "reserva Cálculo, quinta, 7h às 10h, 40 alunos: " << (result ? "sucesso" : "falha") << endl;
    cout << "status atual: " << endl;
    r.printSchedule();
    
    // Caso de conflito de reservas
    request = ReservationRequest("Redes", "quinta", 9, 12, 35);
    result = r.reserve(request);
    cout << "reserva Redes, quinta, 9h às 12h, 35 alunos: " << (result ? "sucesso" : "falha") << endl;
    
    // Caso de reserva válida para outro dia
    request = ReservationRequest("Redes", "segunda", 9, 12, 35);
    result = r.reserve(request);
    cout << "reserva Redes, segunda, 9h às 12h, 35 alunos: " << (result ? "sucesso" : "falha") << endl;
    
    // Caso sem conflito pois exige menos vagas
    request = ReservationRequest("TACD", "quinta", 9, 12, 15);
    result = r.reserve(request);
    cout << "reserva TACD, quinta, 9h às 12h, 15 alunos: " << (result ? "sucesso" : "falha") << endl;
    cout << "status atual: " << endl;
    r.printSchedule();

    // Teste de cancelamento de reserva
    cout << "cancelar reservas de Cálculo: " << (r.cancel("Cálculo") ? "sucesso" : "falha") << endl;
    cout << "status atual: " << endl;
    r.printSchedule();
    
    return 0;
}