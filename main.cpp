// Incluindo bibliotecas necess�rias para a execu��o do projeto:

#include <iostream>
#include <locale.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Defini��o da estrutura que representa um produto
struct Produto {
    string nome;
    double preco;
    int estoque;
    bool precoPorKg;
};

vector<Produto> produtos; // Vetor de produtos cadastrados

// Fun��o de chamada do menu do software
void exibirMenu();

// Fun��o utilizada para cadastrar o produto.
void cadastrarProduto();

// Fun��o utilizada para editar produtos j� cadastrados.
void editarProduto();

// Fun��o utilizada para excluir produtos j� cadastrados.
void excluirProduto();

// Fun��o utilizada para exibir produtos j� cadastrados.
void exibirProdutos();

// Salva os produtos em um arquivo CSV.
void salvarProdutosCSV();

// Permite ao usu�rio comprar um produto. Exibe os produtos e solicita o n�mero do produto e a quantidade desejada, verificando se h� estoque suficiente. Retorna o custo total da compra.
double comprarProduto();

// Finaliza a compra, mostrando o total da compra com todos os produtos escolhidos.
void finalizarCompra(double totalCompra);

// Salva o total da compra em um arquivo CSV chamado compra.csv.
void salvarCompraCSV(double totalCompra);

// Fun��o para carregar os produtos a partir do arquivo CSV
void carregarProdutosCSV() {
    ifstream arquivo("produtos.csv");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo produtos.csv para leitura.\n";
        return;
    }

    string linha;
    // Ignora o cabe�alho do CSV
    getline(arquivo, linha);

    // L� os produtos do arquivo
    while (getline(arquivo, linha)) {
        Produto produto;
        size_t pos = 0;
        // Nome do produto
        pos = linha.find(",");
        produto.nome = linha.substr(0, pos);
        linha.erase(0, pos + 1);

        // Pre�o do produto
        pos = linha.find(",");
        produto.preco = stod(linha.substr(0, pos));
        linha.erase(0, pos + 1);

        // Estoque do produto
        pos = linha.find(",");
        produto.estoque = stoi(linha.substr(0, pos));
        linha.erase(0, pos + 1);

        // Tipo de pre�o (por kg ou por unidade)
        produto.precoPorKg = (linha == "Kg");

        // Adiciona o produto ao vetor de produtos
        produtos.push_back(produto);
    }

    arquivo.close();
    //cout << "Produtos carregados de produtos.csv\n"; teste do produto
}

// Fun��o para salvar os produtos em um arquivo CSV
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
    cout << "Produtos salvos em produtos.csv\n";
}

// Fun��o para exibir o menu
void exibirMenu() {
    cout << "******| Quintandinha Ma�� Amarela |****** \n";
    cout << "Digite a op��o desejada:\n";
    cout << "1. Acessar modo administrador\n";
    cout << "2. Comprar produto\n";
    cout << "3. Finalizar compra\n";
    cout << "4. Cancelar compra\n";
    cout << "*\n";
    cout << "Op��o:";
}

// Fun��o para verificar a senha de administrador
bool verificarAdministrador() {
    string senha;
    cout << "Digite a senha de administrador: ";
    cin >> senha;
    return senha == "123"; // senha do administrador
}

// Fun��o para o modo administrador
void modoAdministrador() {
    carregarProdutosCSV();

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

// Fun��o para cadastrar um produto
void cadastrarProduto() {
    Produto produto;
    int tipoPreco;
    cout << "Digite o nome do produto: ";
    cin.ignore(); // Limpa o buffer antes de usar getline
    getline(cin, produto.nome);
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

// Fun��o para editar um produto
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

    int opcaoAlterar;
    cout << "Deseja alterar o nome? (1 - Sim, 2 - N�o): ";
    cin >> opcaoAlterar;
    if (opcaoAlterar == 1) {
        cout << "Digite o novo nome do produto (atual: " << produto.nome << "): ";
        cin.ignore(); // Limpa o buffer antes de usar getline
        getline(cin, produto.nome);
    }

    cout << "Deseja alterar o pre�o? (1 - Sim, 2 - N�o): ";
    cin >> opcaoAlterar;
    if (opcaoAlterar == 1) {
        cout << "Digite o novo pre�o do produto (atual: R$" << produto.preco << "): ";
        cin >> produto.preco;
    }

    cout << "Deseja alterar o estoque? (1 - Sim, 2 - N�o): ";
    cin >> opcaoAlterar;
    if (opcaoAlterar == 1) {
        cout << "Digite a nova quantidade em estoque (atual: " << produto.estoque << "): ";
        cin >> produto.estoque;
    }

    cout << "Produto editado com sucesso!\n";
}

// Fun��o para excluir um produto
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

// Fun��o para exibir os produtos cadastrados
void exibirProdutos() {
    cout << "Produtos cadastrados:\n";
    for (size_t i = 0; i < produtos.size(); ++i) {
        const Produto& produto = produtos[i];
        cout << i + 1 << ". " << produto.nome << " - R$" << produto.preco << " - Estoque: " << produto.estoque << " - "
             << (produto.precoPorKg ? "Por kg" : "Por unidade") << endl;
    }
}

// Fun��o para comprar um produto
double comprarProduto(double& totalCompra) {
    exibirProdutos();
    int opcaoProduto, quantidade;

    cout << "Digite o n�mero do produto que deseja comprar: ";
    cin >> opcaoProduto;

    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto inv�lido!\n";
        return 0.0;
    }

    Produto& produto = produtos[opcaoProduto - 1];
    cout << "Digite a quantidade que deseja comprar: ";
    cin >> quantidade;

    if (quantidade > produto.estoque) {
        cout << "Quantidade em estoque insuficiente!\n";
        return 0.0;
    }

    double custoProduto = produto.preco * quantidade;
    if (produto.precoPorKg) {
        cout << "Pre�o por kg. Custo total: R$" << custoProduto << endl;
    } else {
        cout << "Pre�o por unidade. Custo total: R$" << custoProduto << endl;
    }

    totalCompra += custoProduto;  // Acumulando o total da compra
    produto.estoque -= quantidade; // Atualizando o estoque
    return 0.0;  // N�o precisa retornar o valor, pois estamos acumulando em totalCompra
}

// Fun��o para finalizar a compra
// Fun��o para finalizar a compra
void finalizarCompra(double totalCompra) {
    if (totalCompra > 0) {
        cout << "Compra finalizada com sucesso! Total: R$" << totalCompra << endl;
        salvarCompraCSV(totalCompra);
        cout << "Obrigado pela compra! Volte sempre...\n";
        exit(0);  // Encerra o programa ap�s finalizar a compra
    } else {
        cout << "Nenhum produto foi comprado. A compra foi cancelada.\n";
    }
}


// Fun��o para salvar a compra em um arquivo CSV
void salvarCompraCSV(double totalCompra) {
    ofstream arquivo("compra.csv");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo compra.csv para salvar os dados.\n";
        return;
    }

    arquivo << "Total da Compra\n";
    arquivo << totalCompra << "\n";

    arquivo.close();
    //cout << "Compra salva em compra.csv\n"; teste de csv
}

// Fun��o para cancelar a compra
void cancelarCompra() {
    cout << "Compra cancelada.\n";
}

int main() {
    setlocale(LC_ALL, "");

// Carrega os produtos no in�cio do programa
    carregarProdutosCSV();

    int opcao;
    double totalCompra = 0.0;

    do {
        exibirMenu();
        cin >> opcao;

        switch (opcao) {
            case 1:
                modoAdministrador();
                break;
            case 2:
                comprarProduto(totalCompra); // Passando o totalCompra por refer�ncia
                break;
            case 3:
                finalizarCompra(totalCompra);
                break;
            case 4:
                cancelarCompra();
                break;
            default:
                cout << "Op��o inv�lida!\n";
        }
    } while (opcao != 0);

    return 0;
}
