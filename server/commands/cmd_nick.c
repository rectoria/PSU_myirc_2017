/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <string.h>
#include "server.h"

bool nick_available(server_t *srv, client_t *client)
{
	bool ret = true;

	for (client_t *tmp = srv->list; ret && tmp; tmp = tmp->next)
		ret = strcmp(client->cmd.param[0], tmp->nick) != 0;
	return (ret);
}

void cmd_nick(server_t *srv, client_t *client)
{
	size_t len;
	char *msg = client->cmd.psize != 1 ? ERR_NONICKNAMEGIVEN :
		ERR_NICKNAMEINUSE;

	if (client->cmd.psize == 1 && nick_available(srv, client)) {
		len = strlen(client->cmd.param[0]) % NICK_LENGTH;
		memset(client->nick, 0, NICK_LENGTH);
		memcpy(client->nick, client->cmd.param[0], len);
		if (!client->logged && client->user[0])
			welcome_newcomer(client);
		return;
	}
	add_pending(client, gen_rpl(msg, TRANSLATE_NICK(client)));
}