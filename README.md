# Trabalho 01: Room Reservation System

**Alunos:**
- Rafael Gontijo Ferreira
- Rudá Dantas Ruoso Brandão

---

## Descrição
Este projeto consiste na realização da primeira atividade da disciplina de Estrutura de Dados, implementando um sistema de reserva de salas simplificado. 

Conforme solicitado, o sistema possui as seguinte operações:
- realizar reservas de disciplinas em salas
- cancelar reservas existentes
- visualizar a grade de horários das salas

As reservas são feitas considerando:
- dia da semana
- intervalo de horário
- número de alunos da disciplina

---

## Organização do Projeto

O sistema está dividido nos seguintes arquivos:
- ```main.cpp``` que possui a função main com os testes do sistema
- ```ReservationRequest.cpp``` que define a classe representativa da solicitação de reserva
- ```ReservationRequest.hpp``` que define os headers para a request
- ```ReservationSystem.cpp``` que define o funcionamento do sistema de reserva, com a estrutura de armazenamento de dados e o gerenciamento de request
- ```ReservationSystem.hpp```que define os headers para o sistema

---

## Estruturas de Dados

Para armazenar o status das salas em cada horário sem usar estruturas do stl, definimos uma estrutura com [sala][dia][horário] = "disciplina" de modo a associar cada sala a 5 dias da semana e cada dia aos 14 horários de reserva. Assim, para cada sala, podemos podemos avaliar seu status de reserva em cada horário em tempo constante, e avaliar o status de todas as salas na ordem assintótica de $O(n)$.

**Comentário:** A atual implementação do sistema não aloca a sala com menor número de vagas capaz de suportar a disciplina, isso pode ser resolvido ordenando o array de capacidade na inicialização do sistema. Entretanto, tal solução gera problemas de escalabilidade em uma possível expansão do sistema onde se poderia adicionar novas salas, pois seria necessário reordenar todos os dados da sala. Uma possível solução para esse problema é a organização das salas em uma lista encadeada, o que permite a fácil inserção de uma nova sala na sua posição ordenada. 