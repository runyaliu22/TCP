#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>  // for inet_ntoa()
#include <vector>

#include "tools.hpp"

using namespace std;

int main(int argc, char *argv[])
{

  if (argc != 4) {
        cerr << "Usage: " << argv[0] << "<port_num> <num_players> <num_hops>" << endl;
        exit(1);
    }

  const char* port_num = argv[1];//why in char array form?
  int num_players = stoi(argv[2]);
  int num_hops = stoi(argv[3]);

  vector<int> player_server_port_number(num_players);
  vector<string> player_ip(num_players);
  vector<int> player_fd(num_players);



  
  int socket_fd = build_server(port_num);


  int port_default = 2000;

  for (int i = 0; i < num_players; i++){

    
    cout << "Waiting for connection on port " << port_num << endl;
    //struct sockaddr_storage socket_addr;
    //socklen_t socket_addr_len = sizeof(socket_addr);

//Q
    struct sockaddr_storage socket_addr;//actually client address
    socklen_t socket_addr_len = sizeof(socket_addr);

    int player_connection_fd;
    player_connection_fd = accept(socket_fd, (struct sockaddr *)&socket_addr, &socket_addr_len);
    
    if (player_connection_fd == -1) {
      cerr << "Error: cannot accept connection on socket" << endl;
      return -1;
    } 
    //player_server_port_number.push_back(port_default + i);
    player_server_port_number[i] = port_default + i;

    struct sockaddr_in * addr = (struct sockaddr_in *)&socket_addr;
    string play_ip = inet_ntoa(addr->sin_addr);

    //cout<<player_ip<<endl;

    player_ip[i] = play_ip;

    //cout<<player_server_ip[i]<<endl;

    //player_fd.push_back(player_connection_fd);

    player_fd[i] = player_connection_fd;



    //cout<<client_connection_fd<<endl;
    
    send(player_connection_fd, &i, sizeof(int), 0);//what to be sent
    send(player_connection_fd, &num_players, sizeof(int), 0);

    //if (i != num_players - 1){
      //send(player_connection_fd, &port_default + i, sizeof(int), 0);

    send(player_connection_fd, &player_server_port_number[i], sizeof(int), 0);

    //}

    char buffer[512];
    recv(player_connection_fd, buffer, 9, 0);
    buffer[9] = 0;

    cout << "Ringmaster received: " << buffer << endl;

  }
 





  for (int i = 0; i < num_players; i++){

    char buffer[512] = {0};
    int neighbor_id = (i + 1)%num_players;

    strcpy(buffer, player_ip[neighbor_id].c_str());
    
    // cout<<"start"<<player_ip[0]<<"end"<<endl;
    // cout<<"start"<<buffer<<"end"<<endl;

    cout<<"start1 "<<buffer<<"end"<<endl;
    cout<<"start2 "<<player_server_port_number[neighbor_id]<<"end"<<endl;

    cout<<"buffersize: "<<sizeof(buffer)<<endl;

    send(player_fd[i], buffer, 512, 0);
    send(player_fd[i], &player_server_port_number[neighbor_id], sizeof(int), 0);


  }

  
  close(socket_fd);

  return 0;
}
