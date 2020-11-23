#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>            // to open and write CMakeLists.txt
#include <QTextStream>
#include <QDir>             // to create new build folder
#include <QProcess>
#include <QStandardPaths>   // to return to run time location

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("cmake-tutorial");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonCMakeList_clicked()
{
    QFile file("CMakeLists.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        // CMake minimum version
        QString cMakeMinimumVersion;
        if (!ui->lineEditCmakeMinimumVersion->text().isEmpty())
            cMakeMinimumVersion = ui->lineEditCmakeMinimumVersion->text();
        else
            cMakeMinimumVersion = ui->lineEditCmakeMinimumVersion->placeholderText();

        stream << QString("cmake_minimum_required(VERSION %1)").arg(cMakeMinimumVersion) << Qt::endl;
        stream << Qt::endl;

        // Project name and version
        QString projectName;
        if (!ui->lineEditProjectName->text().isEmpty())
            projectName = ui->lineEditProjectName->text();
        else
            projectName = ui->lineEditProjectName->placeholderText();

        if (ui->comboBoxVersionChoice->currentText().toLower().contains("no"))
            stream << QString("project(%1)").arg(projectName) << Qt::endl;
        else if (ui->comboBoxVersionChoice->currentText().toLower().contains(("simple"))) {
            QString version;
            if (!ui->lineEditVersion->text().isEmpty())
                version = ui->lineEditVersion->text();
            else
                version = ui->lineEditVersion->placeholderText();

            stream << "# set the project name and version" << Qt::endl;
            stream << QString("project(%1 VERSION %2)").arg(projectName).arg(version) << Qt::endl;
        }
        else {
            QFile versionFile(ui->lineEditVersion->text());
            if (versionFile.exists()) {
                stream << "# include cmake scripts" << Qt::endl;
                stream << QString("include(%1)").arg(ui->lineEditVersion->text());
                ui->plainTextEditLog->appendPlainText("Version file added");
            } else
                ui->plainTextEditLog->appendPlainText("Version file does not exist");
        }

        stream << Qt::endl;


        // Add executable or library
        if (ui->comboBoxProjectType->currentText().contains("exe")) {
            stream << "# add the executable" << Qt::endl;
            stream << "add_executable(Tutorial tutorial.cxx)" << Qt::endl;
        } else {

        }
        stream << Qt::endl;
    }
}

void MainWindow::on_pushButtonBuild_clicked()
{
    QDir dir("build");
    // Check before creating new folder
    if (!dir.exists())
        dir.mkpath(".");
    QDir root = QDir::currentPath();
    QDir::setCurrent(dir.absolutePath());

    QProcess::execute("cmake ..");
    QProcess::execute("make");

    QDir::setCurrent(root.absolutePath());
}

void MainWindow::on_comboBoxVersionChoice_activated(int /*index*/)
{
    checkVersionChoice();
}

void MainWindow::checkVersionChoice()
{
    QString versionChoice = ui->comboBoxVersionChoice->currentText();
    if (versionChoice.toLower().contains("no"))
        ui->lineEditVersion->setPlaceholderText("Ignore this line");
    else if (versionChoice.toLower().contains(("simple")))
        ui->lineEditVersion->setPlaceholderText("1.0");
    else {
        ui->lineEditVersion->setText("CMake/project-version.cmake");
    }
}

void MainWindow::on_lineEditVersion_textChanged(const QString &text)
{
    if (text.contains("file://"))
    {
        // Keep useful path in the text
    }
}
