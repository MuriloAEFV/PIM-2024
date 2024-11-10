#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <locale.h>

using namespace std;

struct Produto {
    string nome;
    double preco;
    int estoque;
    bool precoPorKg;
};

vector<Produto> produtos;

// Fun��es declaradas
void exibirMenuAdministrador();
void cadastrarProduto();
void editarProduto();
void excluirProduto();
void exibirProdutos();
void salvarProdutosCSV();
void carregarProdutosCSV();
bool verificarAdministrador();

bool verificarAdministrador() {
    string senha;
    cout << "Digite a senha de administrador: ";
    cin >> senha;
    return senha == "123"; // Senha do administrador
}

void modoAdministrador() {
    // Carregar os produtos ao iniciar
    carregarProdutosCSV();

    if (!verificarAdministrador()) {
        cout << "Acesso negado. Senha incorreta.\n";
        return;
    }

    int opcAdmin;
    do {
        exibirMenuAdministrador();
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

void exibirMenuAdministrador() {
    cout << "\n--- Modo Administrador ---\n";
    cout << "1. Cadastrar produto\n";
    cout << "2. Editar produto\n";
    cout << "3. Excluir produto\n";
    cout << "4. Exibir produtos\n";
    cout << "5. Sair\n";
    cout << "Op��o: ";
}

void cadastrarProduto() {
    Produto produto;
    int tipoPreco;
    cout << "Digite o nome do produto: ";
    cin.ignore();
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
    cin.ignore();
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

void exibirProdutos() {
    cout << "Produtos dispon�veis:\n";
    for (size_t i = 0; i < produtos.size(); ++i) {
        cout << i + 1 << ". " << produtos[i].nome << " - Pre�o: R$" << produtos[i].preco
             << (produtos[i].precoPorKg ? " por Kg" : " por unidade")
             << " - Estoque: " << produtos[i].estoque << "\n";
    }
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
    cout << "Produtos salvos em produtos.csv\n";
}

// Fun��o para carregar os produtos do arquivo CSV
void carregarProdutosCSV() {
    ifstream arquivo("produtos.csv");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo CSV.\n";
        return;
    }

    string linha;
    getline(arquivo, linha); // Ignora o cabe�alho

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        Produto produto;
        string precoPorKg;

        getline(ss, produto.nome, ',');
        ss >> produto.preco;
        ss.ignore(1, ',');
        ss >> produto.estoque;
        ss.ignore(1, ',');
        getline(ss, precoPorKg);

        produto.precoPorKg = (precoPorKg == "Kg");

        produtos.push_back(produto);
    }

    arquivo.close();
}

int main() {

    setlocale(LC_ALL, " ");

    modoAdministrador();
    return 0;
}
