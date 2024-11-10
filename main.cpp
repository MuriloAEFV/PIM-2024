// Incluindo bibliotecas necessárias para a execução do projeto:

#include <iostream>
#include <locale.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Definição da estrutura que representa um produto
struct Produto {
    string nome;
    double preco;
    int estoque;
    bool precoPorKg;
};

vector<Produto> produtos; // Vetor de produtos cadastrados

// Função de chamada do menu do software
void exibirMenu();

// Função utilizada para cadastrar o produto.
void cadastrarProduto();

// Função utilizada para editar produtos já cadastrados.
void editarProduto();

// Função utilizada para excluir produtos já cadastrados.
void excluirProduto();

// Função utilizada para exibir produtos já cadastrados.
void exibirProdutos();

// Salva os produtos em um arquivo CSV.
void salvarProdutosCSV();

// Permite ao usuário comprar um produto. Exibe os produtos e solicita o número do produto e a quantidade desejada, verificando se há estoque suficiente. Retorna o custo total da compra.
double comprarProduto();

// Finaliza a compra, mostrando o total da compra com todos os produtos escolhidos.
void finalizarCompra(double totalCompra);

// Salva o total da compra em um arquivo CSV chamado compra.csv.
void salvarCompraCSV(double totalCompra);

// Função para carregar os produtos a partir do arquivo CSV
void carregarProdutosCSV() {
    ifstream arquivo("produtos.csv");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo produtos.csv para leitura.\n";
        return;
    }

    string linha;
    // Ignora o cabeçalho do CSV
    getline(arquivo, linha);

    // Lê os produtos do arquivo
    while (getline(arquivo, linha)) {
        Produto produto;
        size_t pos = 0;
        // Nome do produto
        pos = linha.find(",");
        produto.nome = linha.substr(0, pos);
        linha.erase(0, pos + 1);

        // Preço do produto
        pos = linha.find(",");
        produto.preco = stod(linha.substr(0, pos));
        linha.erase(0, pos + 1);

        // Estoque do produto
        pos = linha.find(",");
        produto.estoque = stoi(linha.substr(0, pos));
        linha.erase(0, pos + 1);

        // Tipo de preço (por kg ou por unidade)
        produto.precoPorKg = (linha == "Kg");

        // Adiciona o produto ao vetor de produtos
        produtos.push_back(produto);
    }

    arquivo.close();
    //cout << "Produtos carregados de produtos.csv\n"; teste do produto
}

// Função para salvar os produtos em um arquivo CSV
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

// Função para exibir o menu
void exibirMenu() {
    cout << "******| Quintandinha Maçã Amarela |****** \n";
    cout << "Digite a opção desejada:\n";
    cout << "1. Acessar modo administrador\n";
    cout << "2. Comprar produto\n";
    cout << "3. Finalizar compra\n";
    cout << "4. Cancelar compra\n";
    cout << "*\n";
    cout << "Opção:";
}

// Função para verificar a senha de administrador
bool verificarAdministrador() {
    string senha;
    cout << "Digite a senha de administrador: ";
    cin >> senha;
    return senha == "123"; // senha do administrador
}

// Função para o modo administrador
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
        cout << "Opção: ";
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
                cout << "Opção inválida!\n";
        }
    } while (opcAdmin != 5);
}

// Função para cadastrar um produto
void cadastrarProduto() {
    Produto produto;
    int tipoPreco;
    cout << "Digite o nome do produto: ";
    cin.ignore(); // Limpa o buffer antes de usar getline
    getline(cin, produto.nome);
    cout << "Digite o tipo de preço: \n1. Por kg\n2. Por unidade\n";
    cin >> tipoPreco;
    produto.precoPorKg = (tipoPreco == 1);

    cout << "Digite o preço do produto: ";
    cin >> produto.preco;
    cout << "Digite a quantidade em estoque: ";
    cin >> produto.estoque;

    produtos.push_back(produto);
    cout << "Produto cadastrado com sucesso!\n";
}

// Função para editar um produto
void editarProduto() {
    exibirProdutos();
    int opcaoProduto;
    cout << "Digite o número do produto que deseja editar: ";
    cin >> opcaoProduto;

    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto inválido!\n";
        return;
    }

    Produto& produto = produtos[opcaoProduto - 1];

    int opcaoAlterar;
    cout << "Deseja alterar o nome? (1 - Sim, 2 - Não): ";
    cin >> opcaoAlterar;
    if (opcaoAlterar == 1) {
        cout << "Digite o novo nome do produto (atual: " << produto.nome << "): ";
        cin.ignore(); // Limpa o buffer antes de usar getline
        getline(cin, produto.nome);
    }

    cout << "Deseja alterar o preço? (1 - Sim, 2 - Não): ";
    cin >> opcaoAlterar;
    if (opcaoAlterar == 1) {
        cout << "Digite o novo preço do produto (atual: R$" << produto.preco << "): ";
        cin >> produto.preco;
    }

    cout << "Deseja alterar o estoque? (1 - Sim, 2 - Não): ";
    cin >> opcaoAlterar;
    if (opcaoAlterar == 1) {
        cout << "Digite a nova quantidade em estoque (atual: " << produto.estoque << "): ";
        cin >> produto.estoque;
    }

    cout << "Produto editado com sucesso!\n";
}

// Função para excluir um produto
void excluirProduto() {
    exibirProdutos();
    int opcaoProduto;
    cout << "Digite o número do produto que deseja excluir: ";
    cin >> opcaoProduto;

    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto inválido!\n";
        return;
    }

    produtos.erase(produtos.begin() + opcaoProduto - 1);
    cout << "Produto excluído com sucesso!\n";
}

// Função para exibir os produtos cadastrados
void exibirProdutos() {
    cout << "Produtos cadastrados:\n";
    for (size_t i = 0; i < produtos.size(); ++i) {
        const Produto& produto = produtos[i];
        cout << i + 1 << ". " << produto.nome << " - R$" << produto.preco << " - Estoque: " << produto.estoque << " - "
             << (produto.precoPorKg ? "Por kg" : "Por unidade") << endl;
    }
}

// Função para comprar um produto
double comprarProduto(double& totalCompra) {
    exibirProdutos();
    int opcaoProduto, quantidade;

    cout << "Digite o número do produto que deseja comprar: ";
    cin >> opcaoProduto;

    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
        cout << "Produto inválido!\n";
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
        cout << "Preço por kg. Custo total: R$" << custoProduto << endl;
    } else {
        cout << "Preço por unidade. Custo total: R$" << custoProduto << endl;
    }

    totalCompra += custoProduto;  // Acumulando o total da compra
    produto.estoque -= quantidade; // Atualizando o estoque
    return 0.0;  // Não precisa retornar o valor, pois estamos acumulando em totalCompra
}

// Função para finalizar a compra
// Função para finalizar a compra
void finalizarCompra(double totalCompra) {
    if (totalCompra > 0) {
        cout << "Compra finalizada com sucesso! Total: R$" << totalCompra << endl;
        salvarCompraCSV(totalCompra);
        cout << "Obrigado pela compra! Volte sempre...\n";
        exit(0);  // Encerra o programa após finalizar a compra
    } else {
        cout << "Nenhum produto foi comprado. A compra foi cancelada.\n";
    }
}


// Função para salvar a compra em um arquivo CSV
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

// Função para cancelar a compra
void cancelarCompra() {
    cout << "Compra cancelada.\n";
}

int main() {
    setlocale(LC_ALL, "");

// Carrega os produtos no início do programa
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
                comprarProduto(totalCompra); // Passando o totalCompra por referência
                break;
            case 3:
                finalizarCompra(totalCompra);
                break;
            case 4:
                cancelarCompra();
                break;
            default:
                cout << "Opção inválida!\n";
        }
    } while (opcao != 0);

    return 0;
}
