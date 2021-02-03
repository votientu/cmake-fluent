#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonCMakeList_clicked();

    void on_pushButtonBuild_clicked();

    void on_comboBoxVersionChoice_activated(int index);

    void on_lineEditVersion_textChanged(const QString &arg1);

private:
    void checkVersionChoice();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
