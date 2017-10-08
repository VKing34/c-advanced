TARGETS=${patsubst %.c,%,${wildcard ./*.c}}

default:	${TARGETS}

%:	%.c
	${CC} -g -o $@ $< -Lbt/lib -lbt -Ibt/inc

clean:
	rm -f ${TARGETS}
