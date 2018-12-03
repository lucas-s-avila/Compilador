#include <string>
#include <iostream>
#include <iterator>

/* =================== Declaração das Funções =================== */

std::string tira_esp(std::string txt);

int tam_tipo (std::string txt);

int tam_funcao(std::string txt);

int tam_param(std::string txt);

int tam_id(std::string txt);

bool programa(std::string txt_original);

bool listadeFuncoes(std::string txt_original);

bool funcaoretorno(std::string txt);

bool listadeParametros(std::string txt);

bool parametro(std::string txt);

bool comandodeRetorno(std::string txt);

bool listadeComandos(std::string txt);

bool listadeComandos_(std::string txt);

bool comando(std::string txt);

bool chamadadeFuncao(std::string txt);

bool declaracaodeEstrutura(std::string txt);

bool declaracao(std::string txt);

bool tipo(std::string txt);

bool valorInteiro(std::string txt);

bool valor(std::string txt);

bool texto(std::string txt);

bool letra(std::string txt);

bool identificador(std::string txt);

bool valorReal(std::string txt);

/* =================== Funções Auxiliares =================== */

int c, l;

std::string tira_esp(std::string txt) {
  // Exclui espaços, tabulações e quebras de linhas da string.
  for(std::string::iterator it=txt.begin(); it!=txt.end() && (*it == '\u0020' || *it == '\u000a');) {
    if(*it == '\u0020') {
      txt.erase(it);
      c++;
    }
    else {
      if(*it == '\u000a') {
        txt.erase(it);
        l++;
        c=0;
      }
    }
  }
  return txt;
}

int tam_tipo (std::string txt){
  std::string tipos[] = {"int", "pf", "logico", "texto"};
  int tam_vetor = 0;
  for (int i = 0; i < 4; i++) {
    if ((txt.substr(0,6)).find(tipos[i]) > 0) {
      txt.erase(0,tipos[i].size());
      tam_vetor = tipos[i].size();
      break;
    }
  }
  if (tam_vetor!=0) {
    return tam_vetor;
  }
  return -1;
}

std::string str_retorno(std::string txt) {
  int i;
  std::size_t pos = txt.find("retorno");
  if (pos == -1) {
    return '';
  }
  for(i=0; txt[pos+i] != ";" && txt[pos+i] != *txt.end(), i++);

  if (txt[pos+i] == *txt.end()) {
    return '';
  }
  return txt.substr(pos, i);
}

int tam_funcao(std::string txt) {  // Pega a posição final i da função no txt baseado nas chaves.
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

int tam_param(std::string txt){  // Pega a posição final i da expressao no txt baseado nos parenteses.
  int cont_parenteses = 0;
  int i = 0;
  if(txt[i] == '(') {
    i++;
    cont_parenteses++;
    for(; txt[i] != *txt.end() && cont_parenteses != 0; i++) {
      if (txt[i] == '(') {
        cont_parenteses++;
      }
      if (txt[i] == ')') {
        cont_parenteses--;
      }
    }
    if (cont_parenteses!=0) {
      return -1;
    }
    return i;
  }
  else {
    return -1;
  }
}

int tam_id(std::string txt) {
  int i=0;
  for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!='(' && *it!='{'; it++) {
    i++;
  }
  if(txt[i]==*txt.end()) {
    return -1;
  }
  return i;
}

/* =================== Reconhecedor =================== */

// Reconhecedor da transformação <programa>.
bool programa(std::string txt_original) {
  // Começa com principal?
  txt = txt_original;
  txt = tira_esp(txt);
  if(txt.compare(0,9,"principal") == 0) {
    txt.erase(0,9);
    c += 9;
    // Pega a lista de comandos.
    txt = tira_esp(txt);
    int tam_programa = tam_funcao(txt);
    if (tam_programa < 0) {
      std::cout << l << "; " << c << "\n";
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
    std::cout << l << "; " << c << "\n";
    return false;
  }
}

// Reconhecedor da transformação <ListadeFunções>.
bool listadeFuncoes(std::string txt_original) {

  // Verifica qual o tipo de retorno da função.
  std::string txt = txt_original;
  txt = tira_esp(txt);
  if(txt.compare(0,3, "int") == 0) {
    c += 3;
    txt.erase(0,3);
    txt = tira_esp(txt);

    return funcaoretorno(txt);
  }
  if(txt.compare(0,2, "pf") == 0) {
    c += 2;
    txt.erase(0,2);
    txt = tira_esp(txt);

    return funcaoretorno(txt);
  }
  if(txt.compare(0,6, "logico") == 0) {
    c += 6;
    txt.erase(0,6);
    txt = tira_esp(txt);

    return funcaoretorno(txt);
  }
  if(txt.compare(0,5, "texto") == 0) {
    c += 5;
    txt.erase(0,5);
    txt = tira_esp(txt);

    return funcaoretorno(txt);
  }
  if(txt.compare(0,5, "vetor") == 0) {
    c += 5;
    txt.erase(0,5);
    txt = tira_esp(txt);

    // Pega tipo.
    int tam_t = tam_tipo(txt);
    std::string t = txt.substr(0,tam_t);
    c += tam_t;
    txt.erase(0,tam_t);
    txt = tira_esp(txt);

    return tipo(t) && funcaoretorno(txt);
  }
  if(txt.compare(0,6, "matriz") == 0) {
    c += 6;
    txt.erase(0,6);
    txt = tira_esp(txt);

    // Pega tipo.
    int tam_t = tam_tipo(txt);
    std::string t = txt.substr(0,tam_t);
    c += tam_t;
    txt.erase(0,tam_t);
    txt = tira_esp(txt);

    return tipo(t) && funcaoretorno(txt);
  }
  else {
    // Pega o identificador.
    if (!std::isalpha(*txt.begin())) {
      std::cout << l << "; " << c << "\n";
      return false;
    }
    c += 1;
    txt.erase(0,1);
    txt = tira_esp(txt);

    int tam_i = tam_id(txt);
    std::string letras = txt.substr(0, tam_i);
    c += tam_i;
    txt.erase(0, tam_i);
    txt = tira_esp(txt);

    // Pega a lista de parâmetros.
    int tam_p = tam_param(txt);
    if (tam_p < 0) {
      std::cout << l << "; " << c << "\n";
      return false;
    }
    std::string parametros = txt.substr(0, tam_p);
    c += tam_p;
    txt.erase(0,tam_p);
    txt = tira_esp(txt);

    // Pega a lista de comandos (tamanho da função).
    int tam_f = tam_funcao(txt);
    if (tam_f < 0) {
      std::cout << l << "; " << c << "\n";
      return false;
    }
    c += 1;
    if (txt[tam_f] == *txt.end()) {
      return letra(letras) && listadeParametros(parametros) && listadeComandos_(txt.substr(1, tam_f-2);
    }
    else {
      return letra(letras) && listadeParametros(parametros) && listadeComandos_(txt.substr(1, tam_f-2) && listadeFuncoes(txt.substr(tam_f));
    }
  }
}

bool funcaoretorno(std::string txt) {
  txt = tira_esp(txt);
  // Pega o identificador.
  int tam_i = tam_id(txt)
  std::string id = txt.substr(0, tam_i);
  c += tam_i;
  txt.erase(0, tam_i);
  txt = tira_esp(txt);

  // Pega a lista de parâmetros.
  int tam_p = tam_param(txt);
  if (tam_p < 0) {
    std::cout << l << "; " << c << "\n";
    return false;
  }
  std::string parametros = txt.substr(0, tam_param);
  c += tam_param;
  txt.erase(0,tam_param);
  txt = tira_esp(txt);

  // Pega a lista de comandos (tamanho da função).
  int tam_f = tam_funcao(txt);
  if (tam_f < 0) {
    std::cout << l << "; " << c << "\n";
    return false;
  }

  // Pega o retorno.
  std::string retorno = str_retorno(txt);
  if (retorno == '') {
    std::cout << l << "; " << c << "\n";
    return false;
  }
  txt.erase(txt.find(retorno), retorno.size());

  c++;
  // Deriva.
  if (tam_f == 0) {
    return identificador(id) && listadeParametros(parametros) && listadeComandos_(txt.substr(1, tam_f-2) && comandodeRetorno(retorno);
  }
  else {
    return identificador(id) && listadeParametros(parametros) && listadeComandos_(txt.substr(1, tam_f-2) && comandodeRetorno(retorno) && listadeFuncoes(txt.substr(tam_f));
  }
}

bool listadeParametros(std::string txt) {
  txt = tira_esp(txt);
  if(txt.compare(0,1, '(') == 0) {
    txt.erase(0);
    c++;
  }
  txt = tira_esp(txt);
  if (txt.compare(0,1, ')') == 0) {
    c++;
    return true;
  }
  txt = tira_esp(txt);
  int i = 0;
  for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!=','; it++) {
    i++;
  }
  c += i;
  txt = tira_esp(txt);

  //  Caso so tenha um parametro deriva em Parametro.
  if (txt[i] == ')') {
    c += 1;
    return parametro(txt.substr(0,i-1));
  }

  //  Deriva em Parametro listadeParametros_.
  c += 1;
  return parametro(txt.substr(0,i-1)) && listadeParametros_(txt.substr(i,txt.end()-1));

}

bool listadeParametros_(std::string txt) {
  txt = tira_esp(txt);

  // Pega a virgula.
  if(txt[0] == ',') {
    txt.erase(0,1);
    c += 1;
  }
  else {
    std::cout << l << "; " << c << "\n";
    return false;
  }

  txt = tira_esp(txt);

  int i=0;
  for (std::string::iterator it=i; it!=txt.end() && *it!=','; it++) {
    i++;
  }

  //  Deriva em Parametro listadeParametros_.
  if(txt[i] == ',') {
    return parametro(txt.substr(0,i-1)) && listadeParametros_(txt.substr(i));
  }

  //  Caso so tenha um parametro deriva em Parametro.
  else {
    return parametro(txt);
  }
}

bool parametro(std::string txt) {
  txt = tira_esp(txt);

  int tam_tipo = tam_tipo(txt);
  // No caso da existencia no inicio de um Tipo: deriva em Tipo e Identificador.
  if (tam_tipo>0) {
    return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo, txt.end())));

  } else {
    if(txt.compare(0,5, "vetor") == 0) {
      txt.erase(0,5);
      c += 5;

      txt = tira_esp(txt);

      int tam_tipo = tam_tipo(txt);
      // Deriva para caso exista um Tipo
      if (tam_tipo>0) {
        // Encontra o Identificador
        int j = tam_tipo;
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Tipo Identificador;
        if (j==txt.end()) {
          return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo,txt.end())));
        }

        // Encontra o Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }
        //  Deriva em Tipo Identificador [Valor_Inteiro];
        return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo, j)) && valor_inteiro(txt.substr(j+2, k)));

      // Deriva para caso não exista um Tipo
      } else {
        int pos_como = txt.find("como");
        int j = pos_como+4;
        // Encontra o Identificador
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Identificador como Identificador;
        if (j==txt.end()) {
          return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,txt.end())));
        }

        // Encontra o Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }
        //  Deriva em Identificador como Identificador[Valor_Inteiro];
        return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,j)) && valor_inteiro(txt.substr(j+2, k)));
      }
    }
    if(txt.compare(0,6, "matriz") == 0) {
      txt = tira_esp(txt);

      txt.erase(0,6);
      c += 6;

      int tam_tipo = tam_tipo(txt);

      txt = tira_esp(txt);

      // Deriva para caso exista um Tipo
      if (tam_tipo>0) {
        // Encontra o Identificador
        int j = tam_tipo;
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Tipo Identificador;
        if (j==txt.end()) {
          return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo,txt.end())));
        }

        // Encontra o primeiro Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }

        // Encontra o segundo Valor_Inteiro
        int x = k+3;
        for(std::string::iterator it=k+3; it!=txt.end() && *it!=']'; it++) {
          x++;
        }

        //  Deriva em Tipo Identificador [Valor_Inteiro];
        return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo, j)) && valor_inteiro(txt.substr(j+2, k)) && valor_inteiro(txt.substr(k+3, x)));

      // Deriva para caso não exista um Tipo
      } else {
        int pos_como = txt.find("como");
        int j = pos_como+4;
        // Encontra o Identificador
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Identificador como Identificador;
        if (j==txt.end()) {
          return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,txt.end())));
        }

        // Encontra o primeiro Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }

        // Encontra o segundo Valor_Inteiro
        int x = k+3;
        for(std::string::iterator it=k+3; it!=txt.end() && *it!=']'; it++) {
          x++;
        }

        //  Deriva em Identificador como Identificador[Valor_Inteiro][Valor_Inteiro];
        return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,j)) && valor_inteiro(txt.substr(j+2, k)) && valor_inteiro(txt.substr(k+3, x)));
      }
    }
  }


}

bool comandodeRetorno(std::string txt) {
  txt = tira_esp(txt);
  if (txt.compare(0,7,"retorno")) {
    txt.erase(0,7);
    c += 7;
    txt = tira_esp(txt);
    if(txt.compare(0,1,"=")) {
        txt.erase(0,1);
        c++;
        txt = tira_esp(txt);
        return expressao(txt.substr(txt.begin(), txt.end()-1));
    }
  }
  return false;
}

bool listadeComandos(std::string txt) {
  txt = tira_esp(txt);
  if (txt[0] = '{') {
    txt.erase(0,1);
    c++;
  } else{
    return false
  }
  return listadeComandos_(txt.substr(0, txt.end()-1));
}

bool listadeComandos_(std::string txt) {
  int i = 0;
  for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!=';'; it++) {
    i++;
  }
  if (txt[i] == *txt.end()) {
    return false;
  }
  // Levar para Comando o tamanho exato do Escolha Caso;
  if (txt.compare(0,12, "escolha caso")) {
    txt_auxiliar = txt;
    txt_auxiliar.erase(0,12);
    int i = 12;
    pos_entao = txt_auxiliar.find("entao");
    i+=pos_entao+5;
    txt_auxiliar.erase(0, pos_entao+4);
    tam_escolha = tam_funcao(txt_auxiliar);
    i+=tam_escolha;
    txt_auxiliar.erase(0,tam_escolha);
    while (1==1){
      if (txt.compare(0,4, "caso")) {
        i+=4;
        txt_auxiliar.erase(0,4);
        pos_entao = txt_auxiliar.find("entao");
        i+=pos_entao+5;
        txt_auxiliar.erase(0, pos_entao+4);
        tam_escolha = tam_funcao(txt_auxiliar);
        i+=tam_escolha;
        txt_auxiliar.erase(0,tam_escolha);
      }
      else if (txt.compare(0,14, "caso contrario")) {
        i+=14;
        txt_auxiliar.erase(0,14);
        tam_escolha = tam_funcao(txt_auxiliar);
        i+=tam_escolha;
        txt_auxiliar.erase(0,tam_escolha);
      } else {
        break;
      }
    }
    return (comando(txt.substr(0, i)) && listadeComandos_(txt.substr(i+1,txt.end()));

  }

  // Levar para Comando o tamanho exato do Caso;
  if (txt.compare(0,4, "caso")) {
    txt_auxiliar = txt;
    txt_auxiliar.erase(0,4);
    int i = 4;
    pos_entao = txt_auxiliar.find("entao");
    i+=pos_entao+5;
    txt_auxiliar.erase(0, pos_entao+4);
    tam_escolha = tam_funcao(txt_auxiliar);
    i+=tam_escolha;
    return (comando(txt.substr(0, i)) && listadeComandos_(txt.substr(i+1,txt.end()));

  }

  return (comando(txt.substr(0, i-1)) && listadeComandos_(txt.substr(i+1,txt.end()));

}

bool comando(std::string txt) {


  if (txt.compare(0,3, "leia")) {
    txt.erase(0,3);
    // Deriva em leia (Identificador).
    return identificador(txt.substr(1,txt.end()-1));

  }
  if (txt.compare(0,7, "escreva")) {
    txt.erase(0,7);
    // Deriva em escreva (Identificador).
    return identificador(txt.substr(1,txt.end()-1));

  }
  int tam_tipo = tam_tipo(txt);
  // No caso da existencia no inicio de um Tipo: deriva em Tipo e Identificador.
  if (tam_tipo>0) {
    return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo, txt.end())));

  } else {
    if (txt.compare(0,4, "caso")) {
      txt.erase(0,4);
      pos_entao = txt.find("entao");
      if (pos_entao>0) {
        // Deriva em caso (expressaoLogica) entao {listadeComandos}
        return (expressaoLogica(txt.substr(1, pos_entao-2)) && listadeComandos(txt.substr(pos_entao+5, txt.end())))
      } else {
        return false;
      }
    }
    if (txt.compare(0,12, "escolha caso")) {
      txt.erase(0,12);
      pos_entao = txt.find("entao");
      if (pos_caso_contrario>0) {
        int tam_conteudo_entao = tam_funcao(txt.substr(pos_entao+5, txt.end()));

          // Deriva em escolha caso (expressaoLogica) entao {listadeComandos} <listadeCondicionalCaso>
        return (expressaoLogica(txt.substr(1, pos_entao-2)) && listadeComandos(txt.substr(pos_entao+5, pos_entao+5+tam_conteudo_entao)) && listadeCondicionalCaso(txt.substr(pos_entao+5+tam_conteudo_entao, txt.end())))
      } else {
        return false;
      }
    }

    if(txt.compare(0,5, "vetor") == 0) {
      txt.erase(0,5);
      int tam_tipo = tam_tipo(txt);
      // Deriva para caso exista um Tipo
      if (tam_tipo>0) {
        // Encontra o Identificador
        int j = tam_tipo;
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Tipo Identificador;
        if (j==txt.end()) {
          return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo,txt.end())));
        }

        // Encontra o Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }
        //  Deriva em Tipo Identificador [Valor_Inteiro];
        return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo, j)) && valor_inteiro(txt.substr(j+2, k)));

      // Deriva para caso não exista um Tipo
      } else {
        int pos_como = txt.find("como");
        int j = pos_como+4;
        // Encontra o Identificador
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Identificador como Identificador;
        if (j==txt.end()) {
          return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,txt.end())));
        }

        // Encontra o Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }
        //  Deriva em Identificador como Identificador[Valor_Inteiro];
        return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,j)) && valor_inteiro(txt.substr(j+2, k)));
      }
    }
    if(txt.compare(0,6, "matriz") == 0) {
      txt.erase(0,6);
      int tam_tipo = tam_tipo(txt);
      // Deriva para caso exista um Tipo
      if (tam_tipo>0) {
        // Encontra o Identificador
        int j = tam_tipo;
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Tipo Identificador;
        if (j==txt.end()) {
          return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo,txt.end())));
        }

        // Encontra o primeiro Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }

        // Encontra o segundo Valor_Inteiro
        int x = k+3;
        for(std::string::iterator it=k+3; it!=txt.end() && *it!=']'; it++) {
          x++;
        }

        //  Deriva em Tipo Identificador [Valor_Inteiro];
        return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo, j)) && valor_inteiro(txt.substr(j+2, k)) && valor_inteiro(txt.substr(k+3, x)));

      // Deriva para caso não exista um Tipo
      } else {
        int pos_como = txt.find("como");
        int j = pos_como+4;
        // Encontra o Identificador
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Identificador como Identificador;
        if (j==txt.end()) {
          return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,txt.end())));
        }

        // Encontra o primeiro Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }

        // Encontra o segundo Valor_Inteiro
        int x = k+3;
        for(std::string::iterator it=k+3; it!=txt.end() && *it!=']'; it++) {
          x++;
        }

        //  Deriva em Identificador como Identificador[Valor_Inteiro][Valor_Inteiro];
        return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,j)) && valor_inteiro(txt.substr(j+2, k)) && valor_inteiro(txt.substr(k+3, x)));
      }
    }
    if(txt.compare(0,8, "Complexo") == 0) {
      txt.erase(0,8);
      int j = 0;
      for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!='{'; it++) {
        j++;
      }
      if (j==txt.end()) {
        return false;
      }
      else{
        // Encontra a lista de declarações.
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!='}'; it++) {
          k++;
        }
        //  Deriva em Identificador {listadeDeclaracoes}.
        return (identificador(txt.substr(0,j)) && listadeDeclaracoes(txt.substr(j+2, k)));
      }
    }
    // Procura o primeiro caso "como".
    int pos_como = txt.find("como");
    if (pos_como>0) {
      // Deriva no primeiro caso Letra como Identificador.
      return (letra(txt.substr(0, pos_como-1)) && identificador(txt.substr(pos_como+4, txt.end())));
    } else {

      // Procura a igualdade no segundo caso.
      int pos_igualdade = txt.find('=');
      std::string texto = '';

      // Verifica se é igualado a um texto.
      if (txt[pos_igualdade+1] == '"') {
        texto = txt.substr(pos_igualdade+2, txt.end()-1);
      }

      // Procura caso de letras [Valor Inteiro].
      int pos_colchete_1 = txt.find('[');
      if (pos_colchete_1>0 && pos_igualdade>pos_colchete_1) {
        int pos_colchete_2 = txt.substr(pos_colchete_1+1, txt.end()).find('[');

        // Procura caso de letras [Valor Inteiro][Valor_Inteiro].
        if (pos_colchete_2>0 && pos_igualdade>pos_colchete_1) {
          if (texto.size()>0) {


            // Procura caso de letras [Valor Inteiro][Valor_Inteiro] = "texto".
            return (letra(txt.substr(0, pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_colchete_2-2)) && valorInteiro(txt.substr(pos_colchete_2+1, pos_igualdade-1)) && texto(texto));
          }


          // Procura caso de letras [Valor Inteiro][Valor_Inteiro] = Expressao.
          return (letra(txt.substr(0, pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_colchete_2-2)) && valorInteiro(txt.substr(pos_colchete_2+1, pos_igualdade-1)) && expressao(txt.substr(pos_igualdade+1, txt.end())));
        }
        if (texto.size()>0) {

          // Procura caso de letras [Valor Inteiro] = "texto".
          return (letra(txt.substr(0, pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_igualdade-1)) && texto(texto));
        }

        // Procura caso de letras [Valor Inteiro] = Expressao.
        return (letra(txt.substr(0, pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_igualdade-1)) && expressao(txt.substr(pos_igualdade+1, txt.end())));
      }
      pos_barra = txt.find('/');
      if (pos_barra>0 && pos_igualdade>pos_barra) {

        // Deriva em Letras / atribuicao OU Letras / atribuicaodeAtributo.
        return (letra(txt.substr(0, pos_barra-1)) &&  (atribuicao(txt.substr(pos_barra+1, txt.end())) || atribuicaodeAtributo(txt.substr(pos_barra+1, txt.end()))));
      }

      if (pos_igualdade<0) {
        pos_parenteses = txt.find('(');
        if (pos_parenteses>0) {

          // Deriva em Letras (listadeIdentificadores).
          return (letra(txt.substr(0, pos_parenteses-1)) &&   listadeIdentificadores(txt.substr(pos_parenteses+1, txt.end()-1)));
        }
      }

      if (texto.size()>0) {

        // Deriva em Letras = "texto".
        return (letra(txt.substr(0, pos_igualdade-1)) && texto(texto));
      } else {

        // Deriva em Letras = expressao OU Letras = chamadadeFuncao.
        return (letra(txt.substr(0, pos_igualdade-1)) && (chamadadeFuncao(txt.substr(pos_igualdade+1, txt.end())) || expressao(txt.substr(pos_igualdade+1, txt.end()))));
      }
    }
  }
  return false;
}

bool chamadadeFuncao(std::string txt) {
  // Pega o identificador.
  if (!std::isalpha(*txt.begin())) {
    return false;
  }
  txt.erase(0,1);

  int tam_i = tam_id(txt);
  std::string letras = txt.substr(0, tam_i);
  txt.erase(0, tam_i);

  // Consome "(".
  if(txt[0] != '(') {
    return false;
  }
  txt.erase(0,1);

  // Se não é passado parâmetros.
  if(txt[0] == ')') {
    return letra(letras);
  }
  else {
    // Consome o ")".
    if (*txt.end() == ')') {
      // Pega a lista de ids.
      std::string ids = txt.substr(txt.begin(),txt.end()-1);
      return letra(letras) && listadeIdentificadores(ids);
    }
    return false;
  }
}

bool declaracaodeEstrutura(std::string txt) {
  // Consome o "complexo".
  if (txt.compare(0,8,"complexo") != 0) {
    return false;
  }
  txt.erase(0,8);

  // Se existe identificador.
  if (txt[0] == '{') {
    return false;
  }

  // Pega o identificador.
  int tam_i = tam_id(txt);
  std::string id = txt.substr(0, tam_i);
  txt.erase(0, tam_i);

  // Consome o '{'.
  if (txt[0] != '{') {
    return false;
  }
  txt.erase(0,1);

  // Se não é passado declarações.
  if(txt[0] == '}') {
    return identificador(id);
  }
  else {
    // Consome o '}'.
    if (*txt.end() == '}') {
      // Pega a lista de declarações.
      std::string declaracoes = txt.substr(txt.begin(),txt.end()-1);
      return identificador(id) && listadeDeclaracoes(declaracoes);
    }
    return false;
  }
}

bool listadeDeclaracoes(std::string txt) {
  if(txt.compare(0,3,"int") == 0) {
    txt.erase(0,3);
    if(txt.find(';') != -1) {
      std::string id = txt.substr(0,txt.find(';'));
      txt.erase(0,txt.find(';'));
      if(txt.size()>0) {
        return identificador(id) && listadeDeclaracoes(txt);
      }
      else {
        return identificador(id);
      }
    }
    return false;
  }
  if(txt.compare(0,2,"pf") == 0) {
    txt.erase(0,2);
    if(txt.find(';') != -1) {
      std::string id = txt.substr(0,txt.find(';'));
      if(txt.size()>0) {
        return identificador(id) && listadeDeclaracoes(txt);
      }
      else {
        return identificador(id);
      }
    }
    return false;
  }
  if(txt.compare(0,6,"logico") == 0) {
    txt.erase(0,6);
    if(txt.find(';') != -1) {
      std::string id = txt.substr(0,txt.find(';'));
      if(txt.size()>0) {
        return identificador(id) && listadeDeclaracoes(txt);
      }
      else {
        return identificador(id);
      }
    }
    return false;
  }
  if(txt.compare(0,5,"texto") == 0) {
    txt.erase(0,5);

    if(txt.find(';') != -1) {
      std::string id = txt.substr(0,txt.find(';'));
      if(txt.size()>0) {
        return identificador(id) && listadeDeclaracoes(txt);
      }
      else {
        return identificador(id);
      }
    }
    return false;
  }
  if(txt.compare(0,5,"vetor") == 0) {
    if(txt.find("[") == -1 || txt.find(";") < txt.find("[")) {
      return false;
    }

    if(txt.find("como") < txt.find("[") && txt.find("como") != -1) {
      std::string id1 = txt.substr(0,txt.find("como"));
      txt.erase(0,id1.size()+4);

      std::string id2 = txt.substr(0,txt.find("["));
      txt.erase(0,id2.size()+1);

      if(txt.find("]") == -1) {
        return false;
      }
      std::string v = txt.substr(0,txt.find("]"));
      txt.erase(0,v.size()+1);

      txt.erase(0,1);
      if(txt.size() > 0) {
        return identificador(id1) && identificador(id2) && valorInteiro(v) && listadeDeclaracoes(txt);
      }
      return identificador(id1) && identificador(id2) && valorInteiro(v);
    }

    // Pega tipo.
    int tam_t = tam_tipo(txt);
    std::string t = txt.substr(0,tam_t);
    txt.erase(0,tam_t);

    if(txt.find("[") == -1 || txt.find(";") < txt.find("[")) {
      return false;
    }
    std::string id = txt.substr(0,txt.find("["));
    txt.erase(0,id.size()+1);

    if(txt.find("]") == -1) {
      return false;
    }
    std::string v = txt.substr(0,txt.find("]"));
    txt.erase(0,v.size()+1);

    txt.erase(0,1);
    if(txt.size() > 0) {
      return tipo(t) && identificador(id) && valorInteiro(v) && listadeDeclaracoes(txt);
    }
    return tipo(t) && identificador(id) && valorInteiro(v);
  }
  if(txt.compare(0,6,"matriz") == 0) {
    if(txt.find("[") == -1 || txt.find(";") < txt.find("[")) {
      return false;
    }

    if(txt.find("como") < txt.find("[") && txt.find("como") != -1) {
      std::string id1 = txt.substr(0,txt.find("como"));
      txt.erase(0,id1.size()+4);

      std::string id2 = txt.substr(0,txt.find("["));
      txt.erase(0,id2.size()+1);

      if(txt.find("]") == -1) {
        return false;
      }
      std::string v1 = txt.substr(0,txt.find("]"));
      txt.erase(0,v1.size()+1);

      if(txt.find("[") == -1 || txt.find(";") < txt.find("[")) {
        return false;
      }
      if(txt.find("]") == -1) {
        return false;
      }
      std::string v2 = txt.substr(0,txt.find("]"));
      txt.erase(0,v2.size()+1);

      txt.erase(0,1);
      if(txt.size() > 0) {
        return identificador(id1) && identificador(id2) && valorInteiro(v1) && valorInteiro(v2) && listadeDeclaracoes(txt);
      }
      return identificador(id1) && identificador(id2) && valorInteiro(v1) && valorInteiro(v2);
    }
    // Pega tipo.
    int tam_t = tam_tipo(txt);
    std::string t = txt.substr(0,tam_t);
    txt.erase(0,tam_t);

    if(txt.find("[") == -1 || txt.find(";") < txt.find("[")) {
      return false;
    }
    std::string id = txt.substr(0,txt.find("["));
    txt.erase(0,id.size()+1);

    if(txt.find("]") == -1) {
      return false;
    }
    std::string v1 = txt.substr(0,txt.find("]"));
    txt.erase(0,v1.size()+1);

    if(txt.find("[") == -1 || txt.find(";") < txt.find("[")) {
      return false;
    }
    if(txt.find("]") == -1) {
      return false;
    }
    std::string v2 = txt.substr(0,txt.find("]"));
    txt.erase(0,v2.size()+1);

    txt.erase(0,1);
    if(txt.size() > 0) {
      return tipo(t) && identificador(id) && valorInteiro(v1) && valorInteiro(v2) && listadeDeclaracoes(txt);
    }
    return tipo(t) && identificador(id) && valorInteiro(v1) && valorInteiro(v2);
  }
  // Pega o identificador.
  if (!std::isalpha(*txt.begin())) {
    return false;
  }
  txt.erase(0,1);

  int tam_i = tam_id(txt);
  std::string letras = txt.substr(0, tam_i);
  txt.erase(0, tam_i);

  if(txt.find("como") == -1 || (txt.find("como") > txt.find(";")) {
    return false;
  }

  if(txt.find(";") == -1) {
    return false;
  }
  std::string id = txt.substr(0,txt.find(";"));
  txt.erase(0,id.size()+1);

  if(txt.size() > 0) {
    return letra(letras) && identificador(id) && listadeDeclaracoes(txt);
  }
  return letra(letras) && identificador(id);
}

bool declaracao(std::string txt) {
  // Consome o tipo.
  if (txt.compare(0,5,"vetor") == 0) {
    txt.erase(0,5);

    // Pega tipo.
    int tam_t = tam_tipo(txt);
    std::string t = txt.substr(0,tam_t);
    txt.erase(0,tam_t);

    // Pega identificador.
    std::string id;
    if (txt.find('[') == -1) {
      return false;
    }
    id = txt.substr(0,txt.find('['));
    txt.erase(0,id.size());

    // Pega o valor inteiro.
    std::string v;
    if (*txt.end() == ';' && *(txt.end()-1) == ']') {
      v = txt.substr(txt.begin()+1,txt.end()-2);
      return tipo(t) && identificador(id) && valorInteiro(v);
    }
    return false;
  }
  if (txt.compare(0,6,"matriz") == 0) {
    txt.erase(0,6);

    // Pega tipo.
    int tam_t = tam_tipo(txt);
    std::string t = txt.substr(0,tam_t);
    txt.erase(0,tam_t);

    // Pega identificador.
    std::string id;
    if (txt.find('[') == -1) {
      return false;
    }
    id = txt.substr(0,txt.find('['));
    txt.erase(0,id.size());
    txt.erase(0,1);

    // Pega o primeiro valor inteiro.
    std::string v1;
    if (txt.find(']') == -1) {
      return false;
    }
    v1 = txt.substr(0,txt.find(']'));
    txt.erase(0,v1.size());

    // Pega o segundo valor inteiro.
    std::string v2;
    if (*txt.end() == ';' && *(txt.end()-1) == ']') {
      v2 = txt.substr(txt.begin()+1,txt.end()-2);
      return tipo(t) && identificador(id) && valorInteiro(v1) && valorInteiro(v2);
    }
    return false;
  }
  if (txt.compare(0,3,"int") == 0) {
    txt.erase(0,3);

    // Pega o identificador.
    std::string id;
    if (*txt.end() == ";") {
      id = txt.substr(txt.begin(), txt.end()-1);
      return identificador(id);
    }
    return false;
  }
  if (txt.compare(0,2,"pf") == 0) {
    txt.erase(0,2);

    // Pega o identificador.
    std::string id;
    if (*txt.end() == ";") {
      id = txt.substr(txt.begin(), txt.end()-1);
      return identificador(id);
    }
    return false;
  }
  if (txt.compare(0,6,"logico") == 0) {
    txt.erase(0,6);

    // Pega o identificador.
    std::string id;
    if (*txt.end() == ";") {
      id = txt.substr(txt.begin(), txt.end()-1);
      return identificador(id);
    }
    return false;
  }
  if (txt.compare(0,5,"texto") == 0) {
    txt.erase(0,5);

    // Pega o identificador.
    std::string id;
    if (*txt.end() == ";") {
      id = txt.substr(txt.begin(), txt.end()-1);
      return identificador(id);
    }
    return false;
  }
  return false;
}

bool atribuicao(std::string txt) {

  // Procura a igualdade no segundo caso.
  int pos_igualdade = txt.find('=');
  std::string texto = '';

  // Verifica se é igualado a um texto.
  if (txt[pos_igualdade+1] == '"') {
    texto = txt.substr(pos_igualdade+2, txt.end()-1);
  }
  if (pos_igualdade>0) {
    int pos_colchete_1 = txt.find('[');
    if (pos_colchete_1>0 && pos_igualdade>pos_colchete_1) {
      int pos_colchete_2 = txt.substr(pos_colchete_1+1, txt.end()).find('[');

      // Procura caso de letras [Valor Inteiro][Valor_Inteiro].
      if (pos_colchete_2>0 && pos_igualdade>pos_colchete_1) {
        if (texto.size()>0) {


          // Procura caso de letras [Valor Inteiro][Valor_Inteiro] = "texto".
          return (letra(txt.substr(0, pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_colchete_2-2)) && valorInteiro(txt.substr(pos_colchete_2+1, pos_igualdade-1)) && texto(texto));
        }


        // Procura caso de letras [Valor Inteiro][Valor_Inteiro] = Expressao.
        return (letra(txt.substr(0, pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_colchete_2-2)) && valorInteiro(txt.substr(pos_colchete_2+1, pos_igualdade-1)) && expressao(txt.substr(pos_igualdade+1, txt.end())));
      }
      if (texto.size()>0) {

        // Procura caso de letras [Valor Inteiro] = "texto".
        return (letra(txt.substr(0, pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_igualdade-1)) && texto(texto));
      }

      // Procura caso de letras [Valor Inteiro] = Expressao.
      return (letra(txt.substr(0, pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_igualdade-1)) && expressao(txt.substr(pos_igualdade+1, txt.end())));
    }

    if (texto.size()>0) {

      // Deriva em Letras = "texto".
      return (letra(txt.substr(0, pos_igualdade-1)) && texto(texto));
    } else {

      // Deriva em Letras = expressao OU Letras = chamadadeFuncao.
      return (letra(txt.substr(0, pos_igualdade-1)) && (chamadadeFuncao(txt.substr(pos_igualdade+1, txt.end())) || expressao(txt.substr(pos_igualdade+1, txt.end()))));
    }
  }
  return false;
}

bool atribuicaodeEstrututra(std::string txt) {
  if(txt.compare(0,6,"matriz") == 0) {
    if(txt.find("[") == -1) {
      return false;
    }
    if(txt.find("como") < txt.find("[") && txt.find("como") != -1) {
      std::string id1 = txt.substr(0,txt.find("como"));
      txt.erase(0,id1.size()+4);

      std::string id2 = txt.substr(0,txt.find("["));
      txt.erase(0,id2.size()+1);

      if(txt.find("]") == -1) {
        return false;
      }
      std::string v1 = txt.substr(0,txt.find("]"));
      txt.erase(0,v1.size()+1);

      if(txt.find("[") == -1) {
        return false;
      }
      if(txt.find("]") == -1) {
        return false;
      }
      std::string v2 = txt.substr(0,txt.find("]"));
      txt.erase(0,v2.size()+1);

      if(txt.find(";") == -1) {
        return false;
      }
      txt.erase(0,1);
      return identificador(id1) && identificador(id2) && valorInteiro(v1) && valorInteiro(v2);
    }
    return false;
  }
  if(txt.compare(0,5,"vetor") == 0) {
    if(txt.find("[") == -1) {
      return false;
    }
    if(txt.find("como") < txt.find("[") && txt.find("como") != -1) {
      std::string id1 = txt.substr(0,txt.find("como"));
      txt.erase(0,id1.size()+4);

      std::string id2 = txt.substr(0,txt.find("["));
      txt.erase(0,id2.size()+1);

      if(txt.find("]") == -1) {
        return false;
      }
      std::string v = txt.substr(0,txt.find("]"));
      txt.erase(0,v.size()+1);

      if(txt.find(";") == -1) {
        return false;
      }
      txt.erase(0,1);
      return identificador(id1) && identificador(id2) && valorInteiro(v);
    }
    return false;
  }
  if (!std::isalpha(*txt.begin())) {
    return false;
  }
  txt.erase(0,1);

  int tam_i = tam_id(txt);
  std::string letras = txt.substr(0, tam_i);
  txt.erase(0, tam_i);

  if(txt.find("como") == -1 || (txt.find("como") > txt.find(";")) {
    return false;
  }

  if(txt.find(";") == -1) {
    return false;
  }
  std::string id = txt.substr(0,txt.find(";"));
  txt.erase(0,id.size()+1);

  return letra(letras) && identificador(id);
}

bool atribuicaodeAtributo(std::string txt) {

}

bool listadeCondicionalCaso(std::string txt) {
  if (txt.compare(0,4, "caso")) {
    txt.erase(0,4);
    pos_entao = txt.find("entao");
    if (pos_entao>0) {
      int tam_entao = tam_funcao(txt.substr(pos_entao+4, txt.end()));

      // Deriva em caso (expressaoLogica) entao {listadeComandos} listadeCondicionalCaso
      return (expressaoLogica(txt.substr(1, pos_entao-2)) && listadeComandos_(txt.substr(pos_entao+6,pos_entao+4+tam_entao-2)) && listadeCondicionalCaso(txt.substr(pos_entao+4+tam_entao, txt.end())))
    } else {
      return false;
    }
  } else if (txt.compare(0, 14, "caso contrario")) {
    txt.erase(0,14);
    return (listadeComandos_(txt.begin()+1, txt.end()-1));
  }
  return false;
}

bool listadeIdentificadores(std::string txt) {

}

bool tipo(std::string txt) {
  if (txt == "int" || txt == "pf" || txt == "logico" || txt == "texto") {
    return true;
  }
  return false;
}

bool expressao(std::string txt) {
  if (txt.compare(0,1, '-')) {
    txt.erase(0,1);
    if (std::isalpha(*txt.begin()) || txt.compare(0,1, '(')) {
      // Deriva em - Expressao Aritmetica OU - Expressao Logica
      return (expressaoAritmetica(txt) || expressaoLogica(txt));
    }
  }
  if (txt.compare(0,1, '(')) {
    txt.erase(0,1);
    int tam_parenteses = 0;
    for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!=')'; it++) {
      tam_parenteses++;
    }
    // Deriva em (Expressão Aritmetica) Expressao Aritmetica OU (Expressão Aritmetica) Expressao logica OU (Expressão Logica) Expressao Logica
    return ((expressaoAritmetica(txt.substr(txt.begin(), j)) && (expressaoAritmetica(txt.substr(j+2, txt.end())) || expressaoLogica(txt.substr(j+2, txt.end())))) || (expressaoLogica(txt.substr(txt.begin(), j)) && expressaoLogica(txt.substr(j+2, txt.end()))));
  }
  if (txt.compare(0,10, "Verdadeiro")) {
    txt.erase(0,10);
    // Deriva em Verdadeiro Expressao Logica
    return (expressaoLogica(txt));
  }
  if (txt.comparre(0,5, "Falso")) {
    txt.erase(0,5);
    // Deriva em Falso Expressao logica
    return (expressaoLogica(txt));
  }
  if (std::isalpha(*txt.begin())) {
    int pos_expressao = 0;
    for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!='*' && *it!='/' && *it!='%' && *it!='+' && *it!='-'; it++) {
      pos_expressao++;
    }
    if (it!=txt.end()) {
      // Deriva em <letras> <expressaoAritmetica> OU <letras> <expressaoLogica>
      return (letra(txt.substr(txt.begin(), pos_expressao)) && (expressaoAritmetica(txt.substr(pos_expressao+2, txt.end())) || expressaoLogica(txt.substr(pos_expressao+2, txt.end()))));
    }

    int pos_colchete_1 = txt.find('[');
    int pos_colchete_2 = txt.find(']');
    int pos_colchete_3 = txt.substr(pos_colchete_2, txt.end()).find('[');
    int pos_colchete_4 = txt.substr(pos_colchete_2, txt.end()).find(']');
    if (pos_colchete_1>0) {
      if (pos_colchete_3>0) {
        // Deriva em <Letras> [Valor Inteiro][Valor Inteiro] <expressaoAritmetica> OU <Letras> [Valor Inteiro][Valor Inteiro] <expressaoLogica>
        return (letra(txt.substr(txt.begin(), pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_colchete_2-1)) && valorInteiro(txt.substr(pos_colchete_2+pos_colchete_3+1, pos_colchete_2+pos_colchete_4-1)) && (expressaoAritmetica(txt.substr(pos_colchete_2+pos_colchete_4+1, txt.end())) || expressaoLogica(txt.substr(pos_colchete_2+pos_colchete_4+1, txt.end()))));
      }
      // Deriva em <Letras> [Valor Inteiro] <expressaoAritmetica> OU <Letras> [Valor Inteiro][Valor Inteiro] <expressaoLogica>
      return (letra(txt.substr(txt.begin(), pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_colchete_2-1)) && (expressaoAritmetica(txt.substr(pos_colchete_2+pos_colchete_4+1, txt.end())) || expressaoLogica(txt.substr(pos_colchete_2+pos_colchete_4+1, txt.end()))));
    }
    return (letra(txt.substr(txt.begin(), pos_expressao));

  }

  if (txt.compare(0,1, '!')) {
    txt.erase(0,1);
    return  expressaoLogica(txt);
  }
  std::string inteiros[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  if (txt.compare(0,1, '-')) {
    txt.erase(0,1);
    bool inteiro = false;
    for (size_t i = 0; i < 10; i++) {
      if ((txt.substr(0,1)).find(tipos[i]) > 0) {
        inteiro = true;
        break;
      }
    }
    if (inteiro) {
      int pos_ponto = txt.find('.');
      if (pos_ponto>0) {
        int pos_expressao = 0;
        for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!='*' && *it!='/' && *it!='%' && *it!='+' && *it!='-'; it++) {
          pos_expressao++;
        }
        if (it!=txt.end()) {
          // Deriva em - Valor . Valor <expressaoAritmetica> OU - Valor . Valor <expressaoLogica>
          return (valor(txt.substr(txt.begin(), pos_ponto)) && valor(txt.substr(pos_ponto+2, pos_expressao)) && (expressaoAritmetica(txt.substr(pos_expressao+2, txt.end())) || expressaoLogica(txt.substr(pos_expressao+2, txt.end()))));
        }

        // Deriva em - Valor . Valor
        return (valor(txt.substr(txt.begin(), pos_ponto)) && valor(txt.substr(pos_ponto+2, pos_expressao)));
      }
      int pos_expressao = 0;
      for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!='*' && *it!='/' && *it!='%' && *it!='+' && *it!='-'; it++) {
        pos_expressao++;
      }
      if (it!=txt.end()) {
        // Deriva em - Valor . Valor <expressaoAritmetica> OU - Valor . Valor <expressaoLogica>
        return (valor(txt.substr(txt.begin(), pos_expressao)) && (expressaoAritmetica(txt.substr(pos_expressao+2, txt.end())) || expressaoLogica(txt.substr(pos_expressao+2, txt.end()))));
      }

      // Deriva em - Valor
      return (valor(txt.substr(txt.begin(), pos_expressao));
    }
  } else {
    bool inteiro = false;
    for (size_t i = 0; i < 10; i++) {
      if ((txt.substr(0,1)).find(tipos[i]) > 0) {
        inteiro = true;
        break;
      }
    }
    if (inteiro) {
      int pos_ponto = txt.find('.');
      if (pos_ponto>0) {
        int pos_expressao = 0;
        for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!='*' && *it!='/' && *it!='%' && *it!='+' && *it!='-'; it++) {
          pos_expressao++;
        }
        if (it!=txt.end()) {
          // Deriva em  Valor . Valor <expressaoAritmetica> OU  Valor . Valor <expressaoLogica>
          return (valor(txt.substr(txt.begin(), pos_ponto)) && valor(txt.substr(pos_ponto+2, pos_expressao)) && (expressaoAritmetica(txt.substr(pos_expressao+2, txt.end())) || expressaoLogica(txt.substr(pos_expressao+2, txt.end()))));
        }

        // Deriva em Valor . Valor
        return (valor(txt.substr(txt.begin(), pos_ponto)) && valor(txt.substr(pos_ponto+2, pos_expressao)));
      }
      int pos_expressao = 0;
      for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!='*' && *it!='/' && *it!='%' && *it!='+' && *it!='-'; it++) {
        pos_expressao++;
      }
      if (it!=txt.end()) {
        // Deriva em Valor <expressaoAritmetica> OU  Valor <expressaoLogica>
        return (valor(txt.substr(txt.begin(), pos_expressao)) && (expressaoAritmetica(txt.substr(pos_expressao+2, txt.end())) || expressaoLogica(txt.substr(pos_expressao+2, txt.end()))));
      }

      // Deriva em Valor
      return (valor(txt.substr(txt.begin(), pos_expressao));
    }
  }
  return false;

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

  if(*txt.begin() == '0') {
    txt.erase(0,1);

    if(*txt.begin() == '.') {
      txt.erase(0,1);
      return valor(txt);
    }
    return false;
  }

  else {
    if (!std::isdigit(*txt.begin())) {
      return false;
    }
    txt.erase(0,1);

    if (txt.find('.') == -1) {
      return false;
    }
    if (txt.find('.') == 0 && *txt.end() != '.') {
      txt.erase(0,1);
      return valor(txt);
    }
    if(*txt.end() != '.') {
      std::string v1 == txt.substr(0,txt.find('.'));
      std::string v2 == txt.substr(txt.find('.')+1);
      return valor(v1) && valor(v2);
    }
    return false;
  }
}

bool valorInteiro(std::string txt) {
  if(txt.size() == 1) {
    if(*txt.begin() == '0') {
      return true;
    }
    else {
      return false;
    }
  }
  if(*txt.begin() == '-'){
    txt.erase(0,1);
  }
  if(std::isdigit(*txt.begin()) && *txt.begin() != '0') {
    txt.erase(0,1);
    return valor(txt);
  }
  else {
    return false;
  }
}

bool valor(std::string txt) {
  if(txt.size() > 1) {
    if(!std::isdigit(*txt.begin())) {
      return false
    }
    txt.erase(0,1);
    return valor(txt);
  }
  else {
    if(!std::isdigit(*txt.begin())) {
      return false
    }
    return true;
  }
}

bool texto(std::string txt) {
  if(txt.size() == 1) {
    if(*txt.begin() == '\0') {
      return true;
    }
    else {
      return false;
    }
  }
  if(std::isalnum(*txt.begin())) {
    txt.erase(0,1);
    return texto(txt);
  }
  std::string sym[] = {"_", "|", ",", ".", "<", ">", ":", "/", "?", "]", "[", "=", "+", "-", "*", "!", "@", "#", "%", " ", "\n"};
  for(int i = 0; i < 21; i++) {
    if(*txt.begin() == sym[i]) {
      txt.erase(0,1);
      return texto(txt);
    }
  }
  return false;
}

bool letra(std::string txt) {
  if (txt.size() > 1) {
    if (!std::isalpha(*txt.begin())) {
      return false;
    }
    txt.erase(0,1);
    return letra(txt);
  }
  else {
    if (!std::isalpha(*txt.begin())) {
      return false;
    }
    return true;
  }
}

bool identificador(std::string txt) {
  std::locale loc;
  for(std::string::iterator it=txt.begin(); it!=txt.end(); it++) {
    if (!std::isalpha(*it,loc)) {
      return false;
    }
  }
  return true;
}

int main() {

  c=0;
  l=0;
  // Lê o arquivo passado como: "./exemplo < <nome_do_arquivo>.txt".
  std::string entrada(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());
  entrada.pop_back();

  // Retorna a análise da gramática.
  std::cout << programa(entrada) << std::endl;

  return 0;
}
