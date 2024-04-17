#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include "../../../../usr/include/openssl/evp.h"

using namespace std;

string encriptarContrasena(const string& contrasena) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX *mdctx;

    // Crear contexto de digestión
    mdctx = EVP_MD_CTX_new();
    if (mdctx == nullptr) {
        return ""; 
    }

    // Inicializar SHA256
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
        // Manejar el error si no se pudo inicializar el algoritmo
        EVP_MD_CTX_free(mdctx);
        return "";
    }

    // Actualizar con la contraseña

    if (EVP_DigestFinal_ex(mdctx, hash, nullptr) != 1) {
      // Manejar el error si la operación de hashing falla
      EVP_MD_CTX_free(mdctx); 
      return "";
    }

    EVP_MD_CTX_free(mdctx); 

    // Convertir el hash a una cadena hexadecimal
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) 
        ss << hex << setw(2) << setfill('0') << (int)hash[i];

    return ss.str();
}

// Clase para representar un usuario
class Usuario {
public:
  Usuario(const string& nombre, const string& correoElectronico, const string& contrasena) {
    this->nombre = nombre;
    this->correoElectronico = correoElectronico;
    this->contrasenaEncriptada = encriptarContrasena(contrasena);
  }

  string getNombre() const { return nombre; }
  string getCorreoElectronico() const { return correoElectronico; }
  string getContrasenaEncriptada() const { return contrasenaEncriptada; }

private:
  string nombre;
  string correoElectronico;
  string contrasenaEncriptada;
};

class TablaHashUsuarios {
public:
  TablaHashUsuarios() {}

  void registrarUsuario(const string& nombre, const string& correoElectronico, const string& contrasena) {
    if (tablaHash.find(correoElectronico) != tablaHash.end()) {
      cout << "Error: El correo electrónico ya está registrado." << endl;
      return;
    }

    Usuario* nuevoUsuario = new Usuario(nombre, correoElectronico, contrasena);
    tablaHash[correoElectronico] = nuevoUsuario;
    cout << "Usuario registrado exitosamente." << endl;
  }

  void recuperarInformacionUsuario(const string& correoElectronico) {
    auto it = tablaHash.find(correoElectronico);
    if (it == tablaHash.end()) {
      cout << "Error: El usuario no existe." << endl;
      return;
    }

    Usuario* usuario = it->second;
    cout << "Nombre: " << usuario->getNombre() << endl;
    cout << "Correo electrónico: " << usuario->getCorreoElectronico() << endl;
    cout << "Contraseña: " << usuario->getContrasenaEncriptada() << endl;
  }

private:
  unordered_map<string, Usuario*> tablaHash;
};

int main() {
  TablaHashUsuarios tablaHashUsuarios;

  tablaHashUsuarios.registrarUsuario("Juan", "juan@example.com", "password123");
  tablaHashUsuarios.registrarUsuario("María", "maria@example.com", "hello456");
  tablaHashUsuarios.registrarUsuario("Pedro", "pedro@example.com", "abc789");

  tablaHashUsuarios.recuperarInformacionUsuario("juan@example.com");
  tablaHashUsuarios.recuperarInformacionUsuario("maria@example.com");
  tablaHashUsuarios.recuperarInformacionUsuario("pedro@example.com");
  tablaHashUsuarios.recuperarInformacionUsuario("correo_inexistente@example.com");

  return 0;
}
