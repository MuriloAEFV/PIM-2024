#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Produto {
    string nome;
    double preco;
    int estoque;
    bool precoPorKg;
};

vector<Produto> produtos;  // Vetor global para armazenar os produtos

// Declara��o das fun��es
void carregarProdutosCSV();
void exibirProdutos();
double comprarProduto(vector<Produto>& produtosComprados);
void finalizarCompra(double totalCompra);
void salvarCompraCSV(double totalCompra);  // Declara��o da fun��o que faltava

// Fun��o para carregar os produtos do arquivo CSV
void carregarProdutosCSV() {
    ifstream arquivo("../administrador/produtos.csv");  // Caminho relativo para o arquivo CSV
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de produtos.\n";
        return;
    }

    string linha;
    getline(arquivo, linha); // Ignora o cabe�alho

    while (getline(arquivo, linha)) {
        Produto produto;
        size_t pos = 0;

        // L� o nome do produto
        pos = linha.find(',');
        produto.nome = linha.substr(0, pos);
        linha.erase(0, pos + 1);

        // L� o pre�o do produto
        pos = linha.find(',');
        produto.preco = stod(linha.substr(0, pos));
        linha.erase(0, pos + 1);

        // L� o estoque do produto
        pos = linha.find(',');
        produto.estoque = stoi(linha.substr(0, pos));
        linha.erase(0, pos + 1);

        // L� o tipo de pre�o (Kg ou Unidade)
        produto.precoPorKg = (linha == "Kg");

        // Adiciona o produto ao vetor
        produtos.push_back(produto);
    }

    arquivo.close();  // Fecha o arquivo ap�s a leitura
}

// Fun��o para exibir os produtos dispon�veis
void exibirProdutos() {
    cout << "Produtos dispon�veis:\n";
    for (size_t i = 0; i < produtos.size(); ++i) {
        cout << i + 1 << ". " << produtos[i].nome << " - Pre�o: R$" << produtos[i].preco
             << (produtos[i].precoPorKg ? " por Kg" : " por unidade")
             << " - Estoque: " << produtos[i].estoque << "\n";
    }
}

// Fun��o para comprar um produto
double comprarProduto(vector<Produto>& produtosComprados) {
    exibirProdutos();
    int opcaoProduto, quantidade;
    cout << "Digite o n�mero do produto que deseja comprar: ";
    cin >> opcaoProduto;

    if (opcaoProduto < 1 || opcaoProduto >= produtos.size()) {  // Corrigido para >= no caso de erro
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

    Produto produtoComprado = produtoEscolhido;
    produtoComprado.estoque = quantidade;
    produtosComprados.push_back(produtoComprado);

    return custoTotal;
}

// Fun��o para finalizar a compra
void finalizarCompra(double totalCompra) {
    if (totalCompra == 0) {
        cout << "Nenhum produto foi comprado.\n";
        return;
    }

    cout << "Total da compra: R$" << totalCompra << "\n";
    salvarCompraCSV(totalCompra);  // Registra a compra no CSV
}

// Fun��o para salvar a compra no arquivo CSV
void salvarCompraCSV(double totalCompra) {
    ofstream arquivo("compras.csv", ios::app);  // Abre o arquivo em modo de anexo
    if (!arquivo.is_open()) {
        cout << "Erro ao salvar a compra.\n";
        return;
    }

    arquivo << "Total Compra: R$" << totalCompra << "\n";
    arquivo.close();
    //cout << "Compra registrada com sucesso em compras.csv.\n"; -- teste de cadastro
}

// Fun��o principal do programa
int main() {
    setlocale(LC_ALL,"");  // Configura a localiza��o para suportar caracteres especiais

    vector<Produto> produtosComprados;  // Vetor para armazenar os produtos comprados
    double totalCompra = 0;  // Vari�vel para armazenar o total da compra

    // Chama a fun��o para carregar os produtos do arquivo CSV
    carregarProdutosCSV();

    int opcao;
    do {
        cout << "\n--- Menu de Compras ---\n";
        cout << "1. Comprar produto\n";
        cout << "2. Finalizar compra\n";
        cout << "3. Cancelar compra\n";  // Substitui 'Sair' por 'Cancelar compra'
        cout << "Op��o: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                totalCompra += comprarProduto(produtosComprados);  // Adiciona o custo da compra ao total
                break;
            case 2:
                finalizarCompra(totalCompra);  // Finaliza a compra e exibe o total
                return 0;  // Para a execu��o do programa ap�s a finaliza��o da compra
            case 3:
                cout << "Compra cancelada!\n";  // Exibe mensagem e encerra o programa
                return 0;  // Encerra o programa imediatamente
            default:
                cout << "Op��o inv�lida!\n";
        }
    } while (true);  // Continua at� o usu�rio escolher cancelar ou finalizar

    return 0;
}
