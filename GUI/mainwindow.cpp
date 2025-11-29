#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include <QMessageBox>

#include "../SRC/Funcao/EqCorda.hpp"
#include "../SRC/Metodos/MetodoNewton.hpp"
#include "../SRC/Metodos/MetodoNewtonDdxNum.hpp"
#include "../SRC/Metodos/MetodoNewtonFL.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableResultados->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Deixar liberado digitar apenas digitos (Incluindo os negativos)
    QRegularExpression rx("^-?[0-9.,]*$");
    QValidator *valDouble = new QRegularExpressionValidator(rx, this);

    QRegularExpression rt("^[0-9.,]*$");
    QValidator *valEps = new QRegularExpressionValidator(rt, this);
    //p numeros reais

    ui->inputLambda->setValidator(valDouble);
    ui->inputA2->setValidator(valDouble);
    ui->inputA3->setValidator(valDouble);
    ui->inputEps->setValidator(valEps);

    //p numeros inteiros
    QIntValidator *valInt = new QIntValidator(0, 1000000, this);
    ui->inputN->setValidator(valInt);
    ui->inputMaxIter->setValidator(valInt);


    ui->tableResultados->setColumnCount(3);
    ui->tableResultados->setHorizontalHeaderLabels(
        {"Método", "Raiz", "Iterações"});
}

void MainWindow::on_BtnCalcular_clicked(){
    executarCalculos();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::executarCalculos()
{
    int n = ui->inputN->text().toInt();
    if(n == 0){
        QMessageBox:: warning( this, "Erro", "Insira um valor maior que 0 para n");
        return;
    }
    if(listaLambdas.size() < n){
        QMessageBox:: warning( this, "Erro", "Insira n valores para lambda");
        return;
    }
    if(ui->inputA2->text().isEmpty() || ui->inputA3->text().isEmpty() || ui->inputEps->text().isEmpty() || ui->inputMaxIter->text().isEmpty()){
        QMessageBox::warning(this, "Erro", "Preencha todos os campos");
        return;
    }

    double a2     = ui->inputA2->text().replace(",", ".").toDouble();
    double a3     = ui->inputA3->text().replace(",", ".").toDouble();
    double eps    = ui->inputEps->text().replace(",", ".").toDouble();
    int maxIter   = ui->inputMaxIter->text().toInt();

    QString textoFuncao = QString("f(d) = %1*d³ + %2*d + 3").arg(QString::number(a3, 'f', 2), QString::number(a2, 'f', 2));


    ui->labelFuncao->setText(textoFuncao);

    EqCorda p(a3, a2);
    ui->tableResultados->setRowCount(0);

    // ------------------
    // Método 1
    // ------------------
    MetodoNewton m1(maxIter, 0.5, p, eps);
    double r1 = m1.executaMetodo();
    adicionarResultadoNaTabela("Newton", r1, m1.getIter());

    // ------------------
    // Método 2
    // ------------------
    MetodoNewtonDdxNum m2(maxIter, 0.5, p, eps);
    double r2 = m2.executaMetodo();
    adicionarResultadoNaTabela("Newton DdxNum", r2, m2.getIter());

    // ------------------
    // Método 3
    // ------------------
    for(const double &lambda : listaLambdas){
        MetodoNewtonFL m3(maxIter, 0.5, lambda, p, eps);
        double r3 = m3.executaMetodo();
        adicionarResultadoNaTabela(QString("Newton FL | λ = %1").arg(lambda), r3, m3.getIter());
    }
}

//Função pra adicionar coisas na tabela
void MainWindow::adicionarResultadoNaTabela(
const QString &nome, double raiz, int iter)
{
    int row = ui->tableResultados->rowCount();
    ui->tableResultados->insertRow(row);

    ui->tableResultados->setItem(row, 0, new QTableWidgetItem(nome));
    QString raizFormatada = QString::number(raiz, 'f', 20);
    ui->tableResultados->setItem(row, 1, new QTableWidgetItem(raizFormatada));
    ui->tableResultados->setItem(row, 2, new QTableWidgetItem(QString::number(iter)));
}

void MainWindow::on_btnLambda_clicked()
{
    int limite = ui->inputN->text().toInt();

    //Ve se o n já atingiu o limite
    if (listaLambdas.size() >= limite)
    {
        QMessageBox::warning(this, "Limite atingido", "Você já adicionou todos os n lambdas permitidos.");
        return;
    }

    //Aq Confere se tá preenchido
    QString txt = ui->inputLambda->text();
    if (txt.isEmpty())
    {
        QMessageBox::warning(this, "Erro", "Digite um valor para lambda.");
        return;
    }
    //desabilita o input do N
    ui->inputN->setReadOnly(true);

    txt.replace(",", ".");
    double valor = txt.toDouble();

    listaLambdas.push_back(valor);
    ui->vetorLambda->append(QString::number(valor));
    ui->inputLambda->clear();
}


void MainWindow::on_btnLimpar_clicked()
{
    //Reseta tudo
    listaLambdas.clear();
    ui->inputN->setReadOnly(false);
    ui->vetorLambda->clear();

    ui->tableResultados->setRowCount(0);
}

void MainWindow::on_btnLambdaRem_clicked(){
    QString texto = ui->vetorLambda->toPlainText();
    QStringList linhas = texto.split("\n");

    //Confere se o vetor está vazio
    if (!listaLambdas.isEmpty())
    {
        listaLambdas.pop_back();
        linhas.removeLast();
        ui->vetorLambda->setPlainText(linhas.join("\n"));
    }else{
        QMessageBox::warning(this, "Erro", "Não há valores de lambda para remover");
    }

}
