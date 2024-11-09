// Incluindo bibliotecas necessárias para a execução do projeto:

#include <iostream>
#include <locale.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

     //Definição da estrutura que reresenta um produto
struct Produto {

    //Tipo de variável utilizado para nomear o produto
    string nome;

    //Tipo de variável utilizado para atribuir preço ao produto
    double preco;

    //Tipo de variável utilizado para atribuir um número inteiro ao estoque
    int estoque;

    // true = por kg, false = por unidade (utilizado booleanos para verificação)
    bool precoPorKg;
};

 // Acessando o banco de dados com os produtos já cadastrados.
vector<Produto> produtos;

 // Função de chamada do menu do software
void exibirMenu();

 // Função utilizada para cadastar o produto.
void cadastrarProduto();

// Função utilizada para editar produtos já cadastrados, solicitado o número do produto a ser editado.
void editarProduto();

// Função utilizada para excluir produtos já cadastrados.
void excluirProduto();

// Função utilizada para exibir produtos já cadastrados.
void exibirProdutos();

 // Salva os produtos em um arquivo CSV (atenção essa opção permite vizualização direta por planilhas, mas em caso de muitos dados pode apresentar uma exibição poluída).
void salvarProdutosCSV();

// Permite ao usuário comprar um produto. Exibe os produtos e solicita o número do produto e a quantidade desejada, verificando se há estoque suficiente. Retorna o custo total da compra.
double comprarProduto();

//Finaliza a compra, perguntando ao usuário como deseja pagar (à vista ou a prazo). Calcula o total e salva os dados da compra em um arquivo CSV.
void finalizarCompra(double totalCompra);

 //Salva o total da compra em um arquivo CSV chamado compra.csv. (gera uma nota da compra para o cliente).
void salvarCompraCSV(double totalCompra);

 // Verifica a configuração exata para acessar o modo admistrador (Verifica a senha inserida pelo usuário)
bool verificarAdministrador();

 // Caso aprovado a função de verificação, acessa o menu do administrador com suas respectivas funções.
void modoAdministrador();

// exibir menu usado para o menu de opções
void exibirMenu() {
    cout << "\n*****************************************\n";
    cout << "|        Quintandinha Maçã Amarela         |\n";
    cout << "*****************************************\n";
    cout << "Digite a opção desejada:\n";
    cout << "1. Acessar modo administrador\n";
    cout << "2. Comprar produto\n";
    cout << "3. Finalizar compra\n";
    cout << "4. Cancelar compra\n";
    cout << "*****************************************\n";
    cout << "Opção:";
}

// verificasor de usuário administrador
bool verificarAdministrador() {
    string senha;
    cout << "Digite a senha de administrador: ";
    cin >> senha;
    return senha == "admin123"; // <---- senha do administrador!
}

// opções do modo de administrador
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
        cout << "Opção: ";
        cin >> opcAdmin;

// usado para menu de opções switch case
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

// acesso ao painel cadastrar os produtos
void cadastrarProduto() {
    Produto produto;
    int tipoPreco;
    cout << "Digite o nome do produto: ";
    cin.ignore(); // <--- Limpa o buffer antes de usar getline
    getline(cin, produto.nome); // <---- permitir espaços no nome do produto
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


// menu de alterar o produto já cadastrado
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
    cout << "Digite o novo nome do produto (atual: " << produto.nome << "): ";
    cin.ignore(); // <---- Limpa o buffer antes de usar getline
    getline(cin, produto.nome);

    cout << "Digite o novo preço do produto (atual: R$" << produto.preco << "): ";
    cin >> produto.preco;

    cout << "Digite a nova quantidade em estoque (atual: " << produto.estoque << "): ";
    cin >> produto.estoque;

    int tipoPreco;
    cout << "Digite o tipo de preço (atual: " << (produto.precoPorKg ? "por kg" : "por unidade") << "): \n1. Por kg\n2. Por unidade\n";
    cin >> tipoPreco;
    produto.precoPorKg = (tipoPreco == 1);

    cout << "Produto editado com sucesso!\n";
}

// menu de "deletar"/ excluir um produto já cadastrado
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

// menu de exibição dos produtos já cadastrados
void exibirProdutos() {
    cout << "Produtos disponíveis:\n";
    for (size_t i = 0; i < produtos.size(); ++i) {
        cout << i + 1 << ". " << produtos[i].nome << " - Preço: R$" << produtos[i].preco
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
    cout << "Digite o número do produto que deseja comprar: ";
    cin >> opcaoProduto;
    if (opcaoProduto < 1 || opcaoProduto > produtos.size()) {
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

    // Adicionando o produto comprado ao vetor
    Produto produtoComprado = produtoEscolhido;
    produtoComprado.estoque = quantidade; // Atualiza o estoque com a quantidade comprada
    produtosComprados.push_back(produtoComprado);

    salvarProdutosCSV();
    return custoTotal;
}


// menu de finalização de compra / já com o CSV para obter dados de compra concluída
void finalizarCompra(double totalCompra) {
    if (totalCompra <= 0) {  // Verifica se a compra não tem valor positivo
        cout << "Erro: Nenhum produto foi comprado. A compra não pode ser finalizada.\n";
        return;  // Retorna sem fazer nada se a compra for inválida
    }

    int opcPgto;
    cout << "Total da compra: R$" << totalCompra << "\n";
    cout << "Digite a opção de pagamento:\n";
    cout << "1. Pagamento à vista (15% de desconto)\n";
    cout << "2. Pagamento a prazo\n";
    cout << "*******************************\n";
    cout << "Opção: ";
    cin >> opcPgto;

    switch (opcPgto) {
        case 1:
            totalCompra *= 0.85;
            cout << "Total à vista: R$ " << totalCompra << "\n";
            break;
        case 2: {
            int numParcelas;
            cout << "Número de parcelas: ";
            cin >> numParcelas;
            cout << "Total a prazo: " << numParcelas << " x de R$ " << (totalCompra / numParcelas) << "\n";
            break;
        }
        default:
            cout << "Opção inválida!\n";
            return;
    }

    salvarCompraCSV(totalCompra);
    cout << "Compra finalizada !\n";
}

// salva as comprar com opção de caso o arquivo de csv der erro exibir mensagem de erro.
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
                opc = 4; // <--- Sair após finalizar a compra
                break;
            case 4:
                cout << "Compra cancelada\n";
                break;
            default:
                cout << "Opção inválida!\n";
        }
    } while (opc != 4);

    cout << "Obrigado e Volte Sempre..." << endl; // <-- finaliza o programa
    return 0;
}

