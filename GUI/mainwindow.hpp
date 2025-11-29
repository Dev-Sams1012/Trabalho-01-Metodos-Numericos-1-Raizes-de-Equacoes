#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void executarCalculos();
    void on_btnLambda_clicked();
    void on_btnLimpar_clicked();
    void on_btnLambdaRem_clicked();
    void on_BtnCalcular_clicked();

private:
    Ui::MainWindow *ui;

    QVector<double> listaLambdas;

    void adicionarResultadoNaTabela(const QString &nome, double raiz, int iteracoes);
};
#endif // MAINWINDOW_HPP
