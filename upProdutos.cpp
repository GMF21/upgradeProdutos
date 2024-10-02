#include <iostream>
#include <fstream>

using namespace std;

struct produto {
    int Id;
    string nome;
    float preco;
    int quantidade;
    char status;  // 'A' para Ativo, 'D' para eliminado
};

void adicionarProduto(produto produtos[], int& quantidadeAtual) {
    cout << "Nome do produto: ";
    cin >> produtos[quantidadeAtual].nome;
    cout << "Preço do produto: ";
    cin >> produtos[quantidadeAtual].preco;
    cout << "Quantidade em stock: ";
    cin >> produtos[quantidadeAtual].quantidade;
    produtos[quantidadeAtual].Id = quantidadeAtual + 1; // Atribuir um ID unico baseado na posição
    produtos[quantidadeAtual].status = 'A';  // Definir o status como ativo
    quantidadeAtual++;
}

void exibirProdutos(const produto produtos[], int quantidadeAtual) {
    for (int i = 0; i < quantidadeAtual; i++){
            cout << "Produto " << produtos[i].Id << ":" << endl;
            cout << "Nome: " << produtos[i].nome << endl;
            cout << "Preço: " << produtos[i].preco << endl;
            cout << "Quantidade: " << produtos[i].quantidade << endl;
            cout << "-------------------------" << endl;
        
    }
}

void salvarProdutos(const produto produtos[], int quantidadeAtual) {
    ofstream file("produtos.txt");

    for (int i = 0; i < quantidadeAtual; i++) {
        file << produtos[i].Id << ",";
        file << produtos[i].nome << ",";
        file << produtos[i].preco << ",";
        file << produtos[i].quantidade << ",";
        file << produtos[i].status << endl;  // Salvar também o status
    }

    file.close();
    cout << "Produtos salvos com sucesso no arquivo" << endl;
}

float calcularValorTotal(const produto produtos[], int quantidadeAtual) {
    float valorTotal = 0.0;
    for (int i = 0; i < quantidadeAtual; i++) {
        
        valorTotal += produtos[i].preco * produtos[i].quantidade;
        
    }
    return valorTotal;
}

// Função para alterar produto (apenas produtos ativos podem ser alterados)
void alterarProduto(produto produtos[], int quantidadeAtual) {
    int id;
    cout << "Informe o ID do produto que deseja alterar: ";
    cin >> id;

    bool encontrado = false;
    for (int i = 0; i < quantidadeAtual; i++) {
        if (produtos[i].Id == id && produtos[i].status == 'A') {
            encontrado = true;
            cout << "Nome atual: " << produtos[i].nome << endl;
            cout << "Novo nome: ";
            cin >> produtos[i].nome;

            cout << "Preço atual: " << produtos[i].preco << endl;
            cout << "Novo preço: ";
            cin >> produtos[i].preco;

            cout << "Quantidade atual: " << produtos[i].quantidade << endl;
            cout << "Nova quantidade: ";
            cin >> produtos[i].quantidade;

            cout << "Produto atualizado com sucesso!" << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "Produto com ID " << id << " não encontrado ou está eliminado." << endl;
    }
}

// Função para eliminar produto (altera o status para 'D')
void eliminarProduto(produto produtos[], int quantidadeAtual) {
    int id;
    cout << "Informe o ID do produto que deseja eliminar: ";
    cin >> id;

    bool encontrado = false;
    for (int i = 0; i < quantidadeAtual; i++) {
        if (produtos[i].Id == id && produtos[i].status == 'A') {
            encontrado = true;
            produtos[i].status = 'D';  // Marca como eliminado
            cout << "Produto com ID " << id << " foi eliminado." << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "Produto com ID " << id << " não encontrado ou já foi eliminado." << endl;
    }
}

int main() {
    produto maxProdutos[100]; // max de produtos
    int quantidadeAtual = 0; // quantidade de produtos no stock
    int escolha;

    do {
        cout << "Escolha uma opção:" << endl;
        cout << "1. Adicionar Produto" << endl;
        cout << "2. Exibir Produtos" << endl;
        cout << "3. Calcular Valor Total do estoque" << endl;
        cout << "4. Salvar Produtos em Arquivo" << endl;
        cout << "5. Alterar Produto" << endl;
        cout << "6. Eliminar Produto" << endl;
        cout << "0. Sair" << endl;
        cin >> escolha;

        switch (escolha) {
            case 1:
                adicionarProduto(maxProdutos, quantidadeAtual);
                break;
            case 2:
                exibirProdutos(maxProdutos, quantidadeAtual);
                break;
            case 3:
                cout << "Valor total do estoque: " << calcularValorTotal(maxProdutos, quantidadeAtual) << endl;
                break;
            case 4:
                salvarProdutos(maxProdutos, quantidadeAtual);
                break;
            case 5:
                alterarProduto(maxProdutos, quantidadeAtual);
                break;
            case 6:
                eliminarProduto(maxProdutos, quantidadeAtual);
                break;
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Escolha outra opção." << endl;
        }
    } while (escolha != 0);

    return 0;
}
