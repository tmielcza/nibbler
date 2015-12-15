#ifndef BUFF_CIRCLE_HPP
# define BUFF_CIRCLE_HPP

# include <iostream>
# include <strings.h>

# define BC_SIZE	8192

class Buff_Circle
{
	private:
	char	bc_start[BC_SIZE + 1];
	char	*bc_end;
	char	*bc_headr;
	char	*bc_headw;
	int		bc_nbcmd;
	
	Buff_Circle(const Buff_Circle & src);
	Buff_Circle	&	operator=(const Buff_Circle & src);

	public:
	Buff_Circle(void);
	~Buff_Circle(void);
	void	bc_read(char *tmp);
	void	bc_write(char *tmp, int type);
	int		bc_iscmd(void);
	void	bc_display(void);

};

#endif
