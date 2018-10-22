#include <string>
#include <iostream>
#include <iterator>

std::string retorno(std::string txt) {
  int i;
  std::size_t pos = txt.find("retorno");
  for(i=0; txt[pos+i] != ";" && txt[pos+i] != *txt.end(), i++);
  if(txt[pos+i] == *txt.end()) {
    return '';
  }
  return txt.substr(pos, i);
}

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
    return -1;
  }
}

int tam_param(std::string txt){  // Pega a posição final i da expressao no txt baseado nos parenteses.
  int cont_parenteses = 0;
  int i = 1;

  for(std::string::iterator it=txt.begin(); it!=txt.end() && cont_parenteses!=0; it++) {
    if(it.compare(0,1,'(') == 0) {
      cont_parenteses++;
    }
    if(it.compare(0,1,')') == 0) {
      cont_parenteses--;
    }
    i++;
  }
  if (cont_parenteses!=0) {
    i=0;
  }
  return i;
}

// Reconhecedor da transformação <programa>.
bool programa(std::string txt_original) {
  // Começa com principal?
  txt = txt_original;
  if(txt.compare(0,9,"principal") == 0) {
    txt.erase(0,9);
    // Pega a lista de comandos.
    int tam_programa = tam_funcao(txt);
    if (tam_programa < 0) {
      return false;
    }
    if (*txt.end() == txt[tam_programa]) {
      return listadeComandos(txt.substr(0,tam_programa));
    }
    else {
      return listadeComandos(txt.substr(0,tam_programa)) && listadeFuncoes(txt.substr(tam_programa));
    }
  }
  else {
    return false;
  }
}

// Reconhecedor da transformação <ListadeFunções>.
bool listadeFuncoes(std::string txt_original) {

  // Verifica qual o tipo de retorno da função.
  std::string retorno;
  std::string txt = txt_original;
  if(txt.compare(0,3, "int") == 0) {
    txt.erase(0,3);
    retorno = str_retorno(txt);
    if (retorno == '') {
      return false;
    }
  }
  if(txt.compare(0,2, "pf") == 0) {
    txt.erase(0,2);
    retorno = str_retorno(txt);
    if (retorno == '') {
      return false;
    }
  }
  if(txt.compare(0,6, "logico") == 0) {
    txt.erase(0,6);
    retorno = str_retorno(txt);
    if (retorno == '') {
      return false;
    }
  }
  if(txt.compare(0,5, "texto") == 0) {
    txt.erase(0,5);
    retorno = retorno(txt);
    if (retorno == '') {
      return false;
    }
  }
  if(txt.compare(0,5, "vetor") == 0) {

  }
  if(txt.compare(0,6, "matriz") == 0) {

  }
  else {
    // Pega o identificador.
    int i = 0;
    std::locale loc;
    if (!std::isalpha(txt.begin(),loc)) {
      return false;
    }

    int tam_id =
    for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!='('; it++) {
      i++;
    }
    if(it==txt.end()) {
      return false;
    }
    std::string letras = txt.substr(0, tam_id);
    txt.erase(0,i);

    // Pega a lista de parâmetros.
    int tam_p = tam_param(txt);
    if (tam_p < 0) {
      return false;
    }
    std::string parametros = txt.substr(0, tam_param);
    txt.erase(0,tam_param);

    // Pega a lista de comandos (tamanho da função).
    int tam_f = tam_funcao(txt);
    if (tam_f < 0) {
          return false;
    }
    if (tam_f == 0) {
      return listadeParametros(parametros) && listadeComandos(txt.substr(0, tam_funcao);
    }
    else {
      return listadeParametros(parametros) && listadeComandos(txt.substr(0, tam_funcao) && listadeFuncoes(txt.substr(tam_funcao));
    }
  }
}

bool listadeParametros(std::string txt) {
  if(txt.compare(0,1, '(') == 0) {
    txt.erase(0);
  }

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
