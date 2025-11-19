#include "MainWindow.hpp"
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    entrada = new QLineEdit();
    listaExecucoes = new QListWidget();
    tabela = new QTableWidget(0, 3);

    QPushButton *btnAdd = new QPushButton("Adicionar");
    QPushButton *btnQuadro = new QPushButton("Quadro de Resposta");
    QPushButton *btnComparativo = new QPushButton("Quadro Comparativo");

    layout->addWidget(entrada);
    layout->addWidget(btnAdd);
    layout->addWidget(listaExecucoes);
    layout->addWidget(tabela);
    layout->addWidget(btnQuadro);
    layout->addWidget(btnComparativo);

    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::adicionarExecucao);
    connect(btnQuadro, &QPushButton::clicked, this, &MainWindow::abrirQuadroResposta);
    connect(btnComparativo, &QPushButton::clicked, this, &MainWindow::abrirQuadroComparativo);

    setCentralWidget(central);
}

void MainWindow::adicionarExecucao()
{
    QString valor = entrada->text();
    listaExecucoes->addItem(valor);

    // Aqui você chama seus métodos numéricos em C++
    // e adiciona na tabela
}

void MainWindow::abrirQuadroResposta()
{
    // Abre uma nova janela (QDialog) com o resultado
}

void MainWindow::abrirQuadroComparativo()
{
    // Abre uma nova janela com comparações
}