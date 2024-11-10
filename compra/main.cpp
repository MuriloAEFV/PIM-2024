#include <iostream>   // Biblioteca para manipulação de entrada e saída (ex: cin, cout)
#include <fstream>    // Biblioteca para manipulação de arquivos (ex: ifstream, ofstream)
#include <vector>     // Biblioteca que define o container vector, utilizado para armazenar dados dinâmicos
#include <string>     // Biblioteca para manipulação de strings (ex: string)
#include <cstdlib>    // Para uso de funções de utilidade (por exemplo, std::isdigit)

using namespace std;  // Permite o uso direto de nomes como cout, cin, etc., sem precisar de "std::"

// Estrutura que representa um produto
struct Produto {
    string nome;         // Nome do produto
    double preco;        // Preço do produto
    int estoque;         // Quantidade de produtos disponíveis em estoque
    bool precoPorKg;     // Indica se o preço é por Kg (true) ou por unidade (false)
};

vector<Produto> produtos;  // Vetor global para armazenar os produtos

// Declaração das funções
void carregarProdutosCSV();
void exibirProdutos();
double comprarProduto(vector<Produto>& produtosComprados);
void finalizarCompra(double totalCompra);
void salvarCompraCSV(double totalCompra);
void salvarProdutosCSV();  // Função para salvar o estoque atualizado

// Função para verificar se uma string é um número válido
bool isNumeroValido(const string& str) {
    // Tenta converter a string para double e verificar se é válida
    try {
        stod(str);  // Tenta converter para número
        return true;
    } catch (const invalid_argument& e) {
        return false;
    } catch (const out_of_range& e) {
        return false;
    }
}

// Função para carregar os produtos do arquivo CSV
void carregarProdutosCSV()
{
    ifstream arquivo("../administrador/produtos.csv");  // Caminho relativo para o arquivo CSV
    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo de produtos.\n";
        return;
    }

    string linha;
    getline(arquivo, linha); // Ignora o cabeçalho do arquivo CSV

    while (getline(arquivo, linha))
    {
        Produto produto;
        size_t pos = 0;

        // Lê o nome do produto
        pos = linha.find(';');
        produto.nome = linha.substr(0, pos);
        linha.erase(0, pos + 1);

        // Lê o preço do produto
        pos = linha.find(';');
        string precoStr = linha.substr(0, pos);
        linha.erase(0, pos + 1);

        // Verifica se a string de preço é válida
        if (!isNumeroValido(precoStr)) {
            cout << "Preço inválido para o produto " << produto.nome << ": " << precoStr << endl;
            continue;  // Pula para o próximo produto
        }

        produto.preco = stod(precoStr);  // Converte a string para double

        // Lê o estoque do produto
        pos = linha.find(';');
        produto.estoque = stoi(linha.substr(0, pos));
        linha.erase(0, pos + 1);

        // Lê o tipo de preço (Kg ou Unidade)
        produto.precoPorKg = (linha == "kg");

        // Adiciona o produto ao vetor
        produtos.push_back(produto);
    }

    arquivo.close();  // Fecha o arquivo após a leitura
}

// Função para exibir os produtos disponíveis
void exibirProdutos()
{
    cout << "Produtos disponíveis:\n";
    for (size_t i = 0; i < produtos.size(); ++i)
    {
        cout << i + 1 << ". " << produtos[i].nome << " - Preço: R$" << produtos[i].preco
             << (produtos[i].precoPorKg ? " por Kg" : " por unidade")
             << " - Estoque: " << produtos[i].estoque << "\n";
    }
}

// Função para comprar um produto
double comprarProduto(vector<Produto>& produtosComprados)
{
    exibirProdutos();
    int opcaoProduto, quantidade;

    // Verifica se a opção do produto é válida
    do {
        cout << "Digite o número do produto que deseja comprar: ";
        cin >> opcaoProduto;
        if (opcaoProduto < 1 || opcaoProduto > produtos.size())
        {
            cout << "Produto inválido! Tente novamente.\n";
        }
    } while (opcaoProduto < 1 || opcaoProduto > produtos.size());  // Repete até a opção ser válida

    Produto& produtoEscolhido = produtos[opcaoProduto - 1];
    cout << "Digite a quantidade desejada" << (produtoEscolhido.precoPorKg ? " em Kg: " : " em unidades: ");
    cin >> quantidade;

    // Verifica se a quantidade é suficiente no estoque
    if (quantidade > produtoEscolhido.estoque)
    {
        cout << "Quantidade em estoque insuficiente!\n";
        return 0;
    }

    produtoEscolhido.estoque -= quantidade;  // Atualiza o estoque após a compra
    double custoTotal = quantidade * produtoEscolhido.preco;  // Calcula o custo total da compra
    cout << "Total parcial: R$ " << custoTotal << "\n";

    // Adiciona o produto comprado à lista de produtos comprados
    Produto produtoComprado = produtoEscolhido;
    produtoComprado.estoque = quantidade;
    produtosComprados.push_back(produtoComprado);

    return custoTotal;  // Retorna o custo total da compra
}

// Função para confirmar a finalização da compra
bool confirmarFinalizacaoCompra()
{
    int opcaoConfirmacao;
    cout << "Deseja finalizar a compra?\n1 - Sim\n2 - Não\n";
    do {
        cout << "Escolha uma opção: ";
        cin >> opcaoConfirmacao;

        if (opcaoConfirmacao == 1) {
            return true;  // Retorna verdadeiro se o usuário confirmar a finalização
        } else if (opcaoConfirmacao == 2) {
            cout << "Retornando ao menu principal...\n";
            return false;  // Retorna falso se o usuário não confirmar
        } else {
            cout << "Opção inválida! Tente novamente.\n";
        }
    } while (true);  // Continua até o usuário escolher uma opção válida
}

// Função para finalizar a compra
void finalizarCompra(double totalCompra)
{
    if (totalCompra == 0)
    {
        cout << "Nenhum produto foi comprado.\n";
        return;
    }

    if (confirmarFinalizacaoCompra()) {
        cout << "Total da compra: R$" << totalCompra << "\n";
        salvarCompraCSV(totalCompra);  // Registra a compra no arquivo CSV
        salvarProdutosCSV();  // Atualiza o estoque no arquivo CSV
        cout << "Compra finalizada com sucesso!\n";
    } else {
        cout << "Compra não finalizada.\n";
    }
}

// Função para salvar a compra no arquivo CSV
void salvarCompraCSV(double totalCompra)
{
    ofstream arquivo("compras.csv", ios::app);  // Abre o arquivo em modo de anexo
    if (!arquivo.is_open()) {
        cout << "Erro ao salvar a compra.\n";
        return;
    }

    arquivo << "Total Compra: R$" << totalCompra << "\n";
    arquivo.close();  // Fecha o arquivo após salvar a compra
}

// Função para salvar o estoque atualizado no arquivo CSV
void salvarProdutosCSV()
{
    ofstream arquivo("../administrador/produtos.csv", ios::trunc);  // Abre o arquivo para sobrescrever
    if (!arquivo.is_open()) {
        cout << "Erro ao salvar o estoque.\n";
        return;
    }

    arquivo << "Nome;Preço;Estoque;Tipo\n";  // Cabeçalho do CSV
    for (const Produto& produto : produtos)
    {
        arquivo << produto.nome << ";" << produto.preco << ";" << produto.estoque << ";"
                << (produto.precoPorKg ? "kg" : "unidade") << "\n";
    }

    arquivo.close();  // Fecha o arquivo após salvar
}

// Função para cancelar a compra com confirmação
bool cancelarCompra()
{
    int opcaoCancelamento;
    cout << "Deseja mesmo cancelar a compra? \n1 - Sim\n2 - Não\n";
    do {
        cout << "Escolha uma opção: ";
        cin >> opcaoCancelamento;

        if (opcaoCancelamento == 1) {
            cout << "Compra cancelada!\n";
            return true;  // Retorna verdadeiro se a compra for cancelada
        } else if (opcaoCancelamento == 2) {
            cout << "Retornando ao menu principal...\n";
            return false;  // Retorna falso se o usuário não quiser cancelar
        } else {
            cout << "Opção inválida! Tente novamente.\n";
        }
    } while (true);  // Continua até o usuário escolher uma opção válida
}

// Função principal do programa
int main()
{
    setlocale(LC_ALL,"");  // Configura a localização para suportar caracteres especiais

    vector<Produto> produtosComprados;  // Vetor para armazenar os produtos comprados
    double totalCompra = 0;  // Variável para armazenar o total da compra

    // Chama a função para carregar os produtos do arquivo CSV
    carregarProdutosCSV();

    int opcao;
    do
    {
        // Exibe o menu para o usuário
        cout << "\n--- Menu de Compras ---\n";
        cout << "1. Comprar produto\n";
        cout << "2. Finalizar compra\n";
        cout << "3. Cancelar compra\n";  // Substitui 'Sair' por 'Cancelar compra'

        // Verifica se a opção digitada é válida
        do
        {
            cout << "Opção: ";
            cin >> opcao;
            if (opcao < 1 || opcao > 3)
            {
                cout << "Opção inválida! Tente novamente.\n";
            }
        } while (opcao < 1 || opcao > 3);  // Repete até a opção ser válida

        switch (opcao)
        {
            case 1:
                totalCompra += comprarProduto(produtosComprados);  // Adiciona o custo da compra ao total
                break;
            case 2:
                finalizarCompra(totalCompra);  // Finaliza a compra e exibe o total
                return 0;  // Para a execução do programa após a finalização da compra
            case 3:
                if (cancelarCompra()) {
                    return 0;  // Encerra o programa imediatamente se a compra for cancelada
                }
                break;
            default:
                // Caso ocorra um erro (não esperado devido à verificação anterior)
                cout << "Opção inválida! Erro desconhecido.\n";
        }
    } while (true);  // Continua até o usuário escolher cancelar ou finalizar

    return 0;
}
