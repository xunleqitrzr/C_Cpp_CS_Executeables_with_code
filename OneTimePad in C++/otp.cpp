#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void encrypt(std::string filename) {
  std::ifstream in(filename, std::ios::binary);
  std::vector<unsigned char> to_encrypt((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
  in.close();
  int size = to_encrypt.size();
  std::vector<unsigned char> key(size);
  std::srand(std::time(nullptr));
  for (int i = 0; i < size; i++) {
    key[i] = std::rand() % 256;
  }
  std::ofstream key_out(filename + ".key", std::ios::binary);
  for (int i = 0; i < size; i++) {
    key_out << key[i];
  }
  key_out.close();
  std::vector<unsigned char> encrypted(size);
  for (int i = 0; i < size; i++) {
    encrypted[i] = to_encrypt[i] ^ key[i];
  }
  std::ofstream encrypted_out(filename, std::ios::binary);
  for (int i = 0; i < size; i++) {
    encrypted_out << encrypted[i];
  }
  encrypted_out.close();
}

void decrypt(std::string filename, std::string key) {
  std::ifstream in(filename, std::ios::binary);
  std::vector<unsigned char> file;
  in.seekg(0, std::ios::end);
  file.resize(in.tellg());
  in.seekg(0, std::ios::beg);
  in.read(reinterpret_cast<char*>(file.data()), file.size());
  in.close();
  std::ifstream key_in(key, std::ios::binary);
  std::vector<unsigned char> key_vec;
  key_in.seekg(0, std::ios::end);
  key_vec.resize(key_in.tellg());
  key_in.seekg(0, std::ios::beg);
  key_in.read(reinterpret_cast<char*>(key_vec.data()), key_vec.size());
  key_in.close();
  int size = file.size();
  std::vector<unsigned char> decrypted(size);
  for (int i = 0; i < size; i++) {
    decrypted[i] = file[i] ^ key_vec[i];
  }
  std::ofstream decrypted_out(filename + ".decrypted", std::ios::binary);
  for (int i = 0; i < size; i++) {
    decrypted_out << decrypted[i];
  }
  decrypted_out.close();
}

int main() {
  std::string filename;
  std::cout << "\nFile Path: ";
  std::cin >> filename;
  std::string mode;
  std::cout << "Mode ( Encrypt or Decrypt )  e/d: ";
  std::cin >> mode;
  if (mode == "e") {
    encrypt(filename);
  } else if (mode == "d") {
    std::string key;
    std::cout << "Key Path: ";
    std::cin >> key;
    decrypt(filename, key);
  } else {
    std::cout << "Invalid Mode" << std::endl;
  }
  return 0;
}
