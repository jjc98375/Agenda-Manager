agendaManager: agendaManager.c List.c List.h
		cc -o agendaManager -g agendaManager.c List.c

%.o: %.c
		cc -c -o $@ $< -std=c99

clean:
		rm -f List *.o
		rm -f agendaManager *.o