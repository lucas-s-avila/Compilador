#include <string>
#include <iostream>
#include <iterator>

// Reconhecedor da transformação <programa>.
bool programa(std::string txt) {
  // Começa com principal?
  if(txt.compare(0,9,"principal") == 0) {
    txt.erase(0,9);
    // Pega a lista de comandos.
    int cont_chaves = 0;
    int i = 1;
    if(txt.compare(0,1,'{') == 0) {
      cont_chaves++;
    }
    for(std::string::iterator it=txt.begin()+1; it!=txt.end() && cont_chaves!=0; it++) {
      if(txt.compare(0,1,'{') == 0) {
        cont_chaves++;
      }
      if(txt.compare(0,1,'}') == 0) {
        cont_chaves--;
      }
      i++;
    }
    if(cont_chaves != 0) {
      return false;
    }
    // Caso não exista declarações de funções:
    if(it==txt.end()) {
      return listadeComandos(txt);
    }
    // Caso exista declarações de funções:
    else {
      return listadeComandos(txt.substr(0,i+1)) && listadeFuncoes(txt.substr(i+1));
    }
  }
  else {
    return false;
  }
}

// Reconhecedor da transformação <ListadeFunções>.
bool listadeFuncoes(std::string txt) {
  // Função com retorno de inteiro.
  if(txt.compare(0,3, "int") == 0) {
    txt.erase(0,3);
    // Pega o identificador.
    std::string id = '';
    for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!='('; it++) {
      id+=*it;
    }
    if(it==txt.end()) {
      return false;
    }
    txt.erase(0,id.lenght());

    // Pega a lista de parâmetros.
    std::string parametros = '';
    for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!='{'; it++) {
      parametro+=*it;
    }
    if(it==txt.end()) {
      return false;
    }
    txt.erase(0,parametro.lenght());
  }
  if(txt.compare(0,2, "pf") == 0) {

  }
  if(txt.compare(0,6, "logico") == 0) {

  }
  if(txt.compare(0,5, "texto") == 0) {

  }
  if(txt.compare(0,5, "vetor") == 0) {

  }
  if(txt.compare(0,5, "matriz") == 0) {

  }

}

bool listadeParametros(std::string txt) {

}

bool listadeParametros_(std::string txt) {

}

bool parametro(std::string txt) {

}

bool comandodeRetorno(std::string txt) {

}

bool listadeComandos(std::string txt) {

}

bool listadeComandos_(std::string txt) {

}

bool comando(std::string txt) {

}

bool chamadadeFuncao(std::string txt) {

}

bool declaracaodeEstrututra(std::string txt) {

}

bool listadeDeclaracoes(std::string txt) {

}

bool declaracao(std::string txt) {

}

bool atribuicao(std::string txt) {

}

bool atribuicaodeEstrututra(std::string txt) {

}

bool atribuicaodeAtributo(std::string txt) {

}

bool listadeCondicionalCaso(std::string txt) {

}

bool listadeIdentificadores(std::string txt) {

}

bool tipo(std::string txt) {

}

bool expressao(std::string txt) {

}

bool expressaoLogica(std::string txt) {

}

bool expressaoLogica_(std::string txt) {

}

bool expressaoAritmetica(std::string txt) {

}

bool expressaoAritmetica_(std::string txt) {

}

bool valorReal(std::string txt) {

}

bool valorInteiro(std::string txt) {

}

bool valor(std::string txt) {

}

bool texto(std::string txt) {

}

bool letra(std::string txt) {

}

bool identificador(std::string txt) {

}

int main() {

  // Lê o arquivo passado como: "./exemplo < <nome_do_arquivo>.txt".
  std::string entrada(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());

  // Exclui espaços, tabulações e quebras de linhas da string.
  for(std::string::iterator it=entrada.begin(); it!=entrada.end(); it++) {
    if(it == ' ' || it == '\t' || it == '\n') {
      entrada.erase(it);
    }
  }

  // Retorna a análise da gramática.
  std::cout << programa(entrada) << std::endl;

  return 0;
}
