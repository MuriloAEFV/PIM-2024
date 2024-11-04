// Incluindo bibliotecas necessárias para a execução do projeto:

#include <iostream>
#include <locale.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Produto { //Definição da estrutura que reresenta um produto
    string nome; //Tipo de variável utilizado para nomear o produto
    double preco; //Tipo de variável utilizado para atribuir preço ao produto
    int estoque; //Tipo de variável utilizado para atribuir um número inteiro ao estoque
    bool precoPorKg; // true = por kg, false = por unidade (utilizado booleanos para verificação)
};

vector<Produto> produtos; // Acessando o banco de dados com os produtos já cadastrados.

void exibirMenu(); // Função de chamada do menu do software
void cadastrarProduto(); // Função utilizada para cadastar o produto.
void editarProduto(); // Função utilizada para editar produtos já cadastrados, solicitado o número do produto a ser editado.
void excluirProduto(); // Função utilizada para excluir produtos já cadastrados.
void exibirProdutos(); // Função utilizada para exibir produtos já cadastrados.
void salvarProdutosCSV(); // Salva os produtos em um arquivo CSV (atenção essa opção permite vizualização direta por planilhas, mas em caso de muitos dados pode apresentar uma exibição poluída).
double comprarProduto(); // Permite ao usuário comprar um produto. Exibe os produtos e solicita o número do produto e a quantidade desejada, verificando se há estoque suficiente. Retorna o custo total da compra.
void finalizarCompra(double totalCompra); //Finaliza a compra, perguntando ao usuário como deseja pagar (à vista ou a prazo). Calcula o total e salva os dados da compra em um arquivo CSV.
void salvarCompraCSV(double totalCompra); //Salva o total da compra em um arquivo CSV chamado compra.csv. (gera uma nota da compra para o cliente).

bool verificarAdministrador(); // Verifica a configuração exata para acessar o modo admistrador (Verifica a senha inserida pelo usuário)
void modoAdministrador(); // Caso aprovado a função de verificação, acessa o menu do administrador com suas respectivas funções.

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

bool verificarAdministrador() {
    string senha;
    cout << "Digite a senha de administrador: ";
    cin >> senha;
    return senha == "admin123"; // senha do admin
}

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

void cadastrarProduto() {
    Produto produto;
    int tipoPreco;
    cout << "Digite o nome do produto: ";
    cin.ignore(); // Limpa o buffer antes de usar getline
    getline(cin, produto.nome); // permitir espa�os no nome do produto
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
    cin.ignore(); // Limpa o buffer antes de usar getline
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

void exibirProdutos() {
    cout << "Produtos dispon�veis:\n";
    for (size_t i = 0; i < produtos.size(); ++i) {
        cout << i + 1 << ". " << produtos[i].nome << " - Pre�o: R$" << produtos[i].preco
             << (produtos[i].precoPorKg ? " por Kg" : " por unidade")
             << " - Estoque: " << produtos[i].estoque << "\n";
    }
}

double comprarProduto() {
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

    salvarProdutosCSV();
    return custoTotal;
}

void finalizarCompra(double totalCompra) {
    if (totalCompra == 0) {
        cout << "Nenhum produto foi comprado.\n";
        return;
    }
    int opcPgto;
    cout << "Total da compra: R$" << totalCompra << "\n";
    cout << "Digite a op��o de pagamento:\n";
    cout << "1. Pagamento � vista (15% de desconto)\n";
    cout << "2. Pagamento � prazo\n";
    cout << "*******************************\n";
    cout << "Op��o:";
    cin >> opcPgto;

    switch (opcPgto) {
        case 1:
            totalCompra *= 0.85;
            cout << "Total � vista: R$ " << totalCompra << "\n";
            break;
        case 2: {
            int numParcelas;
            cout << "N�mero de parcelas:";
            cin >> numParcelas;
            cout << "Total � prazo: " << numParcelas << " x de R$ " << (totalCompra / numParcelas) << "\n";
            break;
        }
        default:
            cout << "Op��o inv�lida!\n";
            return;
    }

    salvarCompraCSV(totalCompra);
    //cout << "Compra finalizada e salva no arquivo CSV!\n"; // eu tava usando para testar se deu certo o codigo
}

void salvarCompraCSV(double totalCompra) {
    ofstream arquivo("compra.csv");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo para salvar compra.\n";
        return;
    }

    arquivo << "Total da Compra\n";
    arquivo << totalCompra << "\n";

    arquivo.close();
    //cout << "Compra salva em compra.csv\n"; // eu tava usando para testar se deu certo o codigo
}

int main() {
    setlocale(LC_ALL, "");

    int opc;
    double totalCompra = 0;

    do {
        exibirMenu();
        cin >> opc;

        switch (opc) {
            case 1:
                modoAdministrador(); // Executa o modo administrador se a senha estiver correta
                break;
            case 2:
                totalCompra += comprarProduto();
                break;
            case 3:
                finalizarCompra(totalCompra);
                opc = 4; // Sair ap�s finalizar a compra
                break;
            case 4:
                cout << "Compra cancelada\n";
                break;
            default:
                cout << "Op��o inv�lida!\n";
        }
    } while (opc != 4);

    cout << "Obrigado e Volte Sempre..." << endl;
    return 0;
}
