parametrosCompilacao = -Wall -lm
nomePrograma = EP_01
objs = main.o auxiliares.o calculoErros.o  principais.o

all: EP_01

$(nomePrograma): $(objs)
	gcc -o $(nomePrograma) $(objs) $(parametrosCompilacao)

main.o: codigos/main.c
	gcc -c codigos/main.c $(parametrosCompilacao)

auxiliares.o: codigos/auxiliares.h codigos/auxiliares.c
	gcc -c codigos/auxiliares.c $(parametrosCompilacao)

calculoErros.o: codigos/calculoErros.h codigos/calculoErros.c
	gcc -c codigos/calculoErros.c $(parametrosCompilacao)

principais.o: codigos/principais.h codigos/principais.c
	gcc -c codigos/principais.c $(parametrosCompilacao)

clean:
	-rm -f $(objs) *~

purge: clean
	-rm -f $(nomePrograma)