#pragma once

#include <QDialog>
#include "ui_addrentaldialog.h"  // ✅ Include the full UI definition

class AddRentalDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddRentalDialog(QWidget *parent = nullptr);
    ~AddRentalDialog();

    int getSelectedCustomerId() const;
    int getSelectedVehicleId() const;

private:
    Ui::AddRentalDialog *ui;
    void loadCustomers();
    void loadVehicles();
};
