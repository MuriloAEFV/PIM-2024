// Incluindo bibliotecas necess�rias para a execu��o do projeto:

#include <iostream>
#include <locale.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

     //Defini��o da estrutura que reresenta um produto
struct Produto {

    //Tipo de vari�vel utilizado para nomear o produto
    string nome;

    //Tipo de vari�vel utilizado para atribuir pre�o ao produto
    double preco;

    //Tipo de vari�vel utilizado para atribuir um n�mero inteiro ao estoque
    int estoque;

    // true = por kg, false = por unidade (utilizado booleanos para verifica��o)
    bool precoPorKg;
};

 // Acessando o banco de dados com os produtos j� cadastrados.
vector<Produto> produtos;

 // Fun��o de chamada do menu do software
void exibirMenu();

 // Fun��o utilizada para cadastar o produto.
void cadastrarProduto();

// Fun��o utilizada para editar produtos j� cadastrados, solicitado o n�mero do produto a ser editado.
void editarProduto();

// Fun��o utilizada para excluir produtos j� cadastrados.
void excluirProduto();

// Fun��o utilizada para exibir produtos j� cadastrados.
void exibirProdutos();

 // Salva os produtos em um arquivo CSV (aten��o essa op��o permite vizualiza��o direta por planilhas, mas em caso de muitos dados pode apresentar uma exibi��o polu�da).
void salvarProdutosCSV();

// Permite ao usu�rio comprar um produto. Exibe os produtos e solicita o n�mero do produto e a quantidade desejada, verificando se h� estoque suficiente. Retorna o custo total da compra.
double comprarProduto();

//Finaliza a compra, perguntando ao usu�rio como deseja pagar (� vista ou a prazo). Calcula o total e salva os dados da compra em um arquivo CSV.
void finalizarCompra(double totalCompra);

 //Salva o total da compra em um arquivo CSV chamado compra.csv. (gera uma nota da compra para o cliente).
void salvarCompraCSV(double totalCompra);

 // Verifica a configura��o exata para acessar o modo admistrador (Verifica a senha inserida pelo usu�rio)
bool verificarAdministrador();

 // Caso aprovado a fun��o de verifica��o, acessa o menu do administrador com suas respectivas fun��es.
void modoAdministrador();

// exibir menu usado para o menu de op��es
void exibirMenu() {
    cout << "\n*****************************************\n";
    cout << "|        Quintandinha Ma�� Amarela         |\n";
    cout << "*****************************************\n";
    cout << "Digite a op��o desejada:\n";
    cout << "1. Acessar modo administrador\n";
    cout << "2. Comprar produto\n";
    cout << "3. Finalizar compra\n";
    cout << "4. Cancelar compra\n";
    cout << "*****************************************\n";
    cout << "Op��o:";
}

// verificasor de usu�rio administrador
bool verificarAdministrador() {
    string senha;
    cout << "Digite a senha de administrador: ";
    cin >> senha;
    return senha == "admin123"; // <---- senha do administrador!
}

// op��es do modo de administrador
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
        cout << "Op��o: ";
        cin >> opcAdmin;

// usado para menu de op��es switch case
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
                cout << "Op��o inv�lida!\n";
        }
    } while (opcAdmin != 5);
}

// acesso ao painel cadastrar os produtos
void cadastrarProduto() {
    Produto produto;
    int tipoPreco;
    cout << "Digite o nome do produto: ";
    cin.ignore(); // <--- Limpa o buffer antes de usar getline
    getline(cin, produto.nome); // <---- permitir espa�os no nome do produto
    cout << "Digite o tipo de pre�o: \n1. Por kg\n2. Por unidade\n";
    cin >> tipoPreco;
    produto.precoPorKg = (tipoPreco == 1);

    cout << "Digite o pre�o do produto: ";
    cin >> produto.preco;
    cout << "Digite a quantidade em estoque: ";
    cin >> produto.estoque;

    produtos.push_back(produto);
    cout << "Produto cadastrado com sucesso!\n";
}


// menu de alterar o produto j� cadastrado
void editarProduto() {
    exibirProdutos();
    int opcaoProduto;
    cout << "Digite o n�mero do produto que deseja editar: ";
    cin >> opcaoProduto;

    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto inv�lido!\n";
        return;
    }

    Produto& produto = produtos[opcaoProduto - 1];
    cout << "Digite o novo nome do produto (atual: " << produto.nome << "): ";
    cin.ignore(); // <---- Limpa o buffer antes de usar getline
    getline(cin, produto.nome);

    cout << "Digite o novo pre�o do produto (atual: R$" << produto.preco << "): ";
    cin >> produto.preco;

    cout << "Digite a nova quantidade em estoque (atual: " << produto.estoque << "): ";
    cin >> produto.estoque;

    int tipoPreco;
    cout << "Digite o tipo de pre�o (atual: " << (produto.precoPorKg ? "por kg" : "por unidade") << "): \n1. Por kg\n2. Por unidade\n";
    cin >> tipoPreco;
    produto.precoPorKg = (tipoPreco == 1);

    cout << "Produto editado com sucesso!\n";
}

// menu de "deletar"/ excluir um produto j� cadastrado
void excluirProduto() {
    exibirProdutos();
    int opcaoProduto;
    cout << "Digite o n�mero do produto que deseja excluir: ";
    cin >> opcaoProduto;

    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto inv�lido!\n";
        return;
    }

    produtos.erase(produtos.begin() + opcaoProduto - 1);
    cout << "Produto exclu�do com sucesso!\n";
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
    //cout << "Produtos salvos em produtos.csv\n"; -  teste para verificar se estava salvando
}

// menu de exibi��o dos produtos j� cadastrados
void exibirProdutos() {
    cout << "Produtos dispon�veis:\n";
    for (size_t i = 0; i < produtos.size(); ++i) {
        cout << i + 1 << ". " << produtos[i].nome << " - Pre�o: R$" << produtos[i].preco
             << (produtos[i].precoPorKg ? " por Kg" : " por unidade")
             << " - Estoque: " << produtos[i].estoque << "\n";
    }
}

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
    cout << "Digite o n�mero do produto que deseja comprar: ";
    cin >> opcaoProduto;
    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto inv�lido!\n";
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

    // Adicionando o produto comprado ao vetor
    Produto produtoComprado = produtoEscolhido;
    produtoComprado.estoque = quantidade; // Atualiza o estoque com a quantidade comprada
    produtosComprados.push_back(produtoComprado);

    salvarProdutosCSV();
    return custoTotal;
}


// menu de finaliza��o de compra / j� com o CSV para obter dados de compra conclu�da
void finalizarCompra(double totalCompra) {
    if (totalCompra <= 0) {  // Verifica se a compra n�o tem valor positivo
        cout << "Erro: Nenhum produto foi comprado. A compra n�o pode ser finalizada.\n";
        return;  // Retorna sem fazer nada se a compra for inv�lida
    }

    int opcPgto;
    cout << "Total da compra: R$" << totalCompra << "\n";
    cout << "Digite a op��o de pagamento:\n";
    cout << "1. Pagamento � vista (15% de desconto)\n";
    cout << "2. Pagamento a prazo\n";
    cout << "*******************************\n";
    cout << "Op��o: ";
    cin >> opcPgto;

    switch (opcPgto) {
        case 1:
            totalCompra *= 0.85;
            cout << "Total � vista: R$ " << totalCompra << "\n";
            break;
        case 2: {
            int numParcelas;
            cout << "N�mero de parcelas: ";
            cin >> numParcelas;
            cout << "Total a prazo: " << numParcelas << " x de R$ " << (totalCompra / numParcelas) << "\n";
            break;
        }
        default:
            cout << "Op��o inv�lida!\n";
            return;
    }

    salvarCompraCSV(totalCompra);
    cout << "Compra finalizada !\n";
}

// salva as comprar com op��o de caso o arquivo de csv der erro exibir mensagem de erro.
void salvarCompraCSV(double totalCompra) {
    ofstream arquivo("compra.csv");

    if (!arquivo.is_open()) {
        cout << "Erro ao tentar salvar compra.\n";
        return;
    }

    arquivo << "Total da Compra\n";
    arquivo << totalCompra << "\n";

    arquivo.close();
    //cout << "Compra salva em compra.csv\n"; // eu tava usando para testar se deu certo o codigo
}

// estrutura principal
int main() {
    setlocale(LC_ALL, "");

    int opc;
    double totalCompra = 0;
    vector<Produto> produtosComprados; // Vetor para armazenar os produtos comprados

    do {
        exibirMenu();
        cin >> opc;

        switch (opc) {
            case 1:
                modoAdministrador(); // <--- Executa o modo administrador se a senha estiver correta
                break;
            case 2:
                totalCompra += comprarProduto(produtosComprados); // Passa o vetor de produtos comprados
                break;
            case 3:
                finalizarCompra(totalCompra);
                // Exibe o resumo da compra
                mostrarResumoCompra(produtosComprados); // Mostra o resumo antes de finalizar a compra
                opc = 4; // <--- Sair ap�s finalizar a compra
                break;
            case 4:
                cout << "Compra cancelada\n";
                break;
            default:
                cout << "Op��o inv�lida!\n";
        }
    } while (opc != 4);

    cout << "Obrigado e Volte Sempre..." << endl; // <-- finaliza o programa
    return 0;
}

