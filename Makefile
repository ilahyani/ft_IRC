SRC = main.cpp server.cpp client.cpp Channels.cpp \
      commands/join.cpp commands/kick.cpp commands/nick.cpp commands/notice.cpp commands/part.cpp \
      commands/pass.cpp commands/privmsg.cpp commands/quit.cpp commands/topic.cpp commands/user.cpp \
	  commands/invite.cpp commands/list.cpp commands/mode.cpp commands/names.cpp commands/bot.cpp commands/pong.cpp

OBJ = $(SRC:%.cpp=%.o)

CC = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 

#-g -fsanitize=address

NAME = ircserv

HEADER = irc.hpp server.hpp client.hpp Channels.hpp

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(HEADER)
	@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME) .DS_Store .vscode

re: fclean all