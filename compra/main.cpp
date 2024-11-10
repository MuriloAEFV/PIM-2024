#include <iostream>   // Biblioteca para manipula��o de entrada e sa�da (ex: cin, cout)
#include <fstream>    // Biblioteca para manipula��o de arquivos (ex: ifstream, ofstream)
#include <vector>     // Biblioteca que define o container vector, utilizado para armazenar dados din�micos
#include <string>     // Biblioteca para manipula��o de strings (ex: string)
#include <cstdlib>    // Para uso de fun��es de utilidade (por exemplo, std::isdigit)

using namespace std;  // Permite o uso direto de nomes como cout, cin, etc., sem precisar de "std::"

// Estrutura que representa um produto
struct Produto {
    string nome;         // Nome do produto
    double preco;        // Pre�o do produto
    int estoque;         // Quantidade de produtos dispon�veis em estoque
    bool precoPorKg;     // Indica se o pre�o � por Kg (true) ou por unidade (false)
};

vector<Produto> produtos;  // Vetor global para armazenar os produtos

// Declara��o das fun��es
void carregarProdutosCSV();
void exibirProdutos();
double comprarProduto(vector<Produto>& produtosComprados);
void finalizarCompra(double totalCompra);
void salvarCompraCSV(double totalCompra);
void salvarProdutosCSV();  // Fun��o para salvar o estoque atualizado

// Fun��o para verificar se uma string � um n�mero v�lido
bool isNumeroValido(const string& str) {
    // Tenta converter a string para double e verificar se � v�lida
    try {
        stod(str);  // Tenta converter para n�mero
        return true;
    } catch (const invalid_argument& e) {
        return false;
    } catch (const out_of_range& e) {
        return false;
    }
}

// Fun��o para carregar os produtos do arquivo CSV
void carregarProdutosCSV()
{
    ifstream arquivo("../administrador/produtos.csv");  // Caminho relativo para o arquivo CSV
    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo de produtos.\n";
        return;
    }

    string linha;
    getline(arquivo, linha); // Ignora o cabe�alho do arquivo CSV

    while (getline(arquivo, linha))
    {
        Produto produto;
        size_t pos = 0;

        // L� o nome do produto
        pos = linha.find(';');
        produto.nome = linha.substr(0, pos);
        linha.erase(0, pos + 1);

        // L� o pre�o do produto
        pos = linha.find(';');
        string precoStr = linha.substr(0, pos);
        linha.erase(0, pos + 1);

        // Verifica se a string de pre�o � v�lida
        if (!isNumeroValido(precoStr)) {
            cout << "Pre�o inv�lido para o produto " << produto.nome << ": " << precoStr << endl;
            continue;  // Pula para o pr�ximo produto
        }

        produto.preco = stod(precoStr);  // Converte a string para double

        // L� o estoque do produto
        pos = linha.find(';');
        produto.estoque = stoi(linha.substr(0, pos));
        linha.erase(0, pos + 1);

        // L� o tipo de pre�o (Kg ou Unidade)
        produto.precoPorKg = (linha == "kg");

        // Adiciona o produto ao vetor
        produtos.push_back(produto);
    }

    arquivo.close();  // Fecha o arquivo ap�s a leitura
}

// Fun��o para exibir os produtos dispon�veis
void exibirProdutos()
{
    cout << "Produtos dispon�veis:\n";
    for (size_t i = 0; i < produtos.size(); ++i)
    {
        cout << i + 1 << ". " << produtos[i].nome << " - Pre�o: R$" << produtos[i].preco
             << (produtos[i].precoPorKg ? " por Kg" : " por unidade")
             << " - Estoque: " << produtos[i].estoque << "\n";
    }
}

// Fun��o para comprar um produto
double comprarProduto(vector<Produto>& produtosComprados)
{
    exibirProdutos();
    int opcaoProduto, quantidade;

    // Verifica se a op��o do produto � v�lida
    do {
        cout << "Digite o n�mero do produto que deseja comprar: ";
        cin >> opcaoProduto;
        if (opcaoProduto < 1 || opcaoProduto > produtos.size())
        {
            cout << "Produto inv�lido! Tente novamente.\n";
        }
    } while (opcaoProduto < 1 || opcaoProduto > produtos.size());  // Repete at� a op��o ser v�lida

    Produto& produtoEscolhido = produtos[opcaoProduto - 1];
    cout << "Digite a quantidade desejada" << (produtoEscolhido.precoPorKg ? " em Kg: " : " em unidades: ");
    cin >> quantidade;

    // Verifica se a quantidade � suficiente no estoque
    if (quantidade > produtoEscolhido.estoque)
    {
        cout << "Quantidade em estoque insuficiente!\n";
        return 0;
    }

    produtoEscolhido.estoque -= quantidade;  // Atualiza o estoque ap�s a compra
    double custoTotal = quantidade * produtoEscolhido.preco;  // Calcula o custo total da compra
    cout << "Total parcial: R$ " << custoTotal << "\n";

    // Adiciona o produto comprado � lista de produtos comprados
    Produto produtoComprado = produtoEscolhido;
    produtoComprado.estoque = quantidade;
    produtosComprados.push_back(produtoComprado);

    return custoTotal;  // Retorna o custo total da compra
}

// Fun��o para confirmar a finaliza��o da compra
bool confirmarFinalizacaoCompra()
{
    int opcaoConfirmacao;
    cout << "Deseja finalizar a compra?\n1 - Sim\n2 - N�o\n";
    do {
        cout << "Escolha uma op��o: ";
        cin >> opcaoConfirmacao;

        if (opcaoConfirmacao == 1) {
            return true;  // Retorna verdadeiro se o usu�rio confirmar a finaliza��o
        } else if (opcaoConfirmacao == 2) {
            cout << "Retornando ao menu principal...\n";
            return false;  // Retorna falso se o usu�rio n�o confirmar
        } else {
            cout << "Op��o inv�lida! Tente novamente.\n";
        }
    } while (true);  // Continua at� o usu�rio escolher uma op��o v�lida
}

// Fun��o para finalizar a compra
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
        cout << "Compra n�o finalizada.\n";
    }
}

// Fun��o para salvar a compra no arquivo CSV
void salvarCompraCSV(double totalCompra)
{
    ofstream arquivo("compras.csv", ios::app);  // Abre o arquivo em modo de anexo
    if (!arquivo.is_open()) {
        cout << "Erro ao salvar a compra.\n";
        return;
    }

    arquivo << "Total Compra: R$" << totalCompra << "\n";
    arquivo.close();  // Fecha o arquivo ap�s salvar a compra
}

// Fun��o para salvar o estoque atualizado no arquivo CSV
void salvarProdutosCSV()
{
    ofstream arquivo("../administrador/produtos.csv", ios::trunc);  // Abre o arquivo para sobrescrever
    if (!arquivo.is_open()) {
        cout << "Erro ao salvar o estoque.\n";
        return;
    }

    arquivo << "Nome;Pre�o;Estoque;Tipo\n";  // Cabe�alho do CSV
    for (const Produto& produto : produtos)
    {
        arquivo << produto.nome << ";" << produto.preco << ";" << produto.estoque << ";"
                << (produto.precoPorKg ? "kg" : "unidade") << "\n";
    }

    arquivo.close();  // Fecha o arquivo ap�s salvar
}

// Fun��o para cancelar a compra com confirma��o
bool cancelarCompra()
{
    int opcaoCancelamento;
    cout << "Deseja mesmo cancelar a compra? \n1 - Sim\n2 - N�o\n";
    do {
        cout << "Escolha uma op��o: ";
        cin >> opcaoCancelamento;

        if (opcaoCancelamento == 1) {
            cout << "Compra cancelada!\n";
            return true;  // Retorna verdadeiro se a compra for cancelada
        } else if (opcaoCancelamento == 2) {
            cout << "Retornando ao menu principal...\n";
            return false;  // Retorna falso se o usu�rio n�o quiser cancelar
        } else {
            cout << "Op��o inv�lida! Tente novamente.\n";
        }
    } while (true);  // Continua at� o usu�rio escolher uma op��o v�lida
}

// Fun��o principal do programa
int main()
{
    setlocale(LC_ALL,"");  // Configura a localiza��o para suportar caracteres especiais

    vector<Produto> produtosComprados;  // Vetor para armazenar os produtos comprados
    double totalCompra = 0;  // Vari�vel para armazenar o total da compra

    // Chama a fun��o para carregar os produtos do arquivo CSV
    carregarProdutosCSV();

    int opcao;
    do
    {
        // Exibe o menu para o usu�rio
        cout << "\n--- Menu de Compras ---\n";
        cout << "1. Comprar produto\n";
        cout << "2. Finalizar compra\n";
        cout << "3. Cancelar compra\n";  // Substitui 'Sair' por 'Cancelar compra'

        // Verifica se a op��o digitada � v�lida
        do
        {
            cout << "Op��o: ";
            cin >> opcao;
            if (opcao < 1 || opcao > 3)
            {
                cout << "Op��o inv�lida! Tente novamente.\n";
            }
        } while (opcao < 1 || opcao > 3);  // Repete at� a op��o ser v�lida

        switch (opcao)
        {
            case 1:
                totalCompra += comprarProduto(produtosComprados);  // Adiciona o custo da compra ao total
                break;
            case 2:
                finalizarCompra(totalCompra);  // Finaliza a compra e exibe o total
                return 0;  // Para a execu��o do programa ap�s a finaliza��o da compra
            case 3:
                if (cancelarCompra()) {
                    return 0;  // Encerra o programa imediatamente se a compra for cancelada
                }
                break;
            default:
                // Caso ocorra um erro (n�o esperado devido � verifica��o anterior)
                cout << "Op��o inv�lida! Erro desconhecido.\n";
        }
    } while (true);  // Continua at� o usu�rio escolher cancelar ou finalizar

    return 0;
}
