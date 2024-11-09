<<<<<<< HEAD
// Incluindo bibliotecas necess√°rias para a execu√ß√£o do projeto:
=======
// Incluindo bibliotecas necess·rias para a execuÁ„o do projeto:
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)

#include <iostream>
#include <locale.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

<<<<<<< HEAD
struct Produto { //Defini√ß√£o da estrutura que reresenta um produto
    string nome; //Tipo de vari√°vel utilizado para nomear o produto
    double preco; //Tipo de vari√°vel utilizado para atribuir pre√ßo ao produto
    int estoque; //Tipo de vari√°vel utilizado para atribuir um n√∫mero inteiro ao estoque
    bool precoPorKg; // true = por kg, false = por unidade (utilizado booleanos para verifica√ß√£o)
};

vector<Produto> produtos; // Acessando o banco de dados com os produtos j√° cadastrados.

void exibirMenu(); // Fun√ß√£o de chamada do menu do software
void cadastrarProduto(); // Fun√ß√£o utilizada para cadastar o produto.
void editarProduto(); // Fun√ß√£o utilizada para editar produtos j√° cadastrados, solicitado o n√∫mero do produto a ser editado.
void excluirProduto(); // Fun√ß√£o utilizada para excluir produtos j√° cadastrados.
void exibirProdutos(); // Fun√ß√£o utilizada para exibir produtos j√° cadastrados.
void salvarProdutosCSV(); // Salva os produtos em um arquivo CSV (aten√ß√£o essa op√ß√£o permite vizualiza√ß√£o direta por planilhas, mas em caso de muitos dados pode apresentar uma exibi√ß√£o polu√≠da).
double comprarProduto(); // Permite ao usu√°rio comprar um produto. Exibe os produtos e solicita o n√∫mero do produto e a quantidade desejada, verificando se h√° estoque suficiente. Retorna o custo total da compra.
void finalizarCompra(double totalCompra); //Finaliza a compra, perguntando ao usu√°rio como deseja pagar (√† vista ou a prazo). Calcula o total e salva os dados da compra em um arquivo CSV.
void salvarCompraCSV(double totalCompra); //Salva o total da compra em um arquivo CSV chamado compra.csv. (gera uma nota da compra para o cliente).

bool verificarAdministrador(); // Verifica a configura√ß√£o exata para acessar o modo admistrador (Verifica a senha inserida pelo usu√°rio)
void modoAdministrador(); // Caso aprovado a fun√ß√£o de verifica√ß√£o, acessa o menu do administrador com suas respectivas fun√ß√µes.

void exibirMenu() {
    cout << "\n*****************************************\n";
    cout << "|        Quintandinha MaÔøΩÔøΩ Amarela         |\n";
    cout << "*****************************************\n";
    cout << "Digite a opÔøΩÔøΩo desejada:\n";
=======
     //DefiniÁ„o da estrutura que reresenta um produto
struct Produto {

    //Tipo de vari·vel utilizado para nomear o produto
    string nome;

    //Tipo de vari·vel utilizado para atribuir preÁo ao produto
    double preco;

    //Tipo de vari·vel utilizado para atribuir um n˙mero inteiro ao estoque
    int estoque;

    // true = por kg, false = por unidade (utilizado booleanos para verificaÁ„o)
    bool precoPorKg;
};

 // Acessando o banco de dados com os produtos j· cadastrados.
vector<Produto> produtos;

 // FunÁ„o de chamada do menu do software
void exibirMenu();

 // FunÁ„o utilizada para cadastar o produto.
void cadastrarProduto();

// FunÁ„o utilizada para editar produtos j· cadastrados, solicitado o n˙mero do produto a ser editado.
void editarProduto();

// FunÁ„o utilizada para excluir produtos j· cadastrados.
void excluirProduto();

// FunÁ„o utilizada para exibir produtos j· cadastrados.
void exibirProdutos();

 // Salva os produtos em um arquivo CSV (atenÁ„o essa opÁ„o permite vizualizaÁ„o direta por planilhas, mas em caso de muitos dados pode apresentar uma exibiÁ„o poluÌda).
void salvarProdutosCSV();

// Permite ao usu·rio comprar um produto. Exibe os produtos e solicita o n˙mero do produto e a quantidade desejada, verificando se h· estoque suficiente. Retorna o custo total da compra.
double comprarProduto();

//Finaliza a compra, perguntando ao usu·rio como deseja pagar (‡ vista ou a prazo). Calcula o total e salva os dados da compra em um arquivo CSV.
void finalizarCompra(double totalCompra);

 //Salva o total da compra em um arquivo CSV chamado compra.csv. (gera uma nota da compra para o cliente).
void salvarCompraCSV(double totalCompra);

 // Verifica a configuraÁ„o exata para acessar o modo admistrador (Verifica a senha inserida pelo usu·rio)
bool verificarAdministrador();

 // Caso aprovado a funÁ„o de verificaÁ„o, acessa o menu do administrador com suas respectivas funÁıes.
void modoAdministrador();

// exibir menu usado para o menu de opÁıes
void exibirMenu() {
    cout << "\n*****************************************\n";
    cout << "|        Quintandinha MaÁ„ Amarela         |\n";
    cout << "*****************************************\n";
    cout << "Digite a opÁ„o desejada:\n";
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
    cout << "1. Acessar modo administrador\n";
    cout << "2. Comprar produto\n";
    cout << "3. Finalizar compra\n";
    cout << "4. Cancelar compra\n";
    cout << "*****************************************\n";
<<<<<<< HEAD
    cout << "OpÔøΩÔøΩo:";
}

=======
    cout << "OpÁ„o:";
}

// verificasor de usu·rio administrador
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
bool verificarAdministrador() {
    string senha;
    cout << "Digite a senha de administrador: ";
    cin >> senha;
<<<<<<< HEAD
    return senha == "admin123"; // senha do admin
}

=======
    return senha == "admin123"; // <---- senha do administrador!
}

// opÁıes do modo de administrador
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
void modoAdministrador() {
    if (!verificarAdministrador()) {
        cout << "Acesso negado. Senha incorreta.\n";
        return;
    }

    int opcAdmin;
    do {
        cout << "\n--- Modo Administrador ---\n";
        cout << "1. Cadastrar produto\n";
        cout << "2. Editar produto\n";
        cout << "3. Excluir produto\n";
        cout << "4. Exibir produtos\n";
        cout << "5. Voltar ao menu principal\n";
<<<<<<< HEAD
        cout << "OpÔøΩÔøΩo: ";
        cin >> opcAdmin;

=======
        cout << "OpÁ„o: ";
        cin >> opcAdmin;

// usado para menu de opÁıes switch case
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
        switch (opcAdmin) {
            case 1:
                cadastrarProduto();
                salvarProdutosCSV();
                break;
            case 2:
                editarProduto();
                salvarProdutosCSV();
                break;
            case 3:
                excluirProduto();
                salvarProdutosCSV();
                break;
            case 4:
                exibirProdutos();
                break;
            case 5:
                cout << "Voltando ao menu principal...\n";
                break;
            default:
<<<<<<< HEAD
                cout << "OpÔøΩÔøΩo invÔøΩlida!\n";
=======
                cout << "OpÁ„o inv·lida!\n";
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
        }
    } while (opcAdmin != 5);
}

<<<<<<< HEAD
=======
// acesso ao painel cadastrar os produtos
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
void cadastrarProduto() {
    Produto produto;
    int tipoPreco;
    cout << "Digite o nome do produto: ";
<<<<<<< HEAD
    cin.ignore(); // Limpa o buffer antes de usar getline
    getline(cin, produto.nome); // permitir espaÔøΩos no nome do produto
    cout << "Digite o tipo de preÔøΩo: \n1. Por kg\n2. Por unidade\n";
    cin >> tipoPreco;
    produto.precoPorKg = (tipoPreco == 1);

    cout << "Digite o preÔøΩo do produto: ";
=======
    cin.ignore(); // <--- Limpa o buffer antes de usar getline
    getline(cin, produto.nome); // <---- permitir espaÁos no nome do produto
    cout << "Digite o tipo de preÁo: \n1. Por kg\n2. Por unidade\n";
    cin >> tipoPreco;
    produto.precoPorKg = (tipoPreco == 1);

    cout << "Digite o preÁo do produto: ";
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
    cin >> produto.preco;
    cout << "Digite a quantidade em estoque: ";
    cin >> produto.estoque;

    produtos.push_back(produto);
    cout << "Produto cadastrado com sucesso!\n";
}

<<<<<<< HEAD
void editarProduto() {
    exibirProdutos();
    int opcaoProduto;
    cout << "Digite o nÔøΩmero do produto que deseja editar: ";
    cin >> opcaoProduto;

    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto invÔøΩlido!\n";
=======

// menu de alterar o produto j· cadastrado
void editarProduto() {
    exibirProdutos();
    int opcaoProduto;
    cout << "Digite o n˙mero do produto que deseja editar: ";
    cin >> opcaoProduto;

    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto inv·lido!\n";
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
        return;
    }

    Produto& produto = produtos[opcaoProduto - 1];
    cout << "Digite o novo nome do produto (atual: " << produto.nome << "): ";
<<<<<<< HEAD
    cin.ignore(); // Limpa o buffer antes de usar getline
    getline(cin, produto.nome);

    cout << "Digite o novo preÔøΩo do produto (atual: R$" << produto.preco << "): ";
=======
    cin.ignore(); // <---- Limpa o buffer antes de usar getline
    getline(cin, produto.nome);

    cout << "Digite o novo preÁo do produto (atual: R$" << produto.preco << "): ";
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
    cin >> produto.preco;

    cout << "Digite a nova quantidade em estoque (atual: " << produto.estoque << "): ";
    cin >> produto.estoque;

    int tipoPreco;
<<<<<<< HEAD
    cout << "Digite o tipo de preÔøΩo (atual: " << (produto.precoPorKg ? "por kg" : "por unidade") << "): \n1. Por kg\n2. Por unidade\n";
=======
    cout << "Digite o tipo de preÁo (atual: " << (produto.precoPorKg ? "por kg" : "por unidade") << "): \n1. Por kg\n2. Por unidade\n";
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
    cin >> tipoPreco;
    produto.precoPorKg = (tipoPreco == 1);

    cout << "Produto editado com sucesso!\n";
}

<<<<<<< HEAD
void excluirProduto() {
    exibirProdutos();
    int opcaoProduto;
    cout << "Digite o nÔøΩmero do produto que deseja excluir: ";
    cin >> opcaoProduto;

    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto invÔøΩlido!\n";
=======
// menu de "deletar"/ excluir um produto j· cadastrado
void excluirProduto() {
    exibirProdutos();
    int opcaoProduto;
    cout << "Digite o n˙mero do produto que deseja excluir: ";
    cin >> opcaoProduto;

    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto inv·lido!\n";
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
        return;
    }

    produtos.erase(produtos.begin() + opcaoProduto - 1);
<<<<<<< HEAD
    cout << "Produto excluÔøΩdo com sucesso!\n";
=======
    cout << "Produto excluÌdo com sucesso!\n";
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
}

void salvarProdutosCSV() {
    ofstream arquivo("produtos.csv");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo para salvar produtos.\n";
        return;
    }

    arquivo << "Nome,Preco,Estoque,PrecoPorKg\n";
    for (const auto& produto : produtos) {
        arquivo << produto.nome << "," << produto.preco << "," << produto.estoque << "," << (produto.precoPorKg ? "Kg" : "Unidade") << "\n";
    }

    arquivo.close();
<<<<<<< HEAD
    cout << "Produtos salvos em produtos.csv\n";
}

void exibirProdutos() {
    cout << "Produtos disponÔøΩveis:\n";
    for (size_t i = 0; i < produtos.size(); ++i) {
        cout << i + 1 << ". " << produtos[i].nome << " - PreÔøΩo: R$" << produtos[i].preco
=======
    //cout << "Produtos salvos em produtos.csv\n"; -  teste para verificar se estava salvando
}

// menu de exibiÁ„o dos produtos j· cadastrados
void exibirProdutos() {
    cout << "Produtos disponÌveis:\n";
    for (size_t i = 0; i < produtos.size(); ++i) {
        cout << i + 1 << ". " << produtos[i].nome << " - PreÁo: R$" << produtos[i].preco
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
             << (produtos[i].precoPorKg ? " por Kg" : " por unidade")
             << " - Estoque: " << produtos[i].estoque << "\n";
    }
}

<<<<<<< HEAD
double comprarProduto() {
    exibirProdutos();
    int opcaoProduto, quantidade;
    cout << "Digite o nÔøΩmero do produto que deseja comprar: ";
    cin >> opcaoProduto;
    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto invÔøΩlido!\n";
=======
//mostrar resumo da compra com nome e estoque
void mostrarResumoCompra(const vector<Produto>& produtosComprados) {
    cout << "Resumo da Compra:\n";
    for (const auto& produto : produtosComprados) {
        cout << produto.nome << " - " << produto.estoque << " unidades\n";
    }
}


double comprarProduto(vector<Produto>& produtosComprados) {
    exibirProdutos();
    int opcaoProduto, quantidade;
    cout << "Digite o n˙mero do produto que deseja comprar: ";
    cin >> opcaoProduto;
    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto inv·lido!\n";
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
        return 0;
    }
    Produto& produtoEscolhido = produtos[opcaoProduto - 1];

    cout << "Digite a quantidade desejada" << (produtoEscolhido.precoPorKg ? " em Kg: " : " em unidades: ");
    cin >> quantidade;

    if (quantidade > produtoEscolhido.estoque) {
        cout << "Quantidade em estoque insuficiente!\n";
        return 0;
    }

    produtoEscolhido.estoque -= quantidade;
    double custoTotal = quantidade * produtoEscolhido.preco;
    cout << "Total parcial: R$ " << custoTotal << "\n";

<<<<<<< HEAD
=======
    // Adicionando o produto comprado ao vetor
    Produto produtoComprado = produtoEscolhido;
    produtoComprado.estoque = quantidade; // Atualiza o estoque com a quantidade comprada
    produtosComprados.push_back(produtoComprado);

>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
    salvarProdutosCSV();
    return custoTotal;
}

<<<<<<< HEAD
void finalizarCompra(double totalCompra) {
    if (totalCompra == 0) {
        cout << "Nenhum produto foi comprado.\n";
        return;
    }
    int opcPgto;
    cout << "Total da compra: R$" << totalCompra << "\n";
    cout << "Digite a opÔøΩÔøΩo de pagamento:\n";
    cout << "1. Pagamento ÔøΩ vista (15% de desconto)\n";
    cout << "2. Pagamento ÔøΩ prazo\n";
    cout << "*******************************\n";
    cout << "OpÔøΩÔøΩo:";
=======

// menu de finalizaÁ„o de compra / j· com o CSV para obter dados de compra concluÌda
void finalizarCompra(double totalCompra) {
    if (totalCompra <= 0) {  // Verifica se a compra n„o tem valor positivo
        cout << "Erro: Nenhum produto foi comprado. A compra n„o pode ser finalizada.\n";
        return;  // Retorna sem fazer nada se a compra for inv·lida
    }

    int opcPgto;
    cout << "Total da compra: R$" << totalCompra << "\n";
    cout << "Digite a opÁ„o de pagamento:\n";
    cout << "1. Pagamento ‡ vista (15% de desconto)\n";
    cout << "2. Pagamento a prazo\n";
    cout << "*******************************\n";
    cout << "OpÁ„o: ";
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
    cin >> opcPgto;

    switch (opcPgto) {
        case 1:
            totalCompra *= 0.85;
<<<<<<< HEAD
            cout << "Total ÔøΩ vista: R$ " << totalCompra << "\n";
            break;
        case 2: {
            int numParcelas;
            cout << "NÔøΩmero de parcelas:";
            cin >> numParcelas;
            cout << "Total ÔøΩ prazo: " << numParcelas << " x de R$ " << (totalCompra / numParcelas) << "\n";
            break;
        }
        default:
            cout << "OpÔøΩÔøΩo invÔøΩlida!\n";
=======
            cout << "Total ‡ vista: R$ " << totalCompra << "\n";
            break;
        case 2: {
            int numParcelas;
            cout << "N˙mero de parcelas: ";
            cin >> numParcelas;
            cout << "Total a prazo: " << numParcelas << " x de R$ " << (totalCompra / numParcelas) << "\n";
            break;
        }
        default:
            cout << "OpÁ„o inv·lida!\n";
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
            return;
    }

    salvarCompraCSV(totalCompra);
<<<<<<< HEAD
    //cout << "Compra finalizada e salva no arquivo CSV!\n"; // eu tava usando para testar se deu certo o codigo
}

=======
    cout << "Compra finalizada !\n";
}

// salva as comprar com opÁ„o de caso o arquivo de csv der erro exibir mensagem de erro.
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
void salvarCompraCSV(double totalCompra) {
    ofstream arquivo("compra.csv");

    if (!arquivo.is_open()) {
<<<<<<< HEAD
        cout << "Erro ao abrir o arquivo para salvar compra.\n";
=======
        cout << "Erro ao tentar salvar compra.\n";
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
        return;
    }

    arquivo << "Total da Compra\n";
    arquivo << totalCompra << "\n";

    arquivo.close();
    //cout << "Compra salva em compra.csv\n"; // eu tava usando para testar se deu certo o codigo
}

<<<<<<< HEAD
=======
// estrutura principal
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
int main() {
    setlocale(LC_ALL, "");

    int opc;
    double totalCompra = 0;
<<<<<<< HEAD
=======
    vector<Produto> produtosComprados; // Vetor para armazenar os produtos comprados
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)

    do {
        exibirMenu();
        cin >> opc;

        switch (opc) {
            case 1:
<<<<<<< HEAD
                modoAdministrador(); // Executa o modo administrador se a senha estiver correta
                break;
            case 2:
                totalCompra += comprarProduto();
                break;
            case 3:
                finalizarCompra(totalCompra);
                opc = 4; // Sair apÔøΩs finalizar a compra
=======
                modoAdministrador(); // <--- Executa o modo administrador se a senha estiver correta
                break;
            case 2:
                totalCompra += comprarProduto(produtosComprados); // Passa o vetor de produtos comprados
                break;
            case 3:
                finalizarCompra(totalCompra);
                // Exibe o resumo da compra
                mostrarResumoCompra(produtosComprados); // Mostra o resumo antes de finalizar a compra
                opc = 4; // <--- Sair apÛs finalizar a compra
>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
                break;
            case 4:
                cout << "Compra cancelada\n";
                break;
            default:
<<<<<<< HEAD
                cout << "OpÔøΩÔøΩo invÔøΩlida!\n";
        }
    } while (opc != 4);

    cout << "Obrigado e Volte Sempre..." << endl;
    return 0;
}
=======
                cout << "OpÁ„o inv·lida!\n";
        }
    } while (opc != 4);

    cout << "Obrigado e Volte Sempre..." << endl; // <-- finaliza o programa
    return 0;
}

>>>>>>> 7f9e981 (Atualizando coment√°rios, e corrigindo problemas no c√≥digo do PIM)
