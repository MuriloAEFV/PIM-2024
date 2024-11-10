#include <iostream>      // Para entrada e sa�da de dados (cin, cout)
#include <fstream>       // Para manipula��o de arquivos (leitura e escrita)
#include <vector>        // Para utilizar o vetor (lista din�mica)
#include <string>        // Para manipula��o de strings
#include <sstream>       // Para manipula��o de streams (usado para separar strings)
#include <locale.h>      // Para configurar a localidade do programa (uso de caracteres especiais)
#include <limits>        // Para trabalhar com limites de dados (cin.fail() e limpeza de entrada)
#include <algorithm>     // Para fun��es algor�tmicas como "erase" (remo��o de elementos)
#include <ctime>         // Para trabalhar com datas e horas (verifica��o de altera��es no arquivo)
#include <sys/stat.h>  // Para usar a fun��o stat

using namespace std;

// Estrutura que define o modelo de produto
struct Produto {
    string nome;       // Nome do produto
    double preco;      // Pre�o do produto
    int estoque;       // Quantidade em estoque
    bool precoPorKg;   // Indica se o pre�o � por kg (true) ou por unidade (false)
};

vector<Produto> produtos;  // Vetor global que armazena todos os produtos cadastrados

// Fun��es declaradas no in�cio, para serem implementadas posteriormente
void exibirMenuAdministrador();
void cadastrarProduto();
void editarProduto();
void excluirProduto();
void exibirProdutos();
void salvarProdutosCSV();
void carregarProdutosCSV();
bool verificarAdministrador();
bool arquivoModificado();  // Fun��o para verificar se o arquivo foi modificado

// Fun��o que verifica a senha do administrador
bool verificarAdministrador()
{
    string senha;
    cout << "Digite a senha de administrador: ";
    cin >> senha;
    return senha == "123";  // Verifica se a senha digitada � "123"
}

// Fun��o que gerencia o modo administrador, incluindo todas as opera��es de produtos
void modoAdministrador()
{
    carregarProdutosCSV();  // Carrega os produtos ao iniciar o modo administrador

    // Verifica se a senha de administrador � correta
    if (!verificarAdministrador())
    {
        cout << "Acesso negado. Senha incorreta.\n";
        return;
    }

    int opcAdmin;
    do {
        exibirMenuAdministrador();  // Exibe o menu do administrador
        cin >> opcAdmin;

        // Valida a op��o de entrada
        while (cin.fail() || opcAdmin < 1 || opcAdmin > 5)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Op��o inv�lida! Digite uma op��o v�lida (1 a 5): ";
            cin >> opcAdmin;
        }

        // Verifica se o arquivo de produtos foi modificado e recarrega se necess�rio
        if (arquivoModificado())
        {
            cout << "Arquivo de produtos foi modificado. Recarregando os dados...\n";
            carregarProdutosCSV();  // Recarrega os produtos se houve altera��o no arquivo
        }

        // Realiza a a��o correspondente � op��o do administrador
        switch (opcAdmin)
        {
            case 1:  // Cadastrar produto
                cadastrarProduto();
                salvarProdutosCSV();  // Salva os produtos no arquivo ap�s o cadastro
                break;
            case 2:  // Editar produto
                editarProduto();
                salvarProdutosCSV();
                break;
            case 3:  // Excluir produto
                excluirProduto();
                salvarProdutosCSV();
                break;
            case 4:  // Exibir produtos cadastrados
                exibirProdutos();
                break;
            case 5:  // Sair do modo administrador
                cout << "Voltando ao menu principal...\n";
                break;
        }
    } while (opcAdmin != 5);  // Continua at� que o administrador escolha sair (op��o 5)
}

// Fun��o que exibe o menu de op��es para o administrador
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

// Fun��o que permite ao administrador cadastrar um novo produto
void cadastrarProduto()
{
    Produto produto;  // Declara um objeto Produto para armazenar os dados do novo produto
    int tipoPreco;

    cout << "Digite o nome do produto: ";
    cin.ignore();  // Limpa o buffer de entrada antes de capturar uma nova linha
    getline(cin, produto.nome);  // Captura o nome do produto

    cout << "Digite o tipo de pre�o: \n1. Por kg\n2. Por unidade\nOp��o: ";
    cin >> tipoPreco;

    // Valida a op��o escolhida para o tipo de pre�o
    while (cin.fail() || (tipoPreco != 1 && tipoPreco != 2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Op��o inv�lida! Digite 1 para 'Por kg' ou 2 para 'Por unidade': ";
        cin >> tipoPreco;
    }

    produto.precoPorKg = (tipoPreco == 1);  // Define se o pre�o � por kg ou unidade

    cout << "Digite o pre�o do produto: ";
    cin >> produto.preco;
    cout << "Digite a quantidade em estoque: ";
    cin >> produto.estoque;

    produtos.push_back(produto);  // Adiciona o produto ao vetor
    cout << "Produto cadastrado com sucesso!\n";
}

// Fun��o que permite editar os dados de um produto j� cadastrado
void editarProduto()
{
    exibirProdutos();  // Exibe a lista de produtos cadastrados
    size_t opcaoProduto;
    cout << "Digite o n�mero do produto que deseja editar: ";
    cin >> opcaoProduto;

    // Valida a entrada da op��o de produto
    while (cin.fail() || opcaoProduto < 1 || opcaoProduto > produtos.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Produto inv�lido! Digite um n�mero de produto v�lido: ";
        cin >> opcaoProduto;
    }

    Produto& produto = produtos[opcaoProduto - 1];  // Refer�ncia ao produto selecionado
    cout << "Editando o produto: " << produto.nome << endl;

    // Pergunta ao administrador se deseja alterar as informa��es do produto
    int editarNome;
    cout << "Deseja alterar o nome do produto? (1 - Sim, 2 - N�o): ";
    cin >> editarNome;
    if (editarNome == 1)
    {
        cout << "Digite o novo nome: ";
        cin.ignore();
        getline(cin, produto.nome);
    }

    // As demais edi��es seguem a mesma l�gica: perguntar e validar cada altera��o
    int editarPreco;
    cout << "Deseja alterar o pre�o do produto? (1 - Sim, 2 - N�o): ";
    cin >> editarPreco;
    if (editarPreco == 1)
    {
        cout << "Digite o novo pre�o: ";
        cin >> produto.preco;
    }

    int editarEstoque;
    cout << "Deseja alterar a quantidade em estoque? (1 - Sim, 2 - N�o): ";
    cin >> editarEstoque;
    if (editarEstoque == 1)
    {
        cout << "Digite a nova quantidade em estoque: ";
        cin >> produto.estoque;
    }

    int editarTipoPreco;
    cout << "Deseja alterar o tipo de pre�o (kg ou unidade)? (1 - Sim, 2 - N�o): ";
    cin >> editarTipoPreco;
    if (editarTipoPreco == 1)
    {
        int tipoPreco;
        cout << "Digite o novo tipo de pre�o: \n1. Por kg\n2. Por unidade\nOp��o: ";
        cin >> tipoPreco;
        produto.precoPorKg = (tipoPreco == 1);
    }

    cout << "Produto editado com sucesso!\n";
}

// Fun��o que permite excluir um produto cadastrado
void excluirProduto()
 {
    exibirProdutos();  // Exibe a lista de produtos cadastrados
    size_t opcaoProduto;
    cout << "Digite o n�mero do produto que deseja excluir: ";
    cin >> opcaoProduto;

    // Valida a entrada da op��o de produto
    while (cin.fail() || opcaoProduto < 1 || opcaoProduto > produtos.size())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Produto inv�lido! Digite um n�mero de produto v�lido: ";
        cin >> opcaoProduto;
    }

    int confirmacao;
    cout << "Deseja mesmo excluir o produto? (1 - Excluir, 2 - Cancelar): ";
    cin >> confirmacao;

    // Valida a confirma��o de exclus�o
    while (cin.fail() || (confirmacao != 1 && confirmacao != 2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Op��o inv�lida! Digite 1 para excluir ou 2 para cancelar: ";
        cin >> confirmacao;
    }

    if (confirmacao == 1)
    {
        produtos.erase(produtos.begin() + opcaoProduto - 1);  // Exclui o produto
        cout << "Produto exclu�do com sucesso!\n";
    } else {
        cout << "Exclus�o cancelada.\n";
    }
}

// Fun��o que exibe a lista de produtos cadastrados
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

// Fun��o que salva os dados dos produtos em um arquivo CSV
void salvarProdutosCSV()
 {
    ofstream arquivo("produtos.csv");  // Abre o arquivo para escrita
    if (arquivo.is_open())
    {
        for (const auto& produto : produtos)
        {
            arquivo << produto.nome << ";" << produto.preco << ";" << produto.estoque
                    << ";" << (produto.precoPorKg ? "kg" : "unidade") << endl;
        }
        arquivo.close();  // Fecha o arquivo ap�s salvar
        cout << "Produtos salvos com sucesso!\n";
    } else {
        cout << "Erro ao salvar os produtos no arquivo.\n";
    }
}

// Fun��o que carrega os dados dos produtos a partir de um arquivo CSV
void carregarProdutosCSV() {
    ifstream arquivo("produtos.csv");  // Abre o arquivo para leitura
    string linha;
    produtos.clear();  // Limpa a lista de produtos antes de carregar os dados do arquivo
    while (getline(arquivo, linha))
    {
        stringstream ss(linha);
        Produto produto;
        string tipoPreco;

        // Separa os dados de cada linha (nome, pre�o, estoque e tipo de pre�o)
        getline(ss, produto.nome, ';');
        ss >> produto.preco;
        ss.ignore();
        ss >> produto.estoque;
        ss.ignore();
        getline(ss, tipoPreco);

        produto.precoPorKg = (tipoPreco == "kg");  // Verifica se o tipo de pre�o � por kg

        produtos.push_back(produto);  // Adiciona o produto � lista
    }
    arquivo.close();  // Fecha o arquivo ap�s carregar os dados
}

// Fun��o que verifica se o arquivo de produtos foi modificado
bool arquivoModificado() {
    static time_t ultimaModificacao = 0;  // Armazena a �ltima modifica��o
    struct _stat fileStat;  // Usar _stat no lugar de stat no MinGW
    if (_stat("produtos.csv", &fileStat) == 0) {  // Usa _stat, em vez de stat, no MinGW
        if (fileStat.st_mtime != ultimaModificacao) {
            ultimaModificacao = fileStat.st_mtime;
            return true;  // Retorna true se o arquivo foi modificado
        }
    }
    return false;  // Retorna false se o arquivo n�o foi modificado
}
int main()
 {
    setlocale(LC_ALL, "");  // Configura a localidade para permitir caracteres especiais
    modoAdministrador();  // Inicia o modo administrador
    return 0;
}
