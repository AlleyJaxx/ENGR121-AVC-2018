#include "E101.h"
#include <stdio.h>

int main(){
	
	char server_addr[15] = "130.195.6.196";
	int port = 1024;
	char message[24] = "Please";

	connect_to_server(server_addr, port);
	send_to_server(message);
	receive_from_server(message);
	
	printf("%s", message);
	
return 0;
}
