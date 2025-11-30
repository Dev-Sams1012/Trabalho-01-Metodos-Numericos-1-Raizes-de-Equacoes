#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Trabalho I - Métodos Numéricos I");
    w.setWindowIcon(QIcon("GUI/Icons/logo.png"));
    w.show();
    return a.exec();
}
