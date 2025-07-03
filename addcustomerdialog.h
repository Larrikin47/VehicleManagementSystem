#pragma once

#include <QDialog>

namespace Ui {
class AddCustomerDialog;  // Forward declaration of the UI class
}

class AddCustomerDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddCustomerDialog(QWidget *parent = nullptr);
    ~AddCustomerDialog();

    QString getName() const;
    QString getPhone() const;
    QString getEmail() const;

private:
    Ui::AddCustomerDialog *ui;
};
