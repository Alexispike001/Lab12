#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Estructura para guardar pregunta y respuesta
struct QA {
    string pregunta;
    string respuesta;
};

// Función para cargar la base de conocimiento
vector<QA> cargarBaseDeConocimiento(const string& archivo) {
    vector<QA> base;
    ifstream file(archivo);
    string linea;

    while (getline(file, linea)) {
        size_t separador = linea.find('|');
        if (separador != string::npos) {
            string pregunta = linea.substr(0, separador);
            string respuesta = linea.substr(separador + 1);
            base.push_back({ pregunta, respuesta });
        }
    }
    return base;
}

// Conversión a minúsculas
string aMinusculas(const string& str) {
    string resultado = str;
    transform(resultado.begin(), resultado.end(), resultado.begin(), ::tolower);
    return resultado;
}

// Búsqueda exacta
string busquedaExacta(const string& pregunta, const vector<QA>& base) {
    for (const auto& qa : base) {
        if (aMinusculas(qa.pregunta) == aMinusculas(pregunta)) {
            return qa.respuesta;
        }
    }
    return "";
}

// Búsqueda por palabras clave (cuenta cuántas palabras coinciden)
string busquedaPorPalabrasClave(const string& pregunta, const vector<QA>& base) {
    vector<string> palabrasUsuario;
    istringstream streamUsuario(aMinusculas(pregunta));
    string palabra;
    while (streamUsuario >> palabra) {
        palabrasUsuario.push_back(palabra);
    }

    int maxCoincidencias = 0;
    string mejorRespuesta = "";

    for (const auto& qa : base) {
        int coincidencias = 0;
        for (const auto& palabraUsuario : palabrasUsuario) {
            if (aMinusculas(qa.pregunta).find(palabraUsuario) != string::npos) {
                coincidencias++;
            }
        }
        if (coincidencias > maxCoincidencias) {
            maxCoincidencias = coincidencias;
            mejorRespuesta = qa.respuesta;
        }
    }

    return mejorRespuesta;
}

int main() {
	map<string, string> Conocimiento;
    string archivo = "conocimiento.txt";  
    vector<QA> base = cargarBaseDeConocimiento(Conocimiento, "C:\Users\50257\OneDrive - Colegio San José de la Encarnación\Escritorio\conocimiento.txt");

    cout << "Chatbot Local (escribe 'salir' para terminar)\n\n";

    string preguntaUsuario;
    while (true) {
        cout << "Tú: ";
        getline(cin, preguntaUsuario);
        if (aMinusculas(preguntaUsuario) == "salir") break;

        string respuesta = busquedaExacta(preguntaUsuario, base);
        if (respuesta.empty()) {
            respuesta = busquedaPorPalabrasClave(preguntaUsuario, base);
        }

        if (respuesta.empty()) {
            cout << "Chatbot: Lo siento, no tengo una respuesta para eso.\n";
        }
        else {
            cout << "Chatbot: " << respuesta << "\n";
        }
    }

    return 0;
}