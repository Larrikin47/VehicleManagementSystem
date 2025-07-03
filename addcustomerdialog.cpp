#include "addcustomerdialog.h"
#include "ui_addcustomerdialog.h"  // Must include the generated UI header

AddCustomerDialog::AddCustomerDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::AddCustomerDialog) {
    ui->setupUi(this);
}

AddCustomerDialog::~AddCustomerDialog() {
    delete ui;
}

QString AddCustomerDialog::getName() const {
    return ui->NameEdit->text();  // Matches <widget name="NameEdit"> from your .ui
}

QString AddCustomerDialog::getPhone() const {
    return ui->phoneEdit->text();
}

QString AddCustomerDialog::getEmail() const {
    return ui->emailEdit->text();
}
