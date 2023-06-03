# IRC Server Implementation in C++98

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This project is an IRC server implementation in C++98 that is compatible with official IRC clients. It provides support for handling various IRC commands and allows users to interact with the server using popular IRC clients.

## Features

- **Compatibility**: The IRC server is designed to be compatible with official IRC clients, ensuring a seamless experience for users.
- **Command Handling**: The server supports a wide range of IRC commands, including:
  - `pass`
  - `nick`
  - `user`
  - `join`
  - `kick`
  - `part`
  - `notice`
  - `privmsg`
  - `quit`
  - `topic`
  - `names`
  - `list`
  - `invite`
  - `mode`
  - `bot`
  - `pong`
  - `oper`
  - `wallops`
  - `whois`
- **IRC Client Support**: Users can connect to the server using any standard IRC client, enabling easy integration with existing IRC ecosystems.
- **Scalability**: The server is built with scalability in mind, allowing for a large number of simultaneous connections and efficient message handling.

## Getting Started

To get started with the IRC server, follow these steps:

1. Clone the repository:

   ```
   git clone https://github.com/your-username/irc-server.git
   ```

2. Build the server:

   ```
   cd irc-server
   make
   ```

3. Start the server:

   ```
   ./ircserv PORT PASSWORD
   ```

4. Connect to the server using your preferred IRC client.

## Acknowledgments

We would like to acknowledge the following resources that were instrumental in the development of this IRC server:

- [IRC Protocol](https://tools.ietf.org/html/rfc1459 ) - The official IRC protocol specification.
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/) - A great resource to understand basic networking concepts
- [How sockets work](https://www.ibm.com/docs/en/i/7.3?topic=programming-how-sockets-work) - A short explanation by IBM on how client-server communication work under the hood using stream sockets


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.
