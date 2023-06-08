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

int main(){

    fstream arquivo, arquivoTem;
    string aux, linha, nome, linhaAux, dados = "date.txt" ,dadosTem = "dataTem.txt";
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
                    do{ cout << "\nDigite a matricula do aluno: ";
                        cin >> matricula;
                    }while(matricula < 0);//impedir matriculas negativas
                    flag =  false;
                    cont = 0;
                    aux = to_string(matricula);//convertendo matricula para string
                    arquivo.open(dados); 
                    while(getline(arquivo,linha)){
                        cont2 = 0;
                        while(linha[cont2] != ','){ //pegando apenas a matricula
                            linhaAux += linha[cont2];
                            cont2++;
                        }
                        if (linhaAux == aux) flag = true;//verificando se existe a matricula
                        linhaAux = "";
                    }
                    arquivo.close();
                    if(flag) cout << "\nMatricula ja existente, digite novamente!\n";
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
                        arquivo.open(dados,  ios::app);
                        arquivo << matricula;
                        arquivo << ", " << nome << ", ";
                        arquivo << notas[0] << ", " << notas[1] << ", " << notas[2] << ",\n";
                        arquivo.close();  
                        fim++;                       
                    }              
                    cout << "\n--------------------------------";
                break;
            case 2: cout << "\n--------------------------------"; 
                    arquivo.open(dados);
                    if(arquivo.is_open()){
                        removido = false;
                        cout << "\n--------------------------------";
                        do{ cout << "\n\nDigite a matricula do aluno: ";
                            cin >> matricula;
                        }while(matricula < 0);
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
                        arquivo.open(dados, ios::in);
                        arquivoTem.open(dadosTem, ios::out);
                        linhaAtual = 1;
                        if(arquivo.is_open() || arquivoTem.is_open()){
                            while(getline(arquivo, linha)){
                                if(linhaAtual != cont3){//Não armazenar a linha removida 
                                    arquivoTem << linha << "\n";
                                }
                                linhaAtual++;
                            }
                        }
                        arquivo.close();
                        arquivoTem.close();
                        remove(dados.c_str());
                        rename(dadosTem.c_str(), dados.c_str());//aletarndo o nome do arquivo temporario
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
                    if(fim > 0){ 
                        cout << "\n--------------------------------"; 
                        cout << "\n\nDigite a matricula do aluno: ";
                        cin >> matricula;
                        nAchei = true;
                        for(int j = 0; j < fim; j++){
                            if(matricula == alunos[j].matricula){
                                nAchei = false;
                                do{
                                    cout << "\n--------------------------------"; 
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
                                        case 1: do{ cout << "\nDigite  nova a matricula do aluno: ";
                                                    cin >> matricula;
                                                }while(matricula < 0); //impedir matriculas negativas
                                                flag =  false;
                                                for(int j = 0; j < fim; j++){
                                                    if(alunos[j].matricula == matricula) flag = true;
                                                }
                                                if(flag){ 
                                                    cout << "\nEssa matricula ja existe em nosso sistema!\n";
                                                    cout << "\n--------------------------------"; 
                                                }
                                                else alunos[j].matricula = matricula;
                                            break;
                                        case 2: getchar();
                                                cout << "\nDigite o novo nome do aluno: ";
                                                getline(cin, alunos[j].nome);
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
                                                    case 1: alunos[j].notas[0] = nota;
                                                        break;
                                                    case 2: alunos[j].notas[1] = nota;
                                                        break;
                                                    case 3: alunos[j].notas[2] = nota;
                                                        break;
                                                    case 4: cout << "\nSaindo..."; 
                                                        break;
                                                    default: cout << "\nValor invalido, digite novamente!";                                                     
                                                }
                                                cout << "\n--------------------------------"; 
                                            break;
                                        case 4: cout << "\n\nSaindo...";
                                            break;
                                        default: cout << "\nValor invalido, digite novamente!";
                                    }
                                }while(op2 != 4);
                            }
                        }
                        if(nAchei) cout << "\nA matricula digitada nao foi encontrada!\n";
                        else cout << "\n\nA atualizacao dos dados foi realizada com sucesso!\n";
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
