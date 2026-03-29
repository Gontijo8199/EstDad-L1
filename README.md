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

Para armazenar o status das salas em cada horário sem usar estruturas do stl, alocamos dinamicamente um array de salas, as quais armazenam sua quantidade de vagas e uma matriz [dia][horário] com os 5 dias da semana e cada dia com os 14 horários disponíveis para reserva. Assim, para cada sala, podemos podemos avaliar seu status de reserva em cada horário em tempo constante, e avaliar o status de todas as salas na ordem assintótica de $O(n)$.

A atual implementação do sistema aloca a sala com menor número de vagas capaz de suportar a disciplina, isso garante que uma reserva que exige um número de vagas baixo não ocupe uma sala com mais vagas do que o necessário, o que poderia impedir que outra reserva que precisa de mais vagas fosse feita. 

**Comentário:** Atualmente, cada sala armazena o status de cada horário passível de reserva, mesmo que muitos não sejam usados, gerando um custo de memória desnecessário. Tal custo não é um grande problema para sistemas pequenos com poucas salas, mas pode se tornar uma questão conforme ele cresce. Uma possível solução para esse problema é salvar as reservas como uma lista encadeada, alocando dinamicamente a memória para cada instância de reserva realizada e diminuindo o custo de memória.