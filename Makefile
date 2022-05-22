SRC=dyna_mem.c get_token.c utils.c tree.c exec.c exec2.c exec3.c exec_utils.c signals.c\
	built_export.c built_export_utils.c built_unset.c built_exit.c \
	builtins.c environnement.c built_cd.c exit.c varstar.c \
	token.c heredoc.c resource_management.c built_echo.c \
	var_utils.c parse_tree.c all_heredocs.c builder.c atoms.c star_expand.c
MAIN=main.c # kept separate so testfiles can have their own main
SRCDIR=src
OBJ=${SRC:.c=.o}
OBJDIR=obj
INCLDIR=incl
TESTDIR=test
NAME=minishell
CFLAGS=-Wall -Wextra -Werror -I ${INCLDIR}
CFLAGS+= -I /Users/$(USER)/.brew/opt/readline/include # Macs at 19
LINK_LIB=-L libft -lft -lreadline
LINK_LIB+= -L /Users/$(USER)/.brew/opt/readline/lib # Macs at 19

${NAME} : ${addprefix ${OBJDIR}/, ${OBJ}} libft/libft.a ${SRCDIR}/${MAIN}
	gcc ${CFLAGS} -o ${NAME} $^ ${LINK_LIB}

libft/libft.a:
	cd libft && make

${OBJDIR} : 
	mkdir -p $@

${OBJDIR}/%.o: ${SRCDIR}/%.c | ${OBJDIR}
	gcc ${CFLAGS} -c $< -o $@

test_%: ${TESTDIR}/test_%.c ${addprefix ${OBJDIR}/, ${OBJ}} libft/libft.a
	gcc ${CFLAGS} -o $@ $^ ${LINK_LIB}

all: ${NAME}
	@#empty

clean:
	rm -rf ${OBJDIR} 
	cd libft/ && make clean

fclean: clean 
	rm -f minishell
	cd libft/ && make fclean

re: fclean
	make

bonus: all
	@#empty

.PHONY: re fclean clean all bonus
