#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void adicionarExecucao();
    void abrirQuadroResposta();
    void abrirQuadroComparativo();

private:
    QLineEdit *entrada;
    QListWidget *listaExecucoes;
    QTableWidget *tabela;
};