#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "tools.hpp"

using namespace std;

int main(int argc, char *argv[]){

  int player_id;
  int num_players;
  int port_number_server;

  //char buffer[512] = {0};
  int neighbor_port;

  //if (argc != 4) {
  if (argc != 3) {
        cerr << "Usage: " << argv[0] << "<machine_name> <port_num>" << endl;
        exit(1);
    }

  const char *hostname = argv[1];//the server's ip address
  const char* port_num = argv[2];//the port number of the server I'm reaching to

  //const char* my_port_num = argv[3];

  int socket_fd = build_client(hostname, port_num);

  

  const char *message_0 = "hi there!";
  send(socket_fd, message_0, strlen(message_0), 0);
  




  //potato p;
  //recv


  recv(socket_fd, &player_id, sizeof(int), 0);//stuffing
  cout<<player_id<<endl;

  recv(socket_fd, &num_players, sizeof(int), 0);
  cout<<num_players<<endl;

  recv(socket_fd, &port_number_server, sizeof(int), 0);



  //if (player_id != num_players - 1){

    //recv(socket_fd, &port_server, sizeof(int), 0);

    string temp0 = to_string(port_number_server);
    const char* temp1 = temp0.c_str();

    cout<<"my port number is: " << temp1<<endl;

    cout<<port_number_server<<endl;

    int player_server_fd_0 = build_server(temp1);

    //int player_server_fd_0 = build_server(my_port_num);

    cout << "Waiting for connection on port " << port_number_server << endl;


  //   if (player_id == num_players - 1){

  //     struct sockaddr_storage socket_addr;//actually client address
  //   socklen_t socket_addr_len = sizeof(socket_addr);



  // cout<<"check in!"<<endl;

  //   int player_client_fd;
  //   player_client_fd = accept(player_server_fd_0, (struct sockaddr *)&socket_addr, &socket_addr_len);
  //   cout<<"check out"<<endl;
  //   if (player_client_fd == -1) {
  //     cerr << "Error: cannot accept connection on socket" << endl;
  //     return -1;
  //   } 


  // cout<<"check out"<<endl;

  //   char buffer[512];
  //   recv(player_client_fd, buffer, 11, 0);
  //   buffer[11] = 0;

  //   cout << "Player server received: " << buffer << endl;

  //   }
   

    // cout << "Waiting for connection on port " << port_number_server << endl;
  

    // struct sockaddr_storage socket_addr;//actually client address
    // socklen_t socket_addr_len = sizeof(socket_addr);

    // int player_client_fd;
    // player_client_fd = accept(player_server_fd_0, (struct sockaddr *)&socket_addr, &socket_addr_len);
    // if (player_client_fd == -1) {
    //   cerr << "Error: cannot accept connection on socket" << endl;
    //   return -1;
    // } 

    // char buffer[512];
    // recv(player_client_fd, buffer, 11, 0);
    // buffer[11] = 0;

    // cout << "Player server received: " << buffer << endl;
  //}



  //if (player_id != 0){

    char buffer_1[512] = {0};

    recv(socket_fd, buffer_1, 512, MSG_WAITALL);
    recv(socket_fd, &neighbor_port, sizeof(int), 0);

    string temp3 = to_string(neighbor_port);
    const char* temp4 = temp3.c_str();

    cout<<"start1 "<<buffer_1<<endl;
    cout<<"start2 "<<neighbor_port<<endl;

    int player_server_fd_1 = build_client(buffer_1, temp4);

    const char *message_1 = "hi there!!!";
    send(player_server_fd_1, message_1, strlen(message_1), 0);



    struct sockaddr_storage socket_addr;//actually client address
    socklen_t socket_addr_len = sizeof(socket_addr);



  cout<<"check in"<<endl;

    int player_client_fd;
    player_client_fd = accept(player_server_fd_0, (struct sockaddr *)&socket_addr, &socket_addr_len);
    cout<<"check out"<<endl;
    if (player_client_fd == -1) {
      cerr << "Error: cannot accept connection on socket" << endl;
      return -1;
    } 


  cout<<"check out"<<endl;

    char buffer[512];
    recv(player_client_fd, buffer, 11, 0);
    buffer[11] = 0;

    cout << "Player server received: " << buffer << endl;
    
  //}






  //freeaddrinfo(host_info_list);
  close(socket_fd);

  return 0;
}
