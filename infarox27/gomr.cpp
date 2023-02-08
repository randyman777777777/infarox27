#include <iostream>
#include <fstream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

int main() {
  // Initialize Winsock
  WSADATA wsaData;
  int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (iResult != 0) {
    cout << "WSAStartup failed: " << iResult << endl;
    return 1;
  }

  // Create a socket
  SOCKET sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sendSocket == INVALID_SOCKET) {
    cout << "socket failed: " << WSAGetLastError() << endl;
    WSACleanup();
    return 1;
  }

  // Fill in a sockaddr_in structure with address information
  sockaddr_in sendAddr;
  sendAddr.sin_family = AF_INET;
  sendAddr.sin_port = htons(27015); // replace with the port you want to use
  sendAddr.sin_addr.s_addr = INADDR_BROADCAST;

  // Enable broadcast on the socket
  int broadcast = 1;
  iResult = setsockopt(sendSocket, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast));
  if (iResult == SOCKET_ERROR) {
    cout << "setsockopt failed: " << WSAGetLastError() << endl;
    closesocket(sendSocket);
    WSACleanup();
    return 1;
  }

  // Open the file "hello.txt"
  ifstream file("yani.ps1", ios::in | ios::binary | ios::ate);
  if (!file.is_open()) {
    cout << "Failed to open file" << endl;
    return 1;
  }

  // Get the size of the file
  streamsize size = file.tellg();
  file.seekg(0, ios::beg);

  // Allocate a buffer to store the file data
  char* buffer = new char[size];

  // Read the file into the buffer
  file.read(buffer, size);
  file.close();

  // Send the file data to the broadcast address
  iResult = sendto(sendSocket, buffer, size, 0, (sockaddr*) &sendAddr, sizeof(sendAddr));
  if (iResult == SOCKET_ERROR) {
    cout << "sendto failed: " << WSAGetLastError() << endl;
    closesocket(sendSocket);
    WSACleanup();
    return 1;
  }

  cout << "Bytes sent: " << iResult << endl;

  // Clean up
  delete[] buffer;
  closesocket(sendSocket);
  WSACleanup();

  return 0;
}