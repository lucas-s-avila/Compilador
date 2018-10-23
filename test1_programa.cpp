#include <string>
#include <iostream>
#include <iterator>

/* =================== Funções Auxiliares =================== */

int tam_funcao(std::string txt){  // Pega a posição final i da função no txt baseado nas chaves.
  int cont_chaves = 1;
  int i = 0;

  if (txt[i] == '{') {
    i++;
    for(std::string::iterator it=txt.begin()+1; it!=txt.end() && cont_chaves!=0; it++) {
      if(*it == '{') {
        cont_chaves++;
      }
      if(*it == '}') {
        cont_chaves--;
      }
      i++;
    }
    if (cont_chaves!=0) {
      return -1;
    }
    return i;
  }
  else {
    if (txt[i] == *txt.end()) {
      return 0;
    }
    else {
      return -1;
    }
  }
}

/* =================== Reconhecedor =================== */

// Reconhecedor da transformação <programa>.
bool programa(std::string txt_original) {
  // Começa com principal?
  std::string txt = txt_original;
  if(txt.compare(0,9,"principal") == 0) {
    txt.erase(0,9);
    // Pega a lista de comandos.
    int tam_programa = tam_funcao(txt);
    if (tam_programa < 0) {
      return false;
    }
    if (*txt.end() == txt[tam_programa]) {
      //return listadeComandos(txt.substr(0,tam_programa));
      std::cout << txt.substr(0,tam_programa) << '\n';
      return true;
    }
    else {
      //return listadeComandos(txt.substr(0,tam_programa)) && listadeFuncoes(txt.substr(tam_programa));
      std::cout << txt.substr(0,tam_programa) << "\n\n=============\n\n" << txt.substr(tam_programa) << '\n';
      return true;
    }
  }
  else {
    return false;
  }
}

int main() {

  // Lê o arquivo passado como: "./exemplo < <nome_do_arquivo>.txt".
  std::string entrada(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());
  entrada.pop_back();

  // Exclui espaços, tabulações e quebras de linhas da string.
  for(std::string::iterator it=entrada.begin(); it!=entrada.end();) {
    if(*it == '\u0020' || *it == '\u000a' ) {
      entrada.erase(it);
    }
    else {
      it++;
    }
  }

  // Retorna a análise da gramática.
  std::cout << programa(entrada) << std::endl;

  return 0;
}
