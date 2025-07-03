/* #include "addvehicledialog.h"
#include "ui_addvehicledialog.h"

AddVehicleDialog::AddVehicleDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddVehicleDialog)
{
    ui->setupUi(this);
}

AddVehicleDialog::~AddVehicleDialog()
{
    delete ui;
}

QString AddVehicleDialog::getName() const
{
    return ui->nameEdit->text();
}

double AddVehicleDialog::getRate() const
{
    return ui->rateEdit->value();
}
*/

#include "addvehicledialog.h"
#include "ui_addvehicledialog.h"

AddVehicleDialog::AddVehicleDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddVehicleDialog) {
    ui->setupUi(this);
}

AddVehicleDialog::~AddVehicleDialog() {
    delete ui;
}

QString AddVehicleDialog::getName() const {
    return ui->nameEdit->text();
}

double AddVehicleDialog::getRate() const {
    return ui->rateEdit->value();
}
