# philosophers
Implementação concorrente usando semáforos/mutexes.

-O projeto:
A philosophers é uma versão do “jantar dos filósofos” que é um problema clássico de sincronização e de coordenação de processos concorrentes.

O problema envolve um número philo_total (este número entra como um argumento) de filósofos que estão ao redor de uma mesa com um prato de macarrão no centro. para cada filósofo tem um garfo, e o filósofo usa dois garfos para comer. eles alternam entre atividades: comer, pensar e dormir.

A simulação termina quando um filósofo morre de fome ou quando todos os filósofos ficam saciados.

-Como rodar? 
make para fazer a compilação. 
./philo + argumentos.
ex1: ./philo 4 300 100 100
ex2. ./philo 20 500 100 100 5

-Argumentos:
arg 1- philo_total (número de filósofos em volta da mesa)
arg 2- time_till_starvation em milissegundos (tempo que o filósofo pode ficar sem comer)
arg 3- time_to_eat em milissegundos (tempo que o filósofo leva para fazer uma refeição)
arg 4- time_to_sleep em milissegundos (tempo que o filósofo passa dormindo)
arg 5- meals_till_statiation (argumento opcional. quantas refeições cada filósofo faz até que ele fique saciado)
