#include <iostream>  // Biblioteca para entrada e saída padrão
#include <fstream>   // Biblioteca para manipulação de arquivos
#include <vector>    // Biblioteca para trabalhar com vetores (listas dinâmicas)
#include <string>    // Biblioteca para trabalhar com strings
#include <sstream>   // Biblioteca para manipulação de strings de forma mais eficiente
#include <locale.h>  // Biblioteca para configuração de localização (idioma)
#include <limits>    // Biblioteca para utilizar numeric_limits
#include <algorithm> // Biblioteca para utilizar std::max

using namespace std; // Para evitar escrever std:: antes de cada comando padrão

// Estrutura que define o modelo de produto
struct Produto {
    string nome;        // Nome do produto
    double preco;       // Preço do produto
    int estoque;        // Quantidade em estoque
    bool precoPorKg;    // Tipo de preço (se é por kg ou por unidade)
};

// Vetor global para armazenar os produtos
vector<Produto> produtos;

// Funções declaradas no início

// Função que exibe o menu do administrador
void exibirMenuAdministrador();

// Função que cadastra um novo produto
void cadastrarProduto();

// Função que edita um produto existente
void editarProduto();

// Função que exclui um produto
void excluirProduto();

// Função que exibe os produtos cadastrados
void exibirProdutos();

// Função que salva os produtos em um arquivo CSV
void salvarProdutosCSV();

// Função que carrega os produtos de um arquivo CSV
void carregarProdutosCSV();

// Função que verifica se o usuário tem privilégios de administrador
bool verificarAdministrador();

// Função para verificar a senha de administrador
bool verificarAdministrador() {
    string senha;
    cout << "Digite a senha de administrador: ";
    cin >> senha; // Solicita a senha do administrador
    return senha == "123"; // Verifica se a senha está correta
}

// Função principal que controla o fluxo de execução do programa
void modoAdministrador() {
    // Carrega os produtos do arquivo ao iniciar
    carregarProdutosCSV();

    // Verifica se a senha do administrador está correta
    if (!verificarAdministrador()) {
        cout << "Acesso negado. Senha incorreta.\n";
        return;
    }

    int opcAdmin;
    do {
        // Exibe o menu do administrador
        exibirMenuAdministrador();
        cin >> opcAdmin;  // Lê a opção escolhida pelo administrador

        // Verifica se a opção é válida (1 a 5)
        while (cin.fail() || opcAdmin < 1 || opcAdmin > 5)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer do cin
            cout << "Opção inválida! Digite uma opção válida (1 a 5): ";
            cin >> opcAdmin;
        }

        // Realiza a ação correspondente à opção escolhida
        switch (opcAdmin)
        {
            case 1:
                cadastrarProduto();    // Chama a função de cadastrar produto
                salvarProdutosCSV();   // Salva os produtos após o cadastro
                break;
            case 2:
                editarProduto();       // Chama a função de editar produto
                salvarProdutosCSV();   // Salva os produtos após a edição
                break;
            case 3:
                excluirProduto();      // Chama a função de excluir produto
                salvarProdutosCSV();   // Salva os produtos após a exclusão
                break;
            case 4:
                exibirProdutos();      // Chama a função para exibir os produtos
                break;
            case 5:
                cout << "Voltando ao menu principal...\n";  // Sai do modo administrador
                break;
        }
    } while (opcAdmin != 5); // Repete até o administrador escolher sair (opção 5)
}

// Função que exibe o menu de opções do administrador
void exibirMenuAdministrador()
{
    cout << "\n--- Modo Administrador ---\n";
    cout << "1. Cadastrar produto\n";
    cout << "2. Editar produto\n";
    cout << "3. Excluir produto\n";
    cout << "4. Exibir produtos\n";
    cout << "5. Sair\n";
    cout << "Opção: ";
}

// Função que cadastra um novo produto
void cadastrarProduto()
{
    Produto produto;
    int tipoPreco;
    cout << "Digite o nome do produto: ";
    cin.ignore(); // Limpa o buffer do cin
    getline(cin, produto.nome);  // Lê o nome do produto

    cout << "Digite o tipo de preço: \n1. Por kg\n2. Por unidade\nOpção: ";
    cin >> tipoPreco;  // Lê a opção de tipo de preço

    // Verifica se a opção de tipo de preço é válida
    while (cin.fail() || (tipoPreco != 1 && tipoPreco != 2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opção inválida! Digite 1 para 'Por kg' ou 2 para 'Por unidade': ";
        cin >> tipoPreco;
    }

    produto.precoPorKg = (tipoPreco == 1);  // Define se o preço é por kg ou por unidade

    cout << "Digite o preço do produto: ";
    cin >> produto.preco;  // Lê o preço do produto
    cout << "Digite a quantidade em estoque: ";
    cin >> produto.estoque;  // Lê a quantidade em estoque

    produtos.push_back(produto);  // Adiciona o produto à lista de produtos
    cout << "Produto cadastrado com sucesso!\n";
}

// Função que edita um produto existente
// Função que edita um produto existente
void editarProduto()
{
    exibirProdutos();  // Exibe os produtos disponíveis
    size_t opcaoProduto;
    cout << "Digite o número do produto que deseja editar: ";
    cin >> opcaoProduto;

    // Verifica se a opção é válida (número de produto dentro do intervalo)
    while (cin.fail() || opcaoProduto < 1 || opcaoProduto > produtos.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Produto inválido! Digite um número de produto válido: ";
        cin >> opcaoProduto;
    }

    // Editando o produto
    Produto& produto = produtos[opcaoProduto - 1];
    cout << "Editando o produto: " << produto.nome << endl;

    // Editando o nome
    int editarNome;
    cout << "Deseja alterar o nome do produto? (1 - Sim, 2 - Não): ";
    cin >> editarNome;
    if (editarNome == 1)
    {
        cout << "Digite o novo nome: ";
        cin.ignore(); // Limpa o buffer do cin
        getline(cin, produto.nome);  // Lê o novo nome do produto
    }

    // Editando o preço
    int editarPreco;
    cout << "Deseja alterar o preço do produto? (1 - Sim, 2 - Não): ";
    cin >> editarPreco;
    if (editarPreco == 1)
    {
        cout << "Digite o novo preço: ";
        cin >> produto.preco;  // Lê o novo preço do produto
    }

    // Editando a quantidade em estoque
    int editarEstoque;
    cout << "Deseja alterar a quantidade em estoque? (1 - Sim, 2 - Não): ";
    cin >> editarEstoque;
    if (editarEstoque == 1)
    {
        cout << "Digite a nova quantidade em estoque: ";
        cin >> produto.estoque;  // Lê a nova quantidade em estoque
    }

    // Editando o tipo de preço (kg ou unidade)
    int editarTipoPreco;
    cout << "Deseja alterar o tipo de preço (kg ou unidade)? (1 - Sim, 2 - Não): ";
    cin >> editarTipoPreco;
    if (editarTipoPreco == 1)
    {
        int tipoPreco;
        cout << "Digite o novo tipo de preço: \n1. Por kg\n2. Por unidade\nOpção: ";
        cin >> tipoPreco;
        produto.precoPorKg = (tipoPreco == 1);  // Define se o preço é por kg ou por unidade
    }

    cout << "Produto editado com sucesso!\n";
}


// Função que exclui um produto
// Função que exclui um produto
void excluirProduto()
{
    exibirProdutos();  // Exibe os produtos disponíveis
    size_t opcaoProduto;
    cout << "Digite o número do produto que deseja excluir: ";
    cin >> opcaoProduto;

    // Verifica se a opção é válida
    while (cin.fail() || opcaoProduto < 1 || opcaoProduto > produtos.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Produto inválido! Digite um número de produto válido: ";
        cin >> opcaoProduto;
    }

    // Exibe a confirmação de exclusão
    int confirmacao;
    cout << "Deseja mesmo excluir o produto? (1 - Excluir, 2 - Cancelar): ";
    cin >> confirmacao;

    // Verifica a escolha do usuário
    while (cin.fail() || (confirmacao != 1 && confirmacao != 2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opção inválida! Digite 1 para excluir ou 2 para cancelar: ";
        cin >> confirmacao;
    }

    if (confirmacao == 1)
    {
        // Exclui o produto selecionado
        produtos.erase(produtos.begin() + opcaoProduto - 1);
        cout << "Produto excluído com sucesso!\n";
    }
    else
    {
        cout << "Exclusão cancelada.\n";
    }
}


// Função que exibe os produtos cadastrados
void exibirProdutos()
 {
    cout << "--- Produtos Cadastrados ---\n";
    for (size_t i = 0; i < produtos.size(); ++i)
        {
        cout << i + 1 << ". " << produtos[i].nome
             << " - Preço: " << produtos[i].preco
             << " - Estoque: " << produtos[i].estoque
             << " - Preço por: " << (produtos[i].precoPorKg ? "kg" : "unidade")
             << endl;
    }
}


// Função que salva os produtos em um arquivo CSV
void salvarProdutosCSV()
{
    ofstream arquivo("produtos.csv"); // Abre o arquivo para escrita
    if (arquivo.is_open())
        {
        for (const auto& produto : produtos) {
            arquivo << produto.nome << ";" << produto.preco << ";" << produto.estoque
                    << ";" << (produto.precoPorKg ? "kg" : "unidade") << endl;
        }
        arquivo.close(); // Fecha o arquivo
        cout << "Produtos salvos com sucesso!\n";
    } else {
        cout << "Erro ao salvar os produtos no arquivo.\n";
    }
}

// Função que carrega os produtos de um arquivo CSV
void carregarProdutosCSV()
 {
    ifstream arquivo("produtos.csv"); // Abre o arquivo para leitura
    string linha;
    while (getline(arquivo, linha))
        {
        stringstream ss(linha);
        Produto produto;
        string tipoPreco;

        // Lê cada campo da linha separando por ";"
        getline(ss, produto.nome, ';');  // Lê o nome do produto
        ss >> produto.preco;             // Lê o preço do produto
        ss.ignore();                     // Ignora o separador ";"
        ss >> produto.estoque;           // Lê o estoque do produto
        ss.ignore();                     // Ignora o separador ";"
        getline(ss, tipoPreco);          // Lê o tipo de preço ("kg" ou "unidade")

        // Converte o tipo de preço
        produto.precoPorKg = (tipoPreco == "kg");

        // Adiciona o produto ao vetor de produtos
        produtos.push_back(produto);
    }
    arquivo.close(); // Fecha o arquivo
}


// Função principal que configura a localidade e chama o modo administrador
int main()
 {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");  // Configura o idioma para português brasileiro

    modoAdministrador();  // Chama o modo administrador
    return 0;  // Finaliza o programa
}
