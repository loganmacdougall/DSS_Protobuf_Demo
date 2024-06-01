#include "command_protocal.pb.h"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080

int setup_socket();

int main() {
  char buffer[4096] = {0};

  int serverSocket = setup_socket();
  if (serverSocket < 0)
    return -1;

  int socket = accept(serverSocket, nullptr, nullptr);
  int messageLen = recv(socket, buffer, sizeof(buffer), 0);

  command::Command clientCommand;
  clientCommand.ParseFromArray(buffer, messageLen);

  std::cout << "----- Recived message from client -----" << std::endl;
  std::cout << clientCommand.DebugString();
  std::cout << "---------------------------------------" << std::endl;

  return 0;
}

int setup_socket() {
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  if (bind(serverSocket, (struct sockaddr *)&serverAddress,
           sizeof(serverAddress)) < 0) {
    std::cout << "Error binding" << std::endl;
    return -1;
  }

  if (listen(serverSocket, 0) < 0) {
    std::cout << "Error listening" << std::endl;
    return -1;
  }

  return serverSocket;
}
