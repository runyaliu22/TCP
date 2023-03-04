#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

int build_server(const char* port_num){

  int status;
  int socket_fd;
  struct addrinfo host_info;
  struct addrinfo *host_info_list;
  

  const char *hostname = NULL;//my computer
  //const char *port     = "4444";

  //set host_info to all 0
  memset(&host_info, 0, sizeof(host_info));

  //and then initialize it
  host_info.ai_family   = AF_UNSPEC;
  host_info.ai_socktype = SOCK_STREAM;
  host_info.ai_flags    = AI_PASSIVE;

  status = getaddrinfo(hostname, port_num, &host_info, &host_info_list);
  if (status != 0) {
    cerr << "Error: cannot get address info for host" << endl;
    cerr << "  (" << hostname << "," << port_num << ")" << endl;
    return -1;
  } //if

  socket_fd = socket(host_info_list->ai_family, 
		     host_info_list->ai_socktype, 
		     host_info_list->ai_protocol);

  if (socket_fd == -1) {
    cerr << "Error: cannot create socket" << endl;
    cerr << "  (" << hostname << "," << port_num << ")" << endl;
    return -1;
  } //if

  //set socket
  int yes = 1;

  status = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
  if (status == -1) {
    cerr << "Error: cannot set socket" << endl;
    cerr << "  (" << hostname << "," << port_num << ")" << endl;
    exit(EXIT_FAILURE);
  }
  status = bind(socket_fd, host_info_list->ai_addr, host_info_list->ai_addrlen);
  if (status == -1) {
    cerr << "Error: cannot bind socket" << endl;
    cerr << "  (" << hostname << "," << port_num << ")" << endl;
    return -1;
  } //if

  //freeaddrinfo(host_info_list);//important!

  status = listen(socket_fd, 100);
  if (status == -1) {
    cerr << "Error: cannot listen on socket" << endl; 
    cerr << "  (" << hostname << "," << port_num << ")" << endl;
    return -1;
  } //if

  freeaddrinfo(host_info_list);//important!

  return socket_fd;

}

int build_client(const char* hostname, const char* port_num){

  int status;
  int socket_fd;
  struct addrinfo host_info;
  struct addrinfo *host_info_list;

  

  memset(&host_info, 0, sizeof(host_info));
  host_info.ai_family   = AF_UNSPEC;
  host_info.ai_socktype = SOCK_STREAM;

//set host_info_list
  status = getaddrinfo(hostname, port_num, &host_info, &host_info_list);

  if (status != 0) {
    cerr << "Error: cannot get address info for host" << endl;
    cerr << "  (" << hostname << "," << port_num << ")" << endl;
    return -1;
  } //if

  socket_fd = socket(host_info_list->ai_family, 
		     host_info_list->ai_socktype, 
		     host_info_list->ai_protocol);

  if (socket_fd == -1) {
    cerr << "Error: cannot create socket" << endl;
    cerr << "  (" << hostname << "," << port_num << ")" << endl;
    return -1;
  } //if


  
  cout << "Connecting to " << hostname << " on port " << port_num << "..." << endl;
  
  status = connect(socket_fd, host_info_list->ai_addr, host_info_list->ai_addrlen);
  if (status == -1) {
    cerr << "Error: cannot connect to socket" << endl;
    cerr << "  (" << hostname << "," << port_num << ")" << endl;
    return -1;
  } //if

  freeaddrinfo(host_info_list);

  return socket_fd;

}