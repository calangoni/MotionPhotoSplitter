// reading an entire binary file
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

void processar(char *pathIn, char *pathOut) {
  std::cout << pathIn << " - ";
  streampos size;
  char* memblock = new char[4096];
  int numBytesRead;

  ifstream file (pathIn, ios::in|ios::binary|ios::ate);
  // the file is open with the ios::ate flag, which means that the get pointer will be positioned at the end of the file
  if (file.is_open())
  {
    // char[] magica = {0x4D, 0x6F, 0x74, 0x69, 0x6F, 0x6E, 0x50, 0x68, 0x6F, 0x74, 0x6F, 0x5F, 0x44, 0x61, 0x74, 0x61}
    string magica = "MotionPhoto_Data";
    int iSuc = 0;
    long iFile = 0;
    size = file.tellg();
    memblock = new char [size];
    ofstream *outfile = nullptr;
    file.seekg (0, ios::beg);
    while(iFile < size) {
      file.read (memblock, 4096);
      if (file.failbit) {
        // std::cout << "ERRO, failbit " << iFile << "/" << size << std::endl;
        // break;
      }
      numBytesRead = size - iFile;
      if (numBytesRead > 4096) numBytesRead = 4096;
      if (numBytesRead == 0) {
        std::cout << "ERRO, numBytesRead inválido" << std::endl;
        break;
      }
      else if (numBytesRead > 0) {
        if (outfile != nullptr) {
          outfile->write (memblock, numBytesRead);
          iFile += numBytesRead;
          continue;
        }
        for (int iBuf = 0; iBuf < numBytesRead; iBuf++, iFile++) {
          if (memblock[iBuf] == magica[iSuc]) {
            iSuc ++;
            if (iSuc == magica.length()) {
              std::cout << "Encontrado MotionPhoto_Data !! " << (iFile - magica.length()) << std::endl;
              outfile = new ofstream();
              outfile->open (pathOut);
              iBuf++;
              iFile++;
              outfile->write (memblock + iBuf, numBytesRead - iBuf);
              iFile += numBytesRead - iBuf;
              iBuf += numBytesRead - iBuf;
              break;
            }
            else continue;
          }
          else iSuc = 0;
        }
        // if (iSuc == magica.length()) break;
      }
      else {
        std::cout << "ERRO, numBytesRead inválido" << std::endl;
        break;
      }
    }
    file.close();
    if (outfile != nullptr)
      outfile->close();
    if (iFile == size && iSuc != magica.length()) {
      std::cout << "Arquivo não é motion." << std::endl;
    }
    delete[] memblock;
  }
  else cout << "Unable to open file";
}

int main (int argc, char** argv) {
  // std::cout << "Args: " << argc << std::endl;
  // if (argc > 0) std::cout << " - " << argv[0] << std::endl;
  char *pathIn, *pathOut;
  if (argc == 1) {
    string lineInput;
    while(getline(cin, lineInput)) {
      // std::cout << "lineInput: " << lineInput << std::endl;
      pathIn = new char[lineInput.length() + 1];
      strcpy(pathIn, lineInput.c_str());
      pathOut = pathIn;
      while(*pathOut != '\0' && *pathOut != '\t') pathOut++;
      if (*pathOut != '\t') {
        std::cout << "ERRO: $:> programa nomefoto \\t nomevideo: " << pathIn << std::endl;
        exit(1);
      }
      *pathOut = '\0';
      pathOut++;
      processar(pathIn, pathOut);
      delete[] pathIn;
    }
  }
  else if (argc == 3) {
    pathIn = argv[1];
    pathOut = argv[2];
    processar(pathIn, pathOut);
  }
  else {
    std::cout << "ERRO: $:> programa nomefoto nomevideo" << std::endl;
    exit(1);
  }
  return 0;
}
