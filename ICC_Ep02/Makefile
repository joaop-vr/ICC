LIKWID_HOME=/usr/local
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"
parametrosCompilacao = -Wall -lm -O3 -mavx -march=native -I${LIKWID_HOME}/include -DLIKWID_PERFMON -L${LIKWID_HOME}/lib -llikwid
nomePrograma = perfEG
objs = main.o auxiliares.o elimGauss.o

all: perfEG

$(nomePrograma): $(objs)
	gcc -o $(nomePrograma) $(objs) $(parametrosCompilacao)

main.o: diretorioPrincipal/codigos/main.c
	gcc -c diretorioPrincipal/codigos/main.c $(parametrosCompilacao)

auxiliares.o: diretorioPrincipal/codigos/auxiliares.h diretorioPrincipal/codigos/auxiliares.c
	gcc -c diretorioPrincipal/codigos/auxiliares.c $(parametrosCompilacao)

elimGauss.o: diretorioPrincipal/codigos/elimGauss.h diretorioPrincipal/codigos/elimGauss.c
	gcc -c diretorioPrincipal/codigos/elimGauss.c $(parametrosCompilacao)

clean:
	-rm -f $(objs) *~

purge: clean
	-rm -f $(nomePrograma)
