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
    fstream arquivo;
    string nom, linha;
    string aux;
    short int cont = 0;
    float notas[3];
    short int op, i = 0, op2, op3;
    short int matricula;
    bool removido = false, flag, nAchei;
    float nota;
    tAlunos alunos[tam];
    do{ cout << "\n------------------------------"; 
        cout << "\n\tMENU PRIMARIO";
        cout << "\n------------------------------";
        cout << "\n1-Cadastrar alunos";
        cout << "\n2-Remover alunos";
        cout << "\n3-Relatorio";
        cout << "\n4-Alterar dados";
        cout << "\n5-Sair\nopcao:";
        cin >> op;
        switch(op){
            case 1: if(i < tam){
                        cout << "\n------------------------------";
                        cout << "\n\tCADASTRO";
                        cout << "\n------------------------------";
                    //salvando no txt
                    arquivo.open("date.txt");
                    do{ 
                        do{ cout << "\nDigite a matricula do aluno: ";
                            cin >> matricula;
                        }while(matricula < 0);//impedir matriculas negativas
                        flag =  false;
                        cont = 0;
                        aux = to_string(matricula);
                        while(getline(arquivo,linha)){
                            if(cont == 0){
                                cout << linha << "\n" << aux << "\n\n";
                                if (linha == aux) flag = true;
                            }
                            cont++;
                            if(cont == 5) cont = 0;

                        }
                        if(flag) cout << "\nMatricula ja existente, digite novamente!\n";
                    }while(flag);//impedir matriculas iguais
                    arquivo.close();
                    cout << "\nDigite o nome do aluno: ";
                    getchar();
                    getline(cin, nom);
                    for(int j = 0; j < 3; j++){
                        do{ cout << "\nDigite a "  << j+1 << "a. nota: ";
                            cin >> notas[j];
                        }while(notas[j] > 10 || notas[j] < 0);
                    }
                    cout << "------------------------------";
                    i++;
                    arquivo.open("date.txt",  ios::app);
                    arquivo << matricula;
                    arquivo << "\n" << nom << "\n";
                    arquivo << notas[0] << "\n" << notas[1] << "\n" << notas[2] << "\n";
                    arquivo.close();
                    }else{
                        cout << "\nCadastro cheio!";
                    }
                break;
            case 2: if(i > 0){
                        removido = false;
                        cout << "\n------------------------------";
                        cout << "\n\nDigite a matricula do aluno: ";
                        cin >> matricula;
                        for(int j = 0; j < i; j++){
                            flag = false;
                            if(matricula == alunos[j].matricula){
                                alunos[j].matricula = -1;
                                removido = true;
                                flag = true;
                            }
                            if((removido) && (j < i-1)){
                                alunos[j].matricula = alunos[j+1].matricula;
                                alunos[j].nome = alunos[j+1].nome;
                                if(flag) alunos[j+1].matricula = -1;
                            }

                        }
                        if(removido){
                            i--;
                            cout << "\nRemocao realizada com sucesso!!\n";
                        } 
                        else  cout << "\nMatricula nao  encontrada!\n";
                        cout << "\n------------------------------";
                }else cout << "\nNenhum aluno cadastrado no momento!\n";
                break;
            case 3: flag = true;
                    arquivo.open("date.txt",  ios::in);
                    if(arquivo.is_open()){
                        cout << "\n------------------------------";
                        cout << "\n\tRELATORIO";
                        cout << "\n------------------------------";
                        while(getline(arquivo,linha)){
                            flag = false;
                            cont++;
                            switch(cont){
                                case 1: cout << "\nMatricula do aluno: " << linha;
                                    break;
                                case 2: cout << "\n\nNome do aluno: " << linha;
                                    break;
                                case 3:cout << "\n\nNotas: " << linha;
                                    break;
                                case 4: cout << " " << linha;
                                    break;
                                case 5: cout << " " <<linha;
                                    break;
                            }
                            if(cont == 5){
                                cout << "\n------------------------------";
                                cont = 0;
                            } 
                        }
                        arquivo.close();
                        if(flag) cout << "\nBanco de dados vazio!";
                    }
                break;
            case 4: if(i > 0){
                        cout << "\n------------------------------";
                        cout << "\n\nDigite a matricula do aluno: ";
                        cin >> matricula;
                        nAchei = true;
                        for(int j = 0; j < i; j++){
                            if(matricula == alunos[j].matricula){
                                nAchei = false;
                                do{
                                    cout << "\n------------------------------"; 
                                    cout << "\n\tMENU SECUNDARIO";
                                    cout << "\n------------------------------";
                                    cout << "\n1-Alterar matricula";
                                    cout << "\n2-Alterar nome";
                                    cout << "\n3-Alterar notas";
                                    cout << "\n4-Sair\nopcao:";
                                    cin >> op2;
                                    cout << "\n\n--------------------------------";
                                    switch(op2){
                                        case 1: do{
                                                    do{ cout << "\nDigite  nova a matricula do aluno: ";
                                                        cin >> matricula;
                                                    }while(matricula < 0); //impedir matriculas negativas
                                                    flag =  false;
                                                    for(int j = 0; j < i; j++){
                                                        if(alunos[j].matricula == matricula) flag = true;
                                                    }
                                                    if(flag) cout << "\nMatricula ja existente, digite novamente!\n";
                                                    else alunos[i].matricula = matricula;
                                                }while(flag);//impedir matriculas iguais
                                            break;
                                        case 2: getchar();
                                                cout << "\nDigite o novo nome do aluno: ";
                                                getline(cin, alunos[j].nome);
                                            break;
                                        case 3: cout << "\n------------------------------";
                                                cout << "\n\tMENU TERCIARIO";
                                                cout << "\n------------------------------";
                                                cout << "\n1-Alterar a primeira nota";
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
                                            break;
                                        case 4: cout << "\n\nSaindo...";
                                            break;
                                        default: cout << "\nValor invalido, digite novamente!";
                                    }
                                }while(op2 != 4);
                            }
                        }
                        if(nAchei) cout << "\n\nMatricula nao encontrada!\n";
                        else cout << "\n\nAtualizacao realizada com sucesso!\n";
                    }else cout << "\nNenhum aluno cadastrado no momento!\n";
                break;
            case 5: cout << "\nSaindo..."; 
                break;
            default: cout << "\nValor invalido, digite novamente!";
        }
    }while(op != 5);
    cout << "\n\nFim de programa";
}
