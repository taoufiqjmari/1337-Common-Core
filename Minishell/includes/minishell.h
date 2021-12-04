/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:04:07 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/16 15:06:28 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../libft/libft.h"

# define UP 4283163
# define DOWN 4348699
# define CTRL_D 4
# define DEL 127
# define NL 10

typedef struct s_cmd
{
	char		**args;
	char		*sep;
	char		**red;
	char		**file;
	int			pipe[2];
}				t_cmd;

typedef struct s_trm
{
	char		**line;
	int			lni;
	char		*last;
	char		*curr;
	char		*h_cur;
}				t_trm;

typedef struct s_tool
{
	int			cmd_c;
	int			i;
	char		cwd[1024];
	t_trm		*trm;
	int			exit_status;
	t_cmd		**cmd;
	char		**envp;
	int			original_fd_in;
	int			original_fd_out;
	int			fd_in;
	int			fd_out;
	int			which_builtin;
	pid_t		pid;
	_Bool		exit_flag;
}				t_tool;
t_tool			g_tool;

/*
** PARSING
*/
int				parsing(char *s);
int				same(char *s1, char *s2);
int				doublecount(char **s);
int				itis(char *s);
int				pipe_tkn(int *f, int *i, char **sp);
int				semicln_tkn(int *f, int *i);
int				a_word(char *s);
int				seterr(short err);
int				err_quit(char *s, int err);
int				count_cmds(char **s);
int				ft_getenv(char *s);
int				redirct_tkn(int *f, int *i, char **sp);
int				backslash(char *s);
char			**doublefree(char **ptr);
char			**append_line(char **s, char *line, int free);
char			**split_it(char *s, char **sp, int i, int start);
void			cmd_arg(int *f, int *i);
void			finalizem(int	i);
void			assign(char **sp, int i, int j, int cmd_i);
void			nfree(void *s);
void			fin_slash(char **fin, char *s, int *i);
void			fin_quote(char **fin, char *s, int *i);
void			fin_sngl_q(char **fin, char *s, int *i);
void			fin_vars(char **fin, char *s, int *i);
void			fin_nrml(char **fin, char *s, int *i);
void			fin_err(char **fin, int *i);
short			chk_err(char **sp, int i, int value, int flag);
void			term_line(char **line, int chr);
int				printchr(int c);
void			del(void);
void			up(int *i);
void			down(int *i);
int				single_q(char *s, int *i);
void			print_exit_quit(void);

/*
** EXECUTING
*/
void			executing(void);
void			change_shlvl(void);
void			unset_oldpwd(void);

void			signal_int(int sig);
void			signal_quit(int sig);

_Bool			based_pipe_fork(int i);
void			open_pipe(int i);
void			set_pipe(int i);

_Bool			set_redirections(t_cmd *cmd);
void			reset_std(void);

void			run_infork(int i);
void			run_cmd_path(int i);
void			execve_failure(int i);

void			which_builtin(int i);
void			run_builtin(int i);
void			ft_echo(int i);
void			ft_cd(int i);
void			ft_pwd(void);
void			ft_export(int i);
void			ft_unset(int i);
void			ft_env(void);
void			ft_exit(int i);

void			ft_puterror(char *s1, char *s2, char *s3);
char			*ft_getkey(char *arg);
char			*ft_getvalue(char *arg);
int				ft_isempty(char *s);
void			ft_putexport_cases(char *arg, char *key, char *value);
char			**ft_dcdup(char **argv, int toadd);
void			add_node_dc(char **args, int toadd, int envp_len, int args_len);
_Bool			ft_export_valid(char *cmd);
char			*charp_ternary(char *condition, char *arg1, char *arg2);

#endif
