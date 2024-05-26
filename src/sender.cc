#include "command_protocal.pb.h"
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080
#define SIZE 4096

int setup_socket();

int main() {
  char buffer[SIZE] = {0};

  int socket = setup_socket();
  if (socket < 0)
    return -1;

  command::Command *serverCommand = new command::Command();

  serverCommand->set_cmd(504);
  serverCommand->set_src(command::IPC);
  serverCommand->set_dst(command::OBA);
  serverCommand->set_dtt(100);
  serverCommand->set_sig(1);

  serverCommand->set_int_d(123456);

  std::cout << "------ sending following command ------" << std::endl;
  std::cout << serverCommand->DebugString();
  std::cout << "---------------------------------------" << std::endl;

  serverCommand->SerializePartialToArray(buffer, SIZE);

  send(socket, buffer, SIZE, 0);

  delete serverCommand;

  return 0;
}

int setup_socket() {
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  if (connect(clientSocket, (struct sockaddr *)&serverAddress,
              sizeof(serverAddress)) < 0) {
    std::cout << "Error connecting" << std::endl;
    return -1;
  }

  return clientSocket;
}
