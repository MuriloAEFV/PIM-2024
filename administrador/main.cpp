#include <iostream>  // Biblioteca para entrada e sa�da padr�o
#include <fstream>   // Biblioteca para manipula��o de arquivos
#include <vector>    // Biblioteca para trabalhar com vetores (listas din�micas)
#include <string>    // Biblioteca para trabalhar com strings
#include <sstream>   // Biblioteca para manipula��o de strings de forma mais eficiente
#include <locale.h>  // Biblioteca para configura��o de localiza��o (idioma)
#include <limits>    // Biblioteca para utilizar numeric_limits
#include <algorithm> // Biblioteca para utilizar std::max

using namespace std; // Para evitar escrever std:: antes de cada comando padr�o

// Estrutura que define o modelo de produto
struct Produto {
    string nome;        // Nome do produto
    double preco;       // Pre�o do produto
    int estoque;        // Quantidade em estoque
    bool precoPorKg;    // Tipo de pre�o (se � por kg ou por unidade)
};

// Vetor global para armazenar os produtos
vector<Produto> produtos;

// Fun��es declaradas no in�cio

// Fun��o que exibe o menu do administrador
void exibirMenuAdministrador();

// Fun��o que cadastra um novo produto
void cadastrarProduto();

// Fun��o que edita um produto existente
void editarProduto();

// Fun��o que exclui um produto
void excluirProduto();

// Fun��o que exibe os produtos cadastrados
void exibirProdutos();

// Fun��o que salva os produtos em um arquivo CSV
void salvarProdutosCSV();

// Fun��o que carrega os produtos de um arquivo CSV
void carregarProdutosCSV();

// Fun��o que verifica se o usu�rio tem privil�gios de administrador
bool verificarAdministrador();

// Fun��o para verificar a senha de administrador
bool verificarAdministrador() {
    string senha;
    cout << "Digite a senha de administrador: ";
    cin >> senha; // Solicita a senha do administrador
    return senha == "123"; // Verifica se a senha est� correta
}

// Fun��o principal que controla o fluxo de execu��o do programa
void modoAdministrador() {
    // Carrega os produtos do arquivo ao iniciar
    carregarProdutosCSV();

    // Verifica se a senha do administrador est� correta
    if (!verificarAdministrador()) {
        cout << "Acesso negado. Senha incorreta.\n";
        return;
    }

    int opcAdmin;
    do {
        // Exibe o menu do administrador
        exibirMenuAdministrador();
        cin >> opcAdmin;  // L� a op��o escolhida pelo administrador

        // Verifica se a op��o � v�lida (1 a 5)
        while (cin.fail() || opcAdmin < 1 || opcAdmin > 5)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer do cin
            cout << "Op��o inv�lida! Digite uma op��o v�lida (1 a 5): ";
            cin >> opcAdmin;
        }

        // Realiza a a��o correspondente � op��o escolhida
        switch (opcAdmin)
        {
            case 1:
                cadastrarProduto();    // Chama a fun��o de cadastrar produto
                salvarProdutosCSV();   // Salva os produtos ap�s o cadastro
                break;
            case 2:
                editarProduto();       // Chama a fun��o de editar produto
                salvarProdutosCSV();   // Salva os produtos ap�s a edi��o
                break;
            case 3:
                excluirProduto();      // Chama a fun��o de excluir produto
                salvarProdutosCSV();   // Salva os produtos ap�s a exclus�o
                break;
            case 4:
                exibirProdutos();      // Chama a fun��o para exibir os produtos
                break;
            case 5:
                cout << "Voltando ao menu principal...\n";  // Sai do modo administrador
                break;
        }
    } while (opcAdmin != 5); // Repete at� o administrador escolher sair (op��o 5)
}

// Fun��o que exibe o menu de op��es do administrador
void exibirMenuAdministrador()
{
    cout << "\n--- Modo Administrador ---\n";
    cout << "1. Cadastrar produto\n";
    cout << "2. Editar produto\n";
    cout << "3. Excluir produto\n";
    cout << "4. Exibir produtos\n";
    cout << "5. Sair\n";
    cout << "Op��o: ";
}

// Fun��o que cadastra um novo produto
void cadastrarProduto()
{
    Produto produto;
    int tipoPreco;
    cout << "Digite o nome do produto: ";
    cin.ignore(); // Limpa o buffer do cin
    getline(cin, produto.nome);  // L� o nome do produto

    cout << "Digite o tipo de pre�o: \n1. Por kg\n2. Por unidade\nOp��o: ";
    cin >> tipoPreco;  // L� a op��o de tipo de pre�o

    // Verifica se a op��o de tipo de pre�o � v�lida
    while (cin.fail() || (tipoPreco != 1 && tipoPreco != 2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Op��o inv�lida! Digite 1 para 'Por kg' ou 2 para 'Por unidade': ";
        cin >> tipoPreco;
    }

    produto.precoPorKg = (tipoPreco == 1);  // Define se o pre�o � por kg ou por unidade

    cout << "Digite o pre�o do produto: ";
    cin >> produto.preco;  // L� o pre�o do produto
    cout << "Digite a quantidade em estoque: ";
    cin >> produto.estoque;  // L� a quantidade em estoque

    produtos.push_back(produto);  // Adiciona o produto � lista de produtos
    cout << "Produto cadastrado com sucesso!\n";
}

// Fun��o que edita um produto existente
// Fun��o que edita um produto existente
void editarProduto()
{
    exibirProdutos();  // Exibe os produtos dispon�veis
    size_t opcaoProduto;
    cout << "Digite o n�mero do produto que deseja editar: ";
    cin >> opcaoProduto;

    // Verifica se a op��o � v�lida (n�mero de produto dentro do intervalo)
    while (cin.fail() || opcaoProduto < 1 || opcaoProduto > produtos.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Produto inv�lido! Digite um n�mero de produto v�lido: ";
        cin >> opcaoProduto;
    }

    // Editando o produto
    Produto& produto = produtos[opcaoProduto - 1];
    cout << "Editando o produto: " << produto.nome << endl;

    // Editando o nome
    int editarNome;
    cout << "Deseja alterar o nome do produto? (1 - Sim, 2 - N�o): ";
    cin >> editarNome;
    if (editarNome == 1)
    {
        cout << "Digite o novo nome: ";
        cin.ignore(); // Limpa o buffer do cin
        getline(cin, produto.nome);  // L� o novo nome do produto
    }

    // Editando o pre�o
    int editarPreco;
    cout << "Deseja alterar o pre�o do produto? (1 - Sim, 2 - N�o): ";
    cin >> editarPreco;
    if (editarPreco == 1)
    {
        cout << "Digite o novo pre�o: ";
        cin >> produto.preco;  // L� o novo pre�o do produto
    }

    // Editando a quantidade em estoque
    int editarEstoque;
    cout << "Deseja alterar a quantidade em estoque? (1 - Sim, 2 - N�o): ";
    cin >> editarEstoque;
    if (editarEstoque == 1)
    {
        cout << "Digite a nova quantidade em estoque: ";
        cin >> produto.estoque;  // L� a nova quantidade em estoque
    }

    // Editando o tipo de pre�o (kg ou unidade)
    int editarTipoPreco;
    cout << "Deseja alterar o tipo de pre�o (kg ou unidade)? (1 - Sim, 2 - N�o): ";
    cin >> editarTipoPreco;
    if (editarTipoPreco == 1)
    {
        int tipoPreco;
        cout << "Digite o novo tipo de pre�o: \n1. Por kg\n2. Por unidade\nOp��o: ";
        cin >> tipoPreco;
        produto.precoPorKg = (tipoPreco == 1);  // Define se o pre�o � por kg ou por unidade
    }

    cout << "Produto editado com sucesso!\n";
}


// Fun��o que exclui um produto
// Fun��o que exclui um produto
void excluirProduto()
{
    exibirProdutos();  // Exibe os produtos dispon�veis
    size_t opcaoProduto;
    cout << "Digite o n�mero do produto que deseja excluir: ";
    cin >> opcaoProduto;

    // Verifica se a op��o � v�lida
    while (cin.fail() || opcaoProduto < 1 || opcaoProduto > produtos.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Produto inv�lido! Digite um n�mero de produto v�lido: ";
        cin >> opcaoProduto;
    }

    // Exibe a confirma��o de exclus�o
    int confirmacao;
    cout << "Deseja mesmo excluir o produto? (1 - Excluir, 2 - Cancelar): ";
    cin >> confirmacao;

    // Verifica a escolha do usu�rio
    while (cin.fail() || (confirmacao != 1 && confirmacao != 2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Op��o inv�lida! Digite 1 para excluir ou 2 para cancelar: ";
        cin >> confirmacao;
    }

    if (confirmacao == 1)
    {
        // Exclui o produto selecionado
        produtos.erase(produtos.begin() + opcaoProduto - 1);
        cout << "Produto exclu�do com sucesso!\n";
    }
    else
    {
        cout << "Exclus�o cancelada.\n";
    }
}


// Fun��o que exibe os produtos cadastrados
void exibirProdutos()
 {
    cout << "--- Produtos Cadastrados ---\n";
    for (size_t i = 0; i < produtos.size(); ++i)
        {
        cout << i + 1 << ". " << produtos[i].nome
             << " - Pre�o: " << produtos[i].preco
             << " - Estoque: " << produtos[i].estoque
             << " - Pre�o por: " << (produtos[i].precoPorKg ? "kg" : "unidade")
             << endl;
    }
}


// Fun��o que salva os produtos em um arquivo CSV
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

// Fun��o que carrega os produtos de um arquivo CSV
void carregarProdutosCSV()
 {
    ifstream arquivo("produtos.csv"); // Abre o arquivo para leitura
    string linha;
    while (getline(arquivo, linha))
        {
        stringstream ss(linha);
        Produto produto;
        string tipoPreco;

        // L� cada campo da linha separando por ";"
        getline(ss, produto.nome, ';');  // L� o nome do produto
        ss >> produto.preco;             // L� o pre�o do produto
        ss.ignore();                     // Ignora o separador ";"
        ss >> produto.estoque;           // L� o estoque do produto
        ss.ignore();                     // Ignora o separador ";"
        getline(ss, tipoPreco);          // L� o tipo de pre�o ("kg" ou "unidade")

        // Converte o tipo de pre�o
        produto.precoPorKg = (tipoPreco == "kg");

        // Adiciona o produto ao vetor de produtos
        produtos.push_back(produto);
    }
    arquivo.close(); // Fecha o arquivo
}


// Fun��o principal que configura a localidade e chama o modo administrador
int main()
 {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");  // Configura o idioma para portugu�s brasileiro

    modoAdministrador();  // Chama o modo administrador
    return 0;  // Finaliza o programa
}
