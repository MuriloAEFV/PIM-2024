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

// Declaração das funções
void carregarProdutosCSV();
void exibirProdutos();
double comprarProduto(vector<Produto>& produtosComprados);
void finalizarCompra(double totalCompra);
void salvarCompraCSV(double totalCompra);  // Declaração da função que faltava

// Função para carregar os produtos do arquivo CSV
void carregarProdutosCSV() {
    ifstream arquivo("../administrador/produtos.csv");  // Caminho relativo para o arquivo CSV
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de produtos.\n";
        return;
    }

    string linha;
    getline(arquivo, linha); // Ignora o cabeçalho

    while (getline(arquivo, linha)) {
        Produto produto;
        size_t pos = 0;

        // Lê o nome do produto
        pos = linha.find(',');
        produto.nome = linha.substr(0, pos);
        linha.erase(0, pos + 1);

        // Lê o preço do produto
        pos = linha.find(',');
        produto.preco = stod(linha.substr(0, pos));
        linha.erase(0, pos + 1);

        // Lê o estoque do produto
        pos = linha.find(',');
        produto.estoque = stoi(linha.substr(0, pos));
        linha.erase(0, pos + 1);

        // Lê o tipo de preço (Kg ou Unidade)
        produto.precoPorKg = (linha == "Kg");

        // Adiciona o produto ao vetor
        produtos.push_back(produto);
    }

    arquivo.close();  // Fecha o arquivo após a leitura
}

// Função para exibir os produtos disponíveis
void exibirProdutos() {
    cout << "Produtos disponíveis:\n";
    for (size_t i = 0; i < produtos.size(); ++i) {
        cout << i + 1 << ". " << produtos[i].nome << " - Preço: R$" << produtos[i].preco
             << (produtos[i].precoPorKg ? " por Kg" : " por unidade")
             << " - Estoque: " << produtos[i].estoque << "\n";
    }
}

// Função para comprar um produto
double comprarProduto(vector<Produto>& produtosComprados) {
    exibirProdutos();
    int opcaoProduto, quantidade;
    cout << "Digite o número do produto que deseja comprar: ";
    cin >> opcaoProduto;

    if (opcaoProduto < 1 || opcaoProduto >= produtos.size()) {  // Corrigido para >= no caso de erro
        cout << "Produto inválido!\n";
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

// Função para finalizar a compra
void finalizarCompra(double totalCompra) {
    if (totalCompra == 0) {
        cout << "Nenhum produto foi comprado.\n";
        return;
    }

    cout << "Total da compra: R$" << totalCompra << "\n";
    salvarCompraCSV(totalCompra);  // Registra a compra no CSV
}

// Função para salvar a compra no arquivo CSV
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

// Função principal do programa
int main() {
    setlocale(LC_ALL,"");  // Configura a localização para suportar caracteres especiais

    vector<Produto> produtosComprados;  // Vetor para armazenar os produtos comprados
    double totalCompra = 0;  // Variável para armazenar o total da compra

    // Chama a função para carregar os produtos do arquivo CSV
    carregarProdutosCSV();

    int opcao;
    do {
        cout << "\n--- Menu de Compras ---\n";
        cout << "1. Comprar produto\n";
        cout << "2. Finalizar compra\n";
        cout << "3. Cancelar compra\n";  // Substitui 'Sair' por 'Cancelar compra'
        cout << "Opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                totalCompra += comprarProduto(produtosComprados);  // Adiciona o custo da compra ao total
                break;
            case 2:
                finalizarCompra(totalCompra);  // Finaliza a compra e exibe o total
                return 0;  // Para a execução do programa após a finalização da compra
            case 3:
                cout << "Compra cancelada!\n";  // Exibe mensagem e encerra o programa
                return 0;  // Encerra o programa imediatamente
            default:
                cout << "Opção inválida!\n";
        }
    } while (true);  // Continua até o usuário escolher cancelar ou finalizar

    return 0;
}
