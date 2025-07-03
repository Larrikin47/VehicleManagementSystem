#pragma once
#include <QDialog>
namespace Ui {
class AddVehicleDialog;
}

class AddVehicleDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddVehicleDialog(QWidget *parent = nullptr);
    ~AddVehicleDialog();
    QString getName() const;
    double getRate() const;

private:
    Ui::AddVehicleDialog *ui;
};
