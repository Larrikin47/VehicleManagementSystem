/* #include "loginwindow.h"
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    if (ui->usernameEdit->text() == "admin" && ui->passwordEdit->text() == "1234") {
        MainWindow *mw = new MainWindow();
        mw->show();
        accept();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password");
    }
}
*/
#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::on_loginButton_clicked() {
    if (ui->usernameEdit->text() == "admin" && ui->passwordEdit->text() == "1234") {
        MainWindow *mw = new MainWindow();
        mw->show();
        accept();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password");
    }
}
