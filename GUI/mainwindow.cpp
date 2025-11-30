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

    //Eps nao pode serr negativo, ent esse serve para reais nao negativos
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


    ui->tableResultados->setColumnCount(7);
    ui->tableResultados->setHorizontalHeaderLabels(
        {"Método","a2","a3", "Raiz", "f(x)", "Iterações", "Situação"});
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
    if(ui->inputEps->text().isEmpty() || ui->inputMaxIter->text().isEmpty()){
        QMessageBox::warning(this, "Erro", "Preencha todos os campos");
        return;
    }

    if(n == 0){
        QMessageBox:: warning( this, "Erro", "Insira um valor maior que 0 para n");
        return;
    }
    if(listaLambdas.size() < n){
        QMessageBox:: warning( this, "Erro", "Insira n valores para lambda, a2 e a3");
        return;
    }


    double eps    = ui->inputEps->text().replace(",", ".").toDouble();
    int maxIter   = ui->inputMaxIter->text().toInt();

    if(eps < 0 || eps > 1){
        QMessageBox::warning(this, "Valor incorreto", "Digite um epsilon próximo de 0");
        return;
    }

    ui->tableResultados->setRowCount(0);

    for(int i = 0; i + 1 < listaA2A3.size(); i+=2){

        double a2 = listaA2A3[i];
        double a3 = listaA2A3[i+1];

        QString textoFuncao = QString("f(d) = %1*d³ + %2*d + 3").arg(QString::number(a3, 'f', 2), QString::number(a2, 'f', 2));
        ui->labelFuncao->setText(textoFuncao);

        EqCorda p(a3, a2);


        // ------------------
        // Método 1
        // ------------------
        MetodoNewton m1(maxIter, 0.5, p, eps);
        double r1 = m1.executaMetodo();
        if(m1.getIter() >= maxIter){
            if(r1>0.3)
                adicionarResultadoNaTabela(QString("Newton"), a2, a3, r1, p.f(r1), "Limite ultrapassado!", "Arriscado");
            else
                adicionarResultadoNaTabela(QString("Newton"), a2, a3, r1, p.f(r1), "Limite ultrapassado!", "ok");
        }
        else{
            if(r1>0.3)
                adicionarResultadoNaTabela(QString("Newton"), a2, a3, r1, p.f(r1), m1.getIter(), "Arriscado");
            else
                adicionarResultadoNaTabela(QString("Newton"), a2, a3, r1, p.f(r1), m1.getIter(), "ok");
        }

        // ------------------
        // Método 2
        // ------------------
        MetodoNewtonDdxNum m2(maxIter, 0.5, p, eps);
        double r2 = m2.executaMetodo();

        if(m2.getIter() >= maxIter){
            if(r2>0.3)
                adicionarResultadoNaTabela(QString("Newton Ddx"), a2, a3, r2, p.f(r2), "Limite ultrapassado!", "Arriscado");
            else
                adicionarResultadoNaTabela(QString("Newton Ddx"), a2, a3, r2, p.f(r2), "Limite ultrapassado!", "ok");
        }
        else{
            if(r2>0.3)
                adicionarResultadoNaTabela(QString("Newton Ddx"), a2, a3, r2, p.f(r2), m2.getIter(), "Arriscado");
            else
                adicionarResultadoNaTabela(QString("Newton Ddx"), a2, a3, r2, p.f(r2), m2.getIter(), "ok");
        }

        // ------------------
        // Método 3
        // ------------------
        for(const double &lambda : listaLambdas){
            MetodoNewtonFL m3(maxIter, 0.5, lambda, p, eps);
            double r3 = m3.executaMetodo();

            if(m3.getIter() >= maxIter){
                if(r3>0.3)
                    adicionarResultadoNaTabela(QString("Newton FL | λ = %1").arg(lambda), a2, a3, r3, p.f(r3), "Limite ultrapassado!", "Arriscado");
                else
                    adicionarResultadoNaTabela(QString("Newton FL | λ = %1").arg(lambda), a2, a3, r3, p.f(r3), "Limite ultrapassado!", "ok");
            }
            else{
                if(r3>0.3)
                    adicionarResultadoNaTabela(QString("Newton FL | λ = %1").arg(lambda), a2, a3, r3, p.f(r3), m3.getIter(), "Arriscado");
                else
                    adicionarResultadoNaTabela(QString("Newton FL | λ = %1").arg(lambda), a2, a3, r3, p.f(r3), m3.getIter(), "ok");
            }
        }
    }
}

//Função pra adicionar coisas na tabela
void MainWindow::adicionarResultadoNaTabela(const QString &nome, double a2, double a3, double raiz, double funcao, int iter, QString situacao)
{
    int row = ui->tableResultados->rowCount();
    ui->tableResultados->insertRow(row);

    ui->tableResultados->setItem(row, 0, new QTableWidgetItem(nome));

    ui->tableResultados->setItem(row, 1, new QTableWidgetItem(QString::number(a2)));
    ui->tableResultados->setItem(row, 2, new QTableWidgetItem(QString::number(a3)));

    QString raizFormatada = QString::number(raiz, 'f', 20);
    ui->tableResultados->setItem(row, 3, new QTableWidgetItem(raizFormatada));

    QString funcaoFormatada = QString::number(funcao, 'f', 20);
    ui->tableResultados->setItem(row, 4, new QTableWidgetItem(funcaoFormatada));

    ui->tableResultados->setItem(row, 5, new QTableWidgetItem(QString::number(iter)));

    ui->tableResultados->setItem(row, 6, new QTableWidgetItem(situacao));
}

//Caso o limite seja atingido
void MainWindow::adicionarResultadoNaTabela(const QString &nome, double a2, double a3, double raiz, double funcao, QString iter, QString situacao)
{
    int row = ui->tableResultados->rowCount();
    ui->tableResultados->insertRow(row);

    ui->tableResultados->setItem(row, 0, new QTableWidgetItem(nome));

    ui->tableResultados->setItem(row, 1, new QTableWidgetItem(QString::number(a2)));
    ui->tableResultados->setItem(row, 2, new QTableWidgetItem(QString::number(a3)));

    QString raizFormatada = QString::number(raiz, 'f', 20);
    ui->tableResultados->setItem(row, 3, new QTableWidgetItem(raizFormatada));

    QString funcaoFormatada = QString::number(funcao, 'f', 20);
    ui->tableResultados->setItem(row, 4, new QTableWidgetItem(funcaoFormatada));

    ui->tableResultados->setItem(row, 5, new QTableWidgetItem(iter));

    ui->tableResultados->setItem(row, 6, new QTableWidgetItem(situacao));
}

void MainWindow::on_btnLambda_clicked()
{
    int limite = ui->inputN->text().toInt();

    //Ve se o n já atingiu o limite
    if (listaLambdas.size() >= limite)
    {
        QMessageBox::warning(this, "Limite atingido", "Você já adicionou todos os n conjuntos permitidos.");
        return;
    }

    //Aq Confere se tá preenchido
    QString txtLambda = ui->inputLambda->text();
    QString txtA2 = ui->inputA2->text();
    QString txtA3 = ui->inputA3->text();


    if (txtLambda.isEmpty() || txtA2.isEmpty() || txtA3.isEmpty())
    {
        QMessageBox::warning(this, "Erro", "Preencha corretamente todos os campos.");
        return;
    }

    //desabilita o input do N
    ui->inputN->setReadOnly(true);

    double valorLambda = txtLambda.replace(",", ".").toDouble();
    double valorA2 = txtA2.replace(",", ".").toDouble();
    double valorA3 = txtA3.replace(",", ".").toDouble();

    listaLambdas.push_back(valorLambda);
    listaA2A3.push_back(valorA2);
    listaA2A3.push_back(valorA3);

    QString txtApresentacao = "λ =" + QString:: number(valorLambda) + " | " + "a2 = " + QString:: number(valorA2) + " | " + "a3 = " + QString:: number(valorA3);
    ui->vetorLambda->append(txtApresentacao);
    ui->inputLambda->clear();
    ui->inputA2->clear();
    ui->inputA3->clear();
}


void MainWindow::on_btnLimpar_clicked()
{
    //Reseta tudo
    listaLambdas.clear();
    listaA2A3.clear();

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
        listaA2A3.pop_back();
        listaA2A3.pop_back();

        linhas.removeLast();
        ui->vetorLambda->setPlainText(linhas.join("\n"));
    }else{
        QMessageBox::warning(this, "Erro", "Não há conjunto para remover");
    }

}
