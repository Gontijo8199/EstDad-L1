#include<iostream> 
#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"

using namespace std;

int main(){
    
    int room_count = 2;
    int room_capacity[] = {10, 45};
    ReservationSystem* r = new ReservationSystem(room_count, room_capacity);
    ReservationRequest* request = new ReservationRequest("Estrutura de Dados", "segunda", 7,9, 40);
    bool result = r->reserve(*request);

    cout << "Deu bom? " << result << endl;
    cout << endl;
    r->printSchedule();
    
    return 0;
}