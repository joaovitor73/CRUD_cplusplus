#include <iostream>
using std::cin;
using std::cout;
using std::string; 

struct tAlunos{
    int matricula;
    string nome;
    float notas[3];
};

const short int tam = 3;

int main(){

    short int op, op2, op3, i = 0, matricula;
    bool removido = false, flag, nAchei;
    float nota;
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
        switch(op){
            case 1: cout << "\n--------------------------------"; 
                    if(i < tam){
                        cout << "\n\t  CADASTRO";
                        cout << "\n--------------------------------"; 
                        do{ 
                            do{ cout << "\n\nDigite a matricula do aluno: ";
                                cin >> matricula;
                            }while(matricula < 0);//impedir matriculas negativas
                            flag =  false;
                            for(int j = 0; j < i; j++){
                                if(alunos[j].matricula == matricula) flag = true;
                            }
                            if(flag) cout << "\nEssa matricula ja existe em nosso sistema, digite novamente!\n";
                            else alunos[i].matricula = matricula;
                        }while(flag);//impedir matriculas iguais
                        cout << "\nDigite o nome do aluno: ";
                        getchar();
                        getline(cin, alunos[i].nome);
                        for(int j = 0; j < 3; j++){
                            do{ cout << "\nDigite a "  << j+1 << "a. nota: ";
                                cin >> alunos[i].notas[j];
                            }while(alunos[i].notas[j] > 10 || alunos[i].notas[j] < 0);
                        }
                        i++;
                    }else{
                        cout << "\n\nLista de alunos cheia!";
                    }
                    cout << "\n--------------------------------"; 
                break;
            case 2: cout << "\n--------------------------------"; 
                    if(i > 0){ 
                        removido = false;
                        cout << "\n--------------------------------"; 
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
                            cout << "\nAluno removido com sucesso!!\n";
                        } 
                        else  cout << "\n\nA matricula digitada nao foi encontrada!\n";                 
                    }else cout << "\n\nLista de alunos vazia!\n";
                    cout << "\n--------------------------------"; 
                break;
            case 3: cout << "\n--------------------------------"; 
                    if(i > 0){  
                        cout << "\n\t  RELATORIO";
                        cout << "\n--------------------------------"; 
                        for(int j = 0; j < i; j++){
                            cout << "\n\nMatricula do aluno: " << alunos[j].matricula;
                            cout << "\n\nNome do aluno: " << alunos[j].nome;
                            cout << "\n\nNotas: ";
                            for(int k = 0; k < 3; k++){
                                cout << alunos[j].notas[k] << "  ";
                            }
                        }
                    }else cout << "\n\nLista de alunos vazia!\n";
                    cout << "\n--------------------------------"; 
                break;
            case 4: cout << "\n--------------------------------"; 
                    if(i > 0){ 
                        cout << "\n--------------------------------"; 
                        cout << "\n\nDigite a matricula do aluno: ";
                        cin >> matricula;
                        nAchei = true;
                        for(int j = 0; j < i; j++){
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
                                    switch(op2){
                                        case 1: do{
                                                    do{ cout << "\nDigite  nova a matricula do aluno: ";
                                                        cin >> matricula;
                                                    }while(matricula < 0); //impedir matriculas negativas
                                                    flag =  false;
                                                    for(int j = 0; j < i; j++){
                                                        if(alunos[j].matricula == matricula) flag = true;
                                                    }
                                                    if(flag){ 
                                                        cout << "\nMatricula ja existente, digite novamente!\n";
                                                        cout << "\n--------------------------------"; 
                                                    }
                                                    else alunos[i].matricula = matricula;
                                                }while(flag);//impedir matriculas iguais
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
                        else cout << "\n\nA atualizacao de dados foi realizada com sucesso!\n";
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
