LIKWID_HOME=/usr/local
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"
parametrosCompilacao = -lm -O3 -mavx -march=native -I${LIKWID_HOME}/include -L${LIKWID_HOME}/lib -llikwid
nomePrograma = interpola
objs = main.o auxiliares.o metodosInterpol.o

all: interpola

$(nomePrograma): $(objs)
	gcc -o $(nomePrograma) $(objs) $(parametrosCompilacao)

main.o: ./codigos/main.c
	gcc -c ./codigos/main.c $(parametrosCompilacao)

auxiliares.o: ./codigos/auxiliares.h ./codigos/auxiliares.c
	gcc -c ./codigos/auxiliares.c $(parametrosCompilacao)

metodosInterpol.o: ./codigos/metodosInterpol.h ./codigos/metodosInterpol.c
	gcc -c ./codigos/metodosInterpol.c $(parametrosCompilacao)

clean:
	-rm -f $(objs) *~

purge: clean
	-rm -f $(nomePrograma) codigos/*.o
