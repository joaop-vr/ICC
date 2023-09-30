LIKWID_HOME=/usr/local
parametrosCompilacao = -lm -O3 -mavx -march=native #-I${LIKWID_HOME}/include -L${LIKWID_HOME}/lib -llikwid
nomePrograma = ajustePol
objs = main.o operaEstrutura.o calculoIntervalar.o auxiliares.o

all: ajustePol

$(nomePrograma): $(objs)
	gcc -o $(nomePrograma) $(objs) $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

operaEstrutura.o: operaEstrutura.h operaEstrutura.c
	gcc -c operaEstrutura.c $(parametrosCompilacao)

calculoIntervalar.o: calculoIntervalar.h calculoIntervalar.c
	gcc -c calculoIntervalar.c $(parametrosCompilacao)

auxiliares.o: auxiliares.h auxiliares.c
	gcc -c auxiliares.c $(parametrosCompilacao)

clean:
	-rm -f $(objs) *~

purge: clean
	-rm -f $(nomePrograma)
