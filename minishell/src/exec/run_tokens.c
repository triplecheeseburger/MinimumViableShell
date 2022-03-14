#include "minishell.h"

static void	execute_tree(t_ast_node *node, t_info *info)
{
	if (node->node_type == NODE_PIPE && node->right != NULL)
		info->exit_status = lets_pipe(info);
	else if (info->exit_status == SUCCESS && node->node_type == NODE_REDIR_TYPE)
		info->exit_status = teach_me_direction(node->content, info);
	else if (info->exit_status == SUCCESS && node->node_type == NODE_FILE_NAME)
		info->exit_status = redir_n_join_remainder(node->content, info);
	else if (info->exit_status == SUCCESS && node->node_type == NODE_FILE_PATH)
		info->exit_status = get_fullpath(&node->content, info);
	else if (info->exit_status == SUCCESS && node->node_type == NODE_ARGV)
		info->exit_status = builtin_or_not(node->content, info);
}

static void	search_tree(t_ast_node *node, t_info *info)
{
	execute_tree(node, info);
	if (node->left != NULL)
		search_tree(node->left, info);
	if (node->right != NULL)
		search_tree(node->right, info);
}

static void	init_info(t_info *info)
{
	info->exit_status = SUCCESS;
	info->pipeexists = false;
	info->wasthereanypipe = false;
	info->remainder = NULL;
	info->fd[0] = -1;
	info->fd[1] = -1;
}

static void	clear_info(t_info *info)
{
	if (info->remainder != NULL)
		ft_free_str(info->remainder);
	if (info->fd[0] != -1)
		close(info->fd[0]);
	if (info->fd[1] != -1)
		close(info->fd[1]);
}

void	run_tokens(t_ast_node *node, t_list *env, int *exit_status)
{
	int		origin[2];
	t_info	info;
	int		heredoc;

	info.env = env;
	init_info(&info);
	if (keep_stdio(origin) == FAILURE)
		ft_print_error(NULL, NULL, strerror(errno));
	search_tree(node, &info);
	if (restore_stdio(origin) == FAILURE)
		ft_print_error(NULL, NULL, strerror(errno));
	heredoc = open("mvs_temp", O_RDONLY);
	if (heredoc >= 0)
	{
		close(heredoc);
		if (unlink("mvs_temp") == -1)
			ft_print_error(NULL, NULL, strerror(errno));
	}
	*exit_status = info.exit_status;
	clear_info(&info);
	close(origin[0]);
	close(origin[1]);
}
