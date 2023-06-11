#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct tAlunos{
    int matricula;
    string nome;
    float notas[3];
};

const short int tam = 3;

bool verificarUnicidade(string date, string matricula){
    fstream arq;
    bool flag = false;
    string linha, linhaAux;
    short int cont;
    arq.open(date);
     while(getline(arq,linha)){
        if(!flag){
            cont = 0;
            while(linha[cont] != ','){ //pegando apenas a matricula
                linhaAux += linha[cont];
                cont++;
            }
        }
        if (linhaAux == matricula) flag = true;//verificando se existe a matricula
        linhaAux = "";
    }
    arq.close();
    return flag;
}

void cadastrar(string date, int mat ,string nom, float vet[]){
    fstream arq;
    arq.open(date,  ios::app);
    arq <<  mat;
    arq << ", " << nom << ", ";
    arq << vet[0] << ", " << vet[1] << ", " << vet[2] << ",\n";
    arq.close(); 
}

int impedirMatriculasNegativas(){
    int mat;
    do{ cout << "\nDigite a matricula do aluno: ";
        cin >> mat;
    }while(mat < 0);//impedir matriculas negativas
    return mat;
}

void remover(string date, string dateTem, int posicao){
    fstream arq, arqTem;
    string linha, linhaAux;
    int atual = 1;
    arq.open(date, ios::in);
    arqTem.open(dateTem, ios::out);
    if(arq.is_open() || arqTem.is_open()){
        while(getline(arq, linha)){
            if(atual != posicao){//Não armazenar a linha removida 
                arqTem << linha << "\n";
            }
            atual++;
        }
    }
    arq.close();
    arqTem.close();
    remove(date.c_str());
    rename(dateTem.c_str(), date.c_str());//aletarndo o nome do arquivo temporario
}

int main(){

    fstream arquivo, arquivoTem;
    string aux, linha, nome, linhaAux, dados = "date.txt" ,dadosTem = "dataTem.txt", matriculaS, notasS[3];
    short int op, op2, op3, fim = 0, matricula, cont, cont2, cont3, linhaAtual;
    bool removido = false, flag, nAchei;
    float notas[3],nota;
    tAlunos alunos[tam];

    do{ cout << "\n--------------------------------"; 
        cout << "\n\t  MENU PRIMARIO";
        cout << "\n--------------------------------"; 
        cout << "\n\n1-Cadastrar alunos";
        cout << "\n2-Remover alunos";
        cout << "\n3-Listar alunos";
        cout << "\n4-Alterar dados";
        cout << "\n5-Sair\nopcao:";
        cin >> op;
        cout << "\e[H\e[2J";//limpando tela
        switch(op){
            case 1: cout << "\n--------------------------------";                 
                    cout << "\n\t  CADASTRO";
                    cout << "\n--------------------------------";                   
                    matricula = impedirMatriculasNegativas();
                    aux = to_string(matricula);//convertendo matricula para string
                    flag = verificarUnicidade(dados,aux);
                    if(flag) cout << "\nMatricula ja existente\n";
                    else{
                        cout << "\nDigite o nome do aluno: ";
                        getchar();
                        getline(cin, nome);
                        for(int j = 0; j < 3; j++){
                            do{ cout << "\nDigite a "  << j+1 << "a. nota: ";
                                cin >> notas[j];
                            }while(notas[j] > 10 || notas[j] < 0);
                        }
                        cout << "------------------------------";
                        cadastrar(dados, matricula, nome, notas); 
                        fim++;                       
                    }              
                    cout << "\n--------------------------------";
                break;
            case 2: cout << "\n--------------------------------"; 
                    arquivo.open(dados);
                    if(arquivo.is_open()){
                        removido = false;
                        cout << "\n--------------------------------";
                        matricula = impedirMatriculasNegativas();
                        aux = to_string(matricula);
                        cont3 = 0;//vai armazenar a posição da linha para remover
                        while(getline(arquivo,linha)){ 
                            if(!removido){
                                cont2 = 0;
                                while(linha[cont2] != ','){
                                    linhaAux += linha[cont2];
                                    cont2++;
                                    cont3++;
                                }
                            }
                            if (linhaAux == aux){
                                removido = true;
                            } 
                            linhaAux = ""; 
                        }
                        arquivo.close();
                        remover(dados, dadosTem, cont3);
                        if(removido) cout << "\nAluno removido com sucesso!!\n";
                        else cout << "\nMatricula nao encontrada no sistema!\n";                
                    }else cout << "\n\nLista de alunos vazia!\n";
                    cout << "\n--------------------------------"; 
                break;
            case 3: flag = true;
                    cout << "\n--------------------------------"; 
                    arquivo.open(dados,  ios::in);
                    cont = 0;
                    if(arquivo.is_open()){
                        cout << "\n\t  RELATORIO";
                        cout << "\n--------------------------------"; 
                        while(getline(arquivo,linha)){
                            flag = false;            
                            for (char ch : linha) {//pegando os dados da linha
                                if (ch != ',')  linhaAux += ch;
                                else{
                                    cont++;                         
                                    switch(cont){
                                        case 1: cout << "\nMatricula do aluno: " << linhaAux;
                                            break;
                                        case 2: cout << "\nNome do aluno: " << linhaAux;
                                            break;
                                        case 3:cout << "\nNotas: " << linhaAux;
                                            break;
                                        case 4: cout << " " << linhaAux;
                                            break;
                                        case 5: cout << " " <<linhaAux;
                                            break;
                                    }
                                    linhaAux = ""; 
                                }
                                if(cont == 5){
                                    cout << "\n------------------------------";
                                    cont = 0;
                                } 
                            }                 
                        }
                        arquivo.close();
                        if(flag) cout << "\nBanco de dados vazio!";
                    }else cout << "\n\nLista de alunos vazia!\n";
                    cout << "\n--------------------------------"; 
                break;
            case 4: cout << "\n--------------------------------";
                    arquivo.open(dados,  ios::in); 
                    if(arquivo.is_open()){ 
                        cout << "\n--------------------------------"; 
                        do{ cout << "\n\nDigite a matricula do aluno: ";
                            cin >> matricula;
                        }while(matricula < 0);
                        aux = to_string(matricula);
                        nAchei = true;
                        cont3 = 0;//vai armazenar a posição da linha para remover
                        while(getline(arquivo,linha)){ 
                            if(nAchei){
                                cont2 = 0;
                                while(linha[cont2] != ','){
                                    linhaAux += linha[cont2];
                                    cont2++;
                                    cont3++;
                                }
                            }
                            if (linhaAux == aux){
                                nAchei = false;
                            } 
                            linhaAux = ""; 
                        }
                        arquivo.close();
                        if(nAchei) cout << "\nA matricula digitada nao foi encontrada!\n";
                        else{
                            arquivo.open(dados, ios::in);
                            arquivoTem.open(dadosTem, ios::out);
                            linhaAtual = 1;
                            cont=0;
                            if(arquivo.is_open() || arquivoTem.is_open()){
                                while(getline(arquivo, linha)){
                                    if(linhaAtual != cont3){//Não armazenar a linha removida 
                                        arquivoTem << linha << "\n";
                                    }else{//alterar os dados
                                        //armazenar os dados antigos
                                        linhaAux = "";
                                        for (char ch : linha) {//pegando os dados da linha
                                            if (ch != ',')  linhaAux += ch;
                                            else{
                                                cont++;                         
                                                switch(cont){
                                                    case 1: matriculaS = linhaAux;
                                                        break;
                                                    case 2: nome = linhaAux;
                                                        break;
                                                    case 3: notasS[0] = linhaAux;
                                                        break;
                                                    case 4: notasS[1] = linhaAux;
                                                        break;
                                                    case 5:  notasS[2] = linhaAux;
                                                        break;
                                                }
                                                linhaAux = ""; 
                                            }
                                        }
                                        do{ cout << "\n--------------------------------"; 
                                            cout << "\n\t  MENU SECUNDARIO";
                                            cout << "\n--------------------------------"; 
                                            cout << "\n\n1-Alterar matricula";
                                            cout << "\n2-Alterar nome";
                                            cout << "\n3-Alterar notas";
                                            cout << "\n4-Sair\nopcao:";
                                            cin >> op2;
                                            cout << "\n\n--------------------------------";
                                            cout << "\e[H\e[2J";

                                            switch(op2){
                                                case 1: matricula = impedirMatriculasNegativas();
                                                        aux = to_string(matricula);//convertendo matricula para string
                                                        arquivo.close();
                                                        flag = verificarUnicidade(dados,aux);
                                                        if(flag) cout << "\nMatricula ja existente\n"; 
                                                        else{
                                                            matriculaS = aux;
                                                            cout << "\n\nA atualizacao dos dados foi realizada com sucesso!\n";
                                                        }
                                                    break;
                                                case 2: getchar();
                                                        cout << "\nDigite o novo nome: ";
                                                        getline(cin, nome);
                                                        cout << "\n\nA atualizacao dos dados foi realizada com sucesso!\n";
                                                        cout << "\n--------------------------------"; 
                                                    break;
                                                case 3: cout << "\n--------------------------------"; 
                                                        cout << "\n\t  MENU TERCIARIO";
                                                        cout << "\n--------------------------------"; 
                                                        cout << "\n\n1-Alterar a primeira nota";
                                                        cout << "\n2-Alterar a segunda nota";
                                                        cout << "\n3-Alterar a terceira nota";
                                                        cout << "\n4-Sair\nopcao:";
                                                        cin >> op3;
                                                        cout << "\n--------------------------------"; 
                                                        do{cout << "\nDigite a nota: ";
                                                            cin >> nota;
                                                        }while(nota < 0 || nota > 10);
                                                        switch(op3){
                                                            case 1: notasS[0] = to_string(nota);
                                                                break;
                                                            case 2: notasS[1] = to_string(nota);
                                                                break;
                                                            case 3: notasS[2] = to_string(nota);
                                                                break;
                                                            case 4: cout << "\nSaindo..."; 
                                                                break;
                                                            default: cout << "\nValor invalido, digite novamente!";                                                     
                                                        }
                                                        cout << "\n\nA atualizacao dos dados foi realizada com sucesso!\n";
                                                        cout << "\n--------------------------------"; 
                                                    break;
                                                case 4: cout << "";
                                                    break;
                                                default: cout << "\nValor invalido, digite novamente!";
                                            }
                                        }while(op2 != 4);
                                        arquivoTem <<  matriculaS;
                                        arquivoTem << ", " << nome << ", ";
                                        arquivoTem << notasS[0] << ", " << notasS[1] << ", " << notasS[2] << ",\n";
                                        arquivo.open(dados, ios::in);
                                    }
                                    linhaAtual++;
                                }
                            }
                            arquivo.close();
                            arquivoTem.close();
                            remove(dados.c_str());
                            rename(dadosTem.c_str(), dados.c_str());//aletarndo o nome do arquivo temporario
                        }
                    }else cout << "\n\nLista de alunos vazia!\n";
                    cout << "\n--------------------------------";
                break;
            case 5: cout << "\nSaindo..."; 
                break;
            default: cout << "\nValor invalido, digite novamente!";
        }
    }while(op != 5);
    cout << "\n\nFim de programa";
}
