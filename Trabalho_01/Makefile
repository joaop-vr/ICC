LIKWID_HOME=/home/soft/likwid
parametrosCompilacao = -lm -O3 -mavx -march=native -I ${LIKWID_HOME}/include -L ${LIKWID_HOME}/lib -DLIKWID_PERFMON -llikwid
nomePrograma = ajustePol
objs = main.o operaEstrutura.o calculoIntervalar.o auxiliares.o minimosQuadrados.o

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

minimosQuadrados.o: minimosQuadrados.h minimosQuadrados.c
	gcc -c minimosQuadrados.c $(parametrosCompilacao)

clean:
	-rm -f $(objs) *~ $(nomePrograma)

purge: clean
	-rm -f $(nomePrograma)
