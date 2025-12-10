# Filósofos Coloridos - Problema dos Filósofos Jantando

Uma simulação multithread do clássico **Problema dos Filósofos Jantando**, implementado em C usando POSIX threads (pthreads) e mutexes. Este projeto faz parte do currículo da 42 School e explora conceitos de concorrência, sincronização e prevenção de deadlock.

## 📋 Índice

- [Visão Geral](#visão-geral)
- [O Problema](#o-problema)
- [Funcionalidades](#funcionalidades)
- [Compilação](#compilação)
- [Uso](#uso)
- [Cenários de Teste](#cenários-de-teste)
- [Verificando Vazamentos e Data Races](#verificando-vazamentos-e-data-races)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Recursos de Aprendizado](#recursos-de-aprendizado)

## 🎯 Visão Geral

O Problema dos Filósofos Jantando é um problema clássico de sincronização em ciência da computação que ilustra os desafios de alocar recursos limitados entre múltiplos processos, evitando deadlock e starvation (inanição).

Nesta simulação:
- Filósofos sentam em uma mesa redonda com um prato de espaguete
- Cada filósofo alterna entre comer, dormir e pensar
- Há um garfo entre cada par de filósofos
- Um filósofo precisa de dois garfos para comer
- A simulação termina quando um filósofo morre de fome ou todos os filósofos comeram um número específico de vezes

## 🍝 O Problema

Os filósofos seguem esta rotina:
1. **Pensar** - O filósofo contempla a vida
2. **Pegar garfos** - Tenta pegar os garfos esquerdo e direito
3. **Comer** - Consome espaguete por uma duração especificada (tempo de comer)
4. **Dormir** - Descansa após comer
5. **Repetir** - Continua até a morte ou conclusão

O filósofo morre se não começar a comer dentro de `time_to_die` em milissegundos desde sua última refeição.

## ✨ Funcionalidades

- **Operações thread-safe** usando mutexes
- **Prevenção de deadlock** através de estratégia de ordenação de garfos
- **Monitoramento em tempo real** dos estados dos filósofos
- **Sistema de detecção de morte**
- **Rastreamento de refeições** para condições de conclusão
- **Saída com código de cores** para melhor visualização
- **Tempo de pensamento otimizado** para reduzir uso desnecessário de CPU

## 🔨 Compilação

Para compilar o projeto, simplesmente execute:

```bash
make
```

Isso gerará o executável `philo`.

Para limpar arquivos objeto:
```bash
make clean
```

Para limpar tudo (objetos e executável):
```bash
make fclean
```

Para recompilar do zero:
```bash
make re
```

## 🚀 Uso

```bash
./philo numero_de_filosofos tempo_para_morrer tempo_para_comer tempo_para_dormir [numero_de_vezes_que_cada_filosofo_deve_comer] - opcional
```

### Argumentos

1. **numero_de_filosofos** - Número de filósofos (e garfos) [1-200]
2. **tempo_para_morrer** - Tempo em milissegundos até um filósofo morrer sem comer
3. **tempo_para_comer** - Tempo em milissegundos que leva para comer
4. **tempo_para_dormir** - Tempo em milissegundos gasto dormindo
5. **[numero_de_vezes_que_cada_filosofo_deve_comer]** - (Opcional) A simulação para quando todos os filósofos comeram esse número de vezes

### Exemplo

```bash
./philo 5 310 200 200
```

Isso cria 5 filósofos que morrem após 310ms sem comer, levam 200ms para comer e dormem por 200ms.

## 🧪 Cenários de Teste

### Cenário 1: Filósofo Deve Morrer

Casos de teste onde um filósofo deve morrer de fome:

```bash
#Deve morrer - impossível sobreviver
./philo 1 800 200 200
#Esperado: Filósofo pega um garfo e morre após 800ms

#Deve morrer - tempo insuficiente
./philo 4 310 200 100
#Esperado: Pelo menos um filósofo morre

#Caso limite - morre exatamente no limite
./philo 4 200 205 200
#Esperado: Deve morrer pois o tempo de comer excede o tempo de sobrevivência
```

### Cenário 2: Ninguém Deve Morrer (Comendo Infinitamente)

Casos de teste onde os filósofos devem sobreviver indefinidamente, dependendo da configuração do seu computador alguns filósofos podem morrer devido à execução de processos:

```bash
#Teste básico de sobrevivência
./philo 5 800 200 200
#Esperado: Todos os filósofos comem continuamente, sem mortes

#Teste de estresse
./philo 50 800 200 200
#Esperado: Todos os 50 filósofos sobrevivem

#Timing muito apertado
./philo 4 310 100 100
#Esperado: Deve sobreviver com tempo de pensamento otimizado
```

### Cenário 3: Completar Após N Refeições

Casos de teste com limites de refeições:

```bash
#Completar após 5 refeições cada
./philo 5 800 200 200 5
#Esperado: Simulação termina quando todos os filósofos comem 5 vezes

#Conclusão rápida
./philo 4 410 200 200 3
#Esperado: Todos os filósofos comem 3 vezes, então param

#Muitas refeições
./philo 2 400 100 100 10
#Esperado: Ambos os filósofos completam 10 refeições

#Teste de refeição única
./philo 7 310 100 100 5
#Esperado: Todos os 7 filósofos comem 5 vezes, então a simulação termina
```
Você pode verificar quantas refeições eles comeram usando:
```bash
#Teste com 5 refeições cada
./philo 7 800 200 200 5 | grep 'eating' | wc -l
#Esperado: 35 (7 filósofos * 5 refeições = 35)
```

### Casos Limite Adicionais

```bash
#Filósofo único (caso especial)
./philo 1 800 200 200
#Esperado: Pega um garfo, espera e morre

#Valores mínimos
./philo 2 60 10 10
#Esperado: Deve lidar com execução muito rápida

#Grande número de filósofos
./philo 200 800 200 200
#Esperado: Todos os 200 filósofos devem funcionar adequadamente
```

## 🚨 Verificando Vazamentos e Data Races

```bash
#Filósofo único (caso de vazamento)
valgrind --leak-check=full --show-leak-kinds=all ./philo 1 800 200 200
#Esperado: All heap blocks were freed -- no leaks are possible

#Filósofo único (caso de data race)
valgrind --tool=helgrind ./philo 1 800 200 200
#Esperado: ERROR SUMMARY: 0 errors from 0 contexts (suppressed: n from n)

#Cinco filósofos (caso de vazamento)
valgrind --leak-check=full --show-leak-kinds=all ./philo 5 310 200 100
#Esperado: All heap blocks were freed -- no leaks are possible

#Cinco filósofos (caso de data race)
valgrind --tool=helgrind ./philo 5 310 200 100
#Esperado: ERROR SUMMARY: 0 errors from 0 contexts (suppressed: n from n)

#Cinco filósofos com limite de refeições (caso de vazamento)
valgrind --leak-check=full --show-leak-kinds=all ./philo 5 800 200 200 5
#Esperado: All heap blocks were freed -- no leaks are possible

#Cinco filósofos com limite de refeições (caso de data race)
valgrind --tool=helgrind ./philo 5 800 200 200 5
#Esperado: ERROR SUMMARY: 0 errors from 0 contexts (suppressed: n from n)
```

## 📁 Estrutura do Projeto

```
philo/
├── main.c              # Ponto de entrada e inicialização
├── threads.c           # Criação e gerenciamento de threads
├── routine.c           # Rotina do filósofo (comer, dormir, pensar)
├── monitor.c           # Detecção de morte e rastreamento de refeições
├── philo_utils.c       # Funções utilitárias (tempo, parsing, erros)
├── philo.h             # Arquivo de cabeçalho com estruturas e protótipos
├── Makefile            # Regras de compilação
└───────────────────────────────────────────────────
├── LICENSE             # Licença do projeto
└── README.md           # Este arquivo
```

### Componentes Principais

- **Gerenciamento de Threads**: Cada filósofo executa em uma thread separada
- **Proteção com Mutex**: Garfos, status de morte e saída são protegidos por mutexes
- **Sistema de Monitoramento**: Thread principal monitora mortes e conclusão de refeições
- **Prevenção de Deadlock**: Filósofos de número par pegam garfos em ordem reversa
- **Pensamento Otimizado**: Tempo de pensamento é calculado para prevenir spinning desnecessário

## 📚 Recursos de Aprendizado

Este projeto foi desenvolvido usando estes recursos:

### Artigos e Guias
- [**Philosophers 42 Guide - The Dining Philosophers Problem**](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)  
  Guia abrangente explicando o problema e estratégias de implementação específicas para a versão da 42

- [**Philosophers 42 Guide - Gitbook**](https://42-cursus.gitbook.io/guide/3-rank-03/philosophers)  
  Guia mais fácil que explica o problema e as novas ferramentas que você usará

### Tutoriais em Vídeo
- [**CodeVault - Unix Threads in C**](https://www.youtube.com/watch?v=JbDHLaf1c5Y)  
  Excelente série de vídeos sobre programação pthread e conceitos de sincronização

### Conceitos Adicionais
- POSIX Threads (pthreads)
- Sincronização com Mutex
- Condições de corrida e deadlocks
- Programação thread-safe
- Estratégias de alocação de recursos

## 🎨 Visualização da Saída

O programa exibe ações dos filósofos com timestamps e códigos de cores:

- 🍴 **Branco**: Garfo pegado
- 🍝 **Vermelho**: Comendo
- 😴 **Azul**: Dormindo
- 🧠 **Verde**: Pensando
- 💀 **Amarelo**: Morte
- ✅ **Verde**: Todas as refeições completadas

Exemplo de saída:
```
0 1 has taken a fork 🍴
0 1 has taken a fork 🍴
0 1 is eating 🍝
200 2 has taken a fork 🍴
200 2 has taken a fork 🍴
200 2 is eating 🍝
...
```

## ⚠️ Notas Importantes

- Todos os timestamps são em milissegundos
- A simulação não deve ter data races
- Os filósofos devem morrer dentro de 10ms do tempo real de morte
- A saída de diferentes filósofos não deve ser misturada
- O programa lida com até 200 filósofos
- Um filósofo não pode comer com apenas um garfo

## 🏆 Objetivos do Projeto

- ✅ Aprender sobre threads e mutexes
- ✅ Entender problemas de sincronização
- ✅ Implementar prevenção de deadlock
- ✅ Praticar programação concorrente
- ✅ Otimizar alocação de recursos

---